#include <stdio.h>
#include <string.h>

#include "tecnico/tecnico.h"

typedef struct {
    char username[100];
    char password[50];
} LOGIN;

int main() {
    printf("Iniciando o programa...\n");

    // Inicializar estruturas/listas ligadas a partir dos ficheiros
    NODE *tecnicos = initTecnicos();

    if (tecnicos != NULL) {
        printf("Lista de técnicos carregada com sucesso.\n");
    } else {
        printf("Erro: Nenhum técnico foi carregado.\n");
    }

    // Lógica de Login
    LOGIN loginData;

    printf("--< Area de Login >--");
    printf("\nUsername: ");
    scanf("%s", &loginData.username);
    if(strcmp(loginData.username, "admin")==0) {
        // Admin
    } else {
        printf("Bem-vindo, Técnico!\n");
        // Lógica para técnico
    }

    printf("Nao sei programar");
    return 0;
}