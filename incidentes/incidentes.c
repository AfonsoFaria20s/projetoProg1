#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "incidentes.h"

// Funcao para inicializar a lista ligada a partir do ficheiro
NODE_INCIDENTE* initIncidentes() {
    FILE *fp = fopen("dados\\incidentes.dat", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro 'incidentes.dat'!\n");
        return NULL;
    }

    NODE_INCIDENTE *head = NULL; // Cabeca da lista ligada
    NODE_INCIDENTE *current = NULL;

    INCIDENTE temp;
    int count = 0; // Contador para incidentes carregados

    while (fread(&temp, sizeof(NODE_INCIDENTE), 1, fp)) {
        // Criar um novo node
        NODE_INCIDENTE *newNode = (NODE_INCIDENTE *)malloc(sizeof(NODE_INCIDENTE));
        if (newNode == NULL) {
            printf("Erro ao alocar memória para um novo incidente!\n");
            fclose(fp);
            // Libertar memoria ja alocada
            while (head != NULL) {
                NODE_INCIDENTE *toFree = head;
                head = head->next;
                free(toFree);
            }
            return NULL;
        }
        

        // Copiar os dados do incidente
        newNode->incidente = temp;
        newNode->next = NULL;

        // Adicionar o node a lista ligada
        if (head == NULL) {
            head = newNode;
        } else {
            current->next = newNode;
        }
        current = newNode;
        count++;
    }

    fclose(fp);

    if (count == 0) {
        printf("Nenhum admin foi encontrado no ficheiro.\n");
    } else {
        printf("%d admin(s) carregado(s) com sucesso.\n", count);
    }

    return head;
}


void removerIncidente(NODE_INCIDENTE **incidentes, int id) {
    NODE_INCIDENTE *curr = *incidentes, *prev = NULL;
    while (curr) {
        if (curr->incidente.id == id) {
            if (prev) prev->next = curr->next;
            else *incidentes = curr->next;
            free(curr);
            saveIncidentesToFile(*incidentes);
            printf("Incidente %d removido.\n", id);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Incidente %d não encontrado.\n", id);
}

void saveIncidentesToFile(NODE_INCIDENTE *incidentes) {
    FILE *fp = fopen("dados\\incidentes.dat", "wb");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro 'incidentes.dat' para escrita!\n");
        return;
    }

    NODE_INCIDENTE *curr = incidentes;
    while (curr) {
        fwrite(&(curr->incidente), sizeof(INCIDENTE), 1, fp);
        curr = curr->next;
    }

    fclose(fp);
    printf("Incidentes guardados com sucesso.\n");
}

void printIncidentes(NODE_INCIDENTE *incidentes) {
    while(incidentes) {
        printf("Nome: %s", incidentes->incidente.nome);
        printf("Tecnico atribuido: %s", incidentes->incidente.tecnico_atribuido);

        //Estado
        if(incidentes->incidente.estado==0) printf("Estado: Nao Resolvido");
        else printf("Estado: Resolvido");

        // Severidade: 1, 2, 3 -> baixa, media, alta
        if(incidentes->incidente.severidade==1) printf("Severidade: Baixa");
        if(incidentes->incidente.severidade==2) printf("Severidade: Media");
        if(incidentes->incidente.severidade==3) printf("Severidade: Alta");

        /* Tipo
            1 - Phishing
            2 - Malware
            3 - Acesso nao autorizado
            4 - Falha na conexao
        */
        if(incidentes->incidente.tipo==1) printf("Tipo: Phishing");
        else if(incidentes->incidente.tipo==2) printf("Tipo: Malware");
        else if(incidentes->incidente.tipo==3) printf("Tipo: Acesso nao autorizado");
        else if(incidentes->incidente.tipo==4) printf("Tipo: Falha na conexao");

        // Data
        printf("Data: %i/%i/%i", incidentes->incidente.data_criacao.dia, incidentes->incidente.data_criacao.mes, incidentes->incidente.data_criacao.ano);
    }
}

int addIncidente(NODE_INCIDENTE *incidentes, INCIDENTE newIncidente) {
    NODE_INCIDENTE *LAST = NULL;
    LAST = incidentes;

    // Iterar ate ao final
    while (LAST != NULL) {
        LAST = LAST->next;
    }
    
    LAST->incidente = newIncidente;

    return 0;
}

int getLastId(NODE_INCIDENTE *incidentes) {
    NODE_INCIDENTE *LAST = NULL;
    LAST = incidentes;

    // Iterar ate ao final
    while (LAST != NULL) {
        LAST = LAST->next;
    }
    
    return LAST->incidente.id;
}