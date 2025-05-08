#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "admin.h"

// Funcao para inicializar a lista ligada a partir do ficheiro
NODE* initAdmins() {
    FILE *fp = fopen("dados\\tecnico_list.dat", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro 'tecnico_list.dat'!\n");
        return NULL;
    }

    NODE *head = NULL; // Cabeca da lista ligada
    NODE *current = NULL;

    ADMIN temp;
    int count = 0; // Contador para admins carregados

    while (fread(&temp, sizeof(ADMIN), 1, fp)) {
        // Criar um novo node
        NODE *newNode = (NODE *)malloc(sizeof(NODE));
        if (newNode == NULL) {
            printf("Erro ao alocar memória para um novo admin!\n");
            fclose(fp);
            // Libertar memoria ja alocada
            while (head != NULL) {
                NODE *toFree = head;
                head = head->next;
                free(toFree);
            }
            return NULL;
        }

        // Copiar os dados do admin
        newNode->admin = temp;
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