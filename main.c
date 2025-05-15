#include <stdio.h>
#include <string.h>
#include "tecnico/tecnico.h"
#include "admin/admin.h"

typedef struct {
    char username[100];
    char password[50];
} LOGIN;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    NODE *tecnicos = initTecnicos();
    LOGIN login;
    char resposta[10];
    int sair = 0;

    while (!sair) {
        printf("\n--< Area de Login >--\nUsername: ");
        fgets(login.username, sizeof(login.username), stdin);
        login.username[strcspn(login.username, "\n")] = '\0';

        // ADMIN
        if (strcmp(login.username, "admin") == 0) {
            int opt = 1;
            printf("\nBem-vindo, Admin!\n");
            while (opt != 0) {
                menuAdmin(&opt);
                switch (opt) {
                    case 1: // Validar tecnico
                        limparBuffer();
                        printf("\nUsername do tecnico a validar: ");
                        fgets(login.username, sizeof(login.username), stdin);
                        login.username[strcspn(login.username, "\n")] = '\0';
                        int res = validarTecnico(tecnicos, login.username);
                        if(res==1) {
                            printf("\nSucesso ao validar tecnico!");
                        } else if(res==0) {
                            printf("\nTecnico ja esta ativo!");
                        } else if(res==-1) {
                            printf("\nErro ao validar tecnico!");
                        }
                        break;
                    case 0:
                        printf("\nA sair do menu administrador...\n");
                        break;
                    default:
                        printf("\nOpção inválida!");
                }
            }
        }
        // TECNICO REGISTADO
        else if (isTecnicoRegistered(login.username, tecnicos)) {
            printf("Password: ");
            fgets(login.password, sizeof(login.password), stdin);
            login.password[strcspn(login.password, "\n")] = '\0';
            if (verifyTecnico(login.username, login.password, tecnicos)) {
                int opt = 1;
                printf("\nBem-vindo, %s!\n", login.username);
                while (opt != 0) {
                    menuTecnico(&opt);
                    switch (opt) {
                        case 0:
                            printf("\nA sair...\n");
                            break;
                        case 1:
                            printf("\n[Funcionalidade: Visualizar incidentes atribuídos]\n");
                            break;
                        default:
                            printf("\nOpcao invalida! Tente novamente.");
                            break;
                    }
                }
            } else {
                printf("\nPalavra passe errada!\n");
            }
        }
        // TECNICO NAO REGISTADO
        else {
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

        limparBuffer();
        // Perguntar se quer terminar o programa ou voltar ao login
        printf("\nDeseja terminar o programa? (sim/nao): ");
        fgets(resposta, sizeof(resposta), stdin);
        resposta[strcspn(resposta, "\n")] = '\0';
        if (strcmp(resposta, "sim") == 0) {
            sair = 1;
        }
    }

    freeTecnicos(tecnicos);
    return 0;
}
