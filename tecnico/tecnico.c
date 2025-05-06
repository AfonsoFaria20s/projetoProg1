#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tecnico.h"

// Estrutura para armazenar os dados de um tecnico
typedef struct {
    char user[100];
    char password[50];
} TECNICO;

// Estrutura para o node da lista ligada
typedef struct node {
    TECNICO tecnico;
    struct node *next;
} NODE;

// Funcao para inicializar a lista ligada a partir do ficheiro
NODE* initTecnicos() {
    FILE *fp = fopen("tecnico_list.dat", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro!\n");
        return NULL;
    }

    NODE *head = NULL; // Cabeca da lista ligada
    NODE *current = NULL;

    TECNICO temp;
    while (fread(&temp, sizeof(TECNICO), 1, fp)) {
        // Criar um novo node
        NODE *newNode = (NODE *)malloc(sizeof(NODE));
        if (newNode == NULL) {
            printf("Erro ao alocar memoria!\n");
            fclose(fp);
            return NULL;
        }

        // Copiar os dados do técnico
        newNode->tecnico = temp;
        newNode->next = NULL;

        // Adicionar o node a lista ligada
        if (head == NULL) {
            head = newNode;
        } else {
            current->next = newNode;
        }
        current = newNode;
    }

    fclose(fp);
    return head;
}