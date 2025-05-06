#include <stdio.h>
#include <string.h>

#include "tecnico.h"

typedef struct {
    char user[100];
    char password[50];
} TECNICO;

typedef struct {
    char user[100];
    char password[50];
} ADMIN;

int main() {
    // Login stuff
    TECNICO tecnicoLogin;

    // Inicializar estruturas/listas ligadas
    // a partir dos ficheiros
    NODE *tecnicos = initTecnicos();

    if (tecnicos != NULL) {
        printf("Lista de tecnicos:\n");
        printTecnicos(tecnicos);

        freeTecnicos(tecnicos);
    } else {
        printf("Nenhum técnico foi carregado.\n");
    }

printf("AIIIIIII");

    return 0;
}