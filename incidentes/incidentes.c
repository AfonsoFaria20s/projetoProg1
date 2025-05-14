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