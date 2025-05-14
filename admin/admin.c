#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "admin.h"
#include "../tecnico/tecnico.h"

// Funcao para inicializar a lista ligada a partir do ficheiro
NODE_ADMIN* initAdmins() {
    FILE *fp = fopen("dados\\tecnico_list.dat", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro 'tecnico_list.dat'!\n");
        return NULL;
    }

    NODE_ADMIN *head = NULL; // Cabeca da lista ligada
    NODE_ADMIN *current = NULL;

    ADMIN temp;
    int count = 0; // Contador para admins carregados

    while (fread(&temp, sizeof(ADMIN), 1, fp)) {
        // Criar um novo node
        NODE_ADMIN *newNode = (NODE_ADMIN *)malloc(sizeof(NODE_ADMIN));
        if (newNode == NULL) {
            printf("Erro ao alocar memória para um novo admin!\n");
            fclose(fp);
            // Libertar memoria ja alocada
            while (head != NULL) {
                NODE_ADMIN *toFree = head;
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


int valida_tecnico (NODE* inicio, char username[]){

    printTecnicos(inicio);

}