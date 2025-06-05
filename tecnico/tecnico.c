/**
 * @file tecnico.c
 * @brief Implementação das funções de gestão de técnicos.
 *
 * Este módulo permite inicializar, registar, validar login, ativar, listar e libertar técnicos,
 * bem como apresentar o menu de opções para técnicos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tecnico.h"

#define FILE_PATH "dados/tecnico_list.dat"

/**
 * @brief Inicializa a lista ligada de técnicos a partir do ficheiro binário.
 * @return Ponteiro para o início da lista ligada de técnicos.
 */
NODE_TECNICOS* initTecnicos() {
    FILE *fp = fopen(FILE_PATH, "rb");
    NODE_TECNICOS *head = NULL, *tail = NULL;
    if (fp) {
        TECNICO temp;
        // Lê cada técnico do ficheiro e adiciona à lista ligada
        while (fread(&temp, sizeof(TECNICO), 1, fp)) {
            NODE_TECNICOS *newNode = malloc(sizeof(NODE_TECNICOS));
            if (!newNode) break;
            newNode->tecnico = temp;
            newNode->next = NULL;
            if (!head) head = tail = newNode;
            else { tail->next = newNode; tail = newNode; }
        }
        fclose(fp);
    }
    return head;
}

/**
 * @brief Guarda a lista de técnicos no ficheiro binário.
 * @param tecnicos Ponteiro para o início da lista.
 * @return 0 em caso de sucesso, -1 em caso de erro.
 */
int saveTecnicosToFile(NODE_TECNICOS *tecnicos) {
    FILE *fp = fopen(FILE_PATH, "wb");
    if (!fp) return -1;
    // Escreve cada técnico no ficheiro
    while (tecnicos) {
        fwrite(&tecnicos->tecnico, sizeof(TECNICO), 1, fp);
        tecnicos = tecnicos->next;
    }
    fclose(fp);
    return 0;
}

/**
 * @brief Verifica se um técnico existe pelo username.
 * @param username Nome do técnico.
 * @param tecnicos Ponteiro para o início da lista.
 * @return 1 se existe, 0 caso contrário.
 */
int tecnicoExists(const char *username, NODE_TECNICOS *tecnicos) {
    while (tecnicos) {
        if (strcmp(tecnicos->tecnico.user, username) == 0)
            return 1;
        tecnicos = tecnicos->next;
    }
    return 0;
}

/**
 * @brief Regista um novo técnico na lista ligada.
 * @param username Nome do técnico.
 * @param password Palavra-passe.
 * @param tecnicos Ponteiro para o início da lista.
 * @return 1 em caso de sucesso, 0 em caso de erro.
 */
int registerTecnico(const char *username, const char *password, NODE_TECNICOS **tecnicos) {
    NODE_TECNICOS *newNode = malloc(sizeof(NODE_TECNICOS));
    if (!newNode) return 0;
    strncpy(newNode->tecnico.user, username, sizeof(newNode->tecnico.user));
    strncpy(newNode->tecnico.password, password, sizeof(newNode->tecnico.password));
    newNode->tecnico.isAtivo = 0; // Novo técnico começa como inativo
    newNode->next = NULL;
    if (!*tecnicos)
        *tecnicos = newNode;
    else {
        NODE_TECNICOS *temp = *tecnicos;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
    saveTecnicosToFile(*tecnicos);
    return 1;
}

/**
 * @brief Valida o login de um técnico.
 * @param username Nome do técnico.
 * @param password Palavra-passe.
 * @param tecnicos Ponteiro para o início da lista.
 * @return 1 se válido, 0 caso contrário.
 */
int validTecnicoLogin(char *username, char *password, NODE_TECNICOS *tecnicos) {
    while (tecnicos) {
        if (strcmp(tecnicos->tecnico.user, username) == 0 &&
            strcmp(tecnicos->tecnico.password, password) == 0)
            return 1;
        tecnicos = tecnicos->next;
    }
    return 0;
}

/**
 * @brief Liberta a memória ocupada pela lista de técnicos.
 * @param head Ponteiro para o início da lista.
 */
void freeTecnicos(NODE_TECNICOS *head) {
    while (head) {
        NODE_TECNICOS *temp = head;
        head = head->next;
        free(temp);
    }
}

/**
 * @brief Apresenta o menu de opções para o técnico.
 * @param opt Ponteiro para a opção escolhida.
 */
void menuTecnico(int *opt) {
    printf("\n--< Menu Tecnico >--");
    printf("\n1 - Visualizar incidentes atribuidos");
    printf("\n2 - Atualizar estado de incidente");
    printf("\n3 - Adicionar comentário");
    printf("\n4 - Delegar incidente");
    printf("\n5 - Registar ferramenta usada");
    printf("\n0 - Sair");
    printf("\nOpcao: ");
    scanf("%i", opt);
    while (getchar() != '\n');
}

/**
 * @brief Ativa um técnico (torna-o ativo).
 * @param tecnicos Ponteiro para o início da lista.
 * @param username Nome do técnico.
 * @return 1 se ativado, 0 se já estava ativo, -1 se não encontrado.
 */
int ativarTecnico(NODE_TECNICOS *tecnicos, char username[]) {
    while(tecnicos) {
        if(strcmp(tecnicos->tecnico.user, username)==0) {
            if(tecnicos->tecnico.isAtivo == 1) return 0;
            tecnicos->tecnico.isAtivo = 1;
            saveTecnicosToFile(tecnicos);
            return 1;
        }
        tecnicos = tecnicos->next;
    }
    return -1;
}

/**
 * @brief Lista todos os técnicos registados.
 * @param tecnicos Ponteiro para o início da lista.
 */
void listarTecnicos(NODE_TECNICOS *tecnicos) {
    printf("\n--- Lista de Técnicos ---\n");
    while (tecnicos) {
        printf("Username: %s | Estado: %s\n", tecnicos->tecnico.user, tecnicos->tecnico.isAtivo ? "Ativo" : "Inativo");
        tecnicos = tecnicos->next;
    }
}