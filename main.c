#include <stdio.h>
#include <string.h>
#include "tecnico/tecnico.h"

typedef struct {
    char username[100];
    char password[50];
} LOGIN;

int main() {
    NODE *tecnicos = initTecnicos();

    LOGIN login;
    char resposta[10];

    printf("\n--< Area de Login >--\nUsername: ");
    fgets(login.username, sizeof(login.username), stdin);
    login.username[strcspn(login.username, "\n")] = '\0';

        // LOGICA ADMIN
    if (strcmp(login.username, "admin") == 0) {
        printf("\nBem-vindo, Admin!\n");

        // LOGICA TECNICO LOGIN
    } else if (isTecnicoRegistered(login.username, tecnicos)) {
        printf("\nPassword: ");
        fgets(login.password, sizeof(login.password), stdin);
        login.password[strcspn(login.password, "\n")] = '\0';
        // Login sucesso
        if(verifyTecnico(login.username,login.password,tecnicos)) {
            
        } else{
            printf("\nPalavra passe errada!");
        }
    } else {

        // LOGICA TECNICO NAO REGISTADO

        printf("\nNao esta registado. Deseja registar-se? (sim/nao): ");
        fgets(resposta, sizeof(resposta), stdin);
        resposta[strcspn(resposta, "\n")] = '\0';

        if (strcmp(resposta, "sim") == 0) {
            printf("\nPassword (min 5 caracteres): ");
            fgets(login.password, sizeof(login.password), stdin);
            login.password[strcspn(login.password, "\n")] = '\0';

            while (strlen(login.password) < 5) {
                printf("\nPassword muito curta! Tente novamente: ");
                fgets(login.password, sizeof(login.password), stdin);
                login.password[strcspn(login.password, "\n")] = '\0';
            }

            if (registerTecnico(login.username, login.password, &tecnicos))
                printf("\nTecnico registado com sucesso!\n");
            else
                printf("\nErro ao registar tecnico.\n");
        } else {
            printf("\nOperacao cancelada.\n");
        }
    }

    freeTecnicos(tecnicos);
    return 0;
}
