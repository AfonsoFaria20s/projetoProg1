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
