#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tecnico.h"

#define FILE_PATH "dados/tecnico_list.dat"

NODE_TECNICOS* initTecnicos() {
    FILE *fp = fopen(FILE_PATH, "rb");
    if (!fp) return NULL;

    NODE_TECNICOS *head = NULL, *tail = NULL;
    TECNICO temp;

    while (fread(&temp, sizeof(TECNICO), 1, fp)) {
        NODE_TECNICOS *newNode = malloc(sizeof(NODE_TECNICOS));
        if (!newNode) break;

        newNode->tecnico = temp;
        newNode->next = NULL;

        if (!head)
            head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(fp);
    return head;
}

void menuTecnico(int *opt) {
    printf("\n--< Menu >--");
    printf("\n1 - Visualizar incidentes atribuidos");
    printf("\n2 - ");
    printf("\n0 - Sair");
    printf("\n\nOpcao: ");
    scanf("%i", opt);
    printf("------------");
}

int isTecnicoRegistered(const char *username, NODE_TECNICOS *tecnicos) {
    while (tecnicos) {
        if (strcmp(tecnicos->tecnico.user, username) == 0)
            return 1;
        tecnicos = tecnicos->next;
    }
    return 0;
}

int registerTecnico(const char *username, const char *password, NODE_TECNICOS **tecnicos) {
    NODE_TECNICOS *newNode = malloc(sizeof(NODE_TECNICOS));
    if (!newNode) return 0;

    strncpy(newNode->tecnico.user, username, sizeof(newNode->tecnico.user));
    strncpy(newNode->tecnico.password, password, sizeof(newNode->tecnico.password));
    newNode->tecnico.isAtivo = 0;
    
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

void saveTecnicosToFile(NODE_TECNICOS *tecnicos) {
    FILE *fp = fopen(FILE_PATH, "wb");
    if (!fp) return;

    while (tecnicos) {
        fwrite(&tecnicos->tecnico, sizeof(TECNICO), 1, fp);
        tecnicos = tecnicos->next;
    }

    fclose(fp);
}

void freeTecnicos(NODE_TECNICOS *head) {
    while (head) {
        NODE_TECNICOS *temp = head;
        head = head->next;
        free(temp);
    }
}

int verifyTecnico(char *username, char *password, NODE_TECNICOS *tecnicos) {
    while (tecnicos) {
        if (strcmp(tecnicos->tecnico.user, username) == 0) {
            if(strcmp(tecnicos->tecnico.password, password)==0) {
                return 1;
            }
        }
        tecnicos = tecnicos->next;
    }
    return 0;
}

NODE_TECNICOS* getTecnico(char *username, char *password, NODE_TECNICOS *tecnicos) {
    while (tecnicos) {
        // Verifica se o username e a password correspondem
        if ((strcmp(tecnicos->tecnico.user, username) == 0) && 
            (strcmp(tecnicos->tecnico.password, password) == 0)) {
            return tecnicos; // Retorna o ponteiro para o nó encontrado
        }
        tecnicos = tecnicos->next; // Avança para o próximo node
    }
    return NULL; // Retorna NULL se não encontrar o técnico
}

void printTecnicos(NODE_TECNICOS *tecnicos) {
    printf("\n--< Tecnicos atualmente registados >--");
    while(tecnicos) {
        printf("\nUsername: %s", tecnicos->tecnico.user);
        printf("\nPassword: %s", tecnicos->tecnico.password);
        printf("\n");
        tecnicos = tecnicos->next;
    }
}