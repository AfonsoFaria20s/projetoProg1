#include <stdio.h>
#include <string.h>

#include "tecnico.h"

typedef struct {
    char username[100];
    char password[50];
} LOGIN;

int main() {
    /*       
        Inicializar estruturas/listas       
        ligadas a partir dos ficheiros      
    */

    NODE *tecnicos = initTecnicos();      

    if (tecnicos != NULL) {
        printf("Lista de tecnicos:\n");
        printTecnicos(tecnicos);

        freeTecnicos(tecnicos);
    } else {
        printf("Nenhum técnico foi carregado.\n");
    }

    // Login Logic

    LOGIN loginData;

    printf("--< Area de Login >--");
    printf("\nUsername: ");
    scanf("%s", &loginData.username);
    if(strcmp(loginData.username, "admin")==0) {
        // Admin
    } else {
        // Tecnico
    }

    return 0;
}