#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tecnico.h"

#define FILE_PATH "dados/tecnico_list.dat"

NODE_TECNICOS* initTecnicos() {
    FILE *fp = fopen(FILE_PATH, "rb");
    NODE_TECNICOS *head = NULL, *tail = NULL;
    if (fp) {
        TECNICO temp;
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

int saveTecnicosToFile(NODE_TECNICOS *tecnicos) {
    FILE *fp = fopen(FILE_PATH, "wb");
    if (!fp) return -1;
    while (tecnicos) {
        fwrite(&tecnicos->tecnico, sizeof(TECNICO), 1, fp);
        tecnicos = tecnicos->next;
    }
    fclose(fp);
    return 0;
}

int tecnicoExists(const char *username, NODE_TECNICOS *tecnicos) {
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

int validTecnicoLogin(char *username, char *password, NODE_TECNICOS *tecnicos) {
    while (tecnicos) {
        if (strcmp(tecnicos->tecnico.user, username) == 0 &&
            strcmp(tecnicos->tecnico.password, password) == 0)
            return 1;
        tecnicos = tecnicos->next;
    }
    return 0;
}

void freeTecnicos(NODE_TECNICOS *head) {
    while (head) {
        NODE_TECNICOS *temp = head;
        head = head->next;
        free(temp);
    }
}

void menuTecnico(int *opt) {
    printf("\n--< Menu Tecnico >--");
    printf("\n1 - Visualizar incidentes atribuidos");
    printf("\n0 - Sair");
    printf("\nOpcao: ");
    scanf("%i", opt);
    while (getchar() != '\n');
}

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