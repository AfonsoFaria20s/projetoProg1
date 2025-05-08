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

    printf("--< Área de Login >--\n");
    printf("Username: ");
    scanf("%s", loginData.username); // Removido o '&'

    if (strcmp(loginData.username, "admin") == 0) {
        printf("Bem-vindo, Admin!\n");
        // Lógica para admin
    } else {
        printf("Bem-vindo, Técnico!\n");
        // Lógica para técnico
    }

    printf("Finalizando o programa...\n");
    return 0;
}