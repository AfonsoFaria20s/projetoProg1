#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tecnico.h"

// Função para inicializar a lista ligada a partir do ficheiro
NODE* initTecnicos() {
    FILE *fp = fopen("dados\\tecnico_list.dat", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro 'tecnico_list.dat'!\n");
        return NULL;
    }

    NODE *head = NULL; // Cabeça da lista ligada
    NODE *current = NULL;

    TECNICO temp;
    int count = 0; // Contador para técnicos carregados

    while (fread(&temp, sizeof(TECNICO), 1, fp)) {
        // Criar um novo node
        NODE *newNode = (NODE *)malloc(sizeof(NODE));
        if (newNode == NULL) {
            printf("Erro ao alocar memória para um novo técnico!\n");
            fclose(fp);
            // Liberar memória já alocada
            while (head != NULL) {
                NODE *toFree = head;
                head = head->next;
                free(toFree);
            }
            return NULL;
        }

        // Copiar os dados do técnico
        newNode->tecnico = temp;
        newNode->next = NULL;

        // Adicionar o node à lista ligada
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
        printf("Nenhum tecnico foi encontrado no ficheiro.\n");
    } else {
        printf("%d tecnico(s) carregado(s) com sucesso.\n", count);
    }

    return head;
}