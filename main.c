#include <stdio.h>
#include <string.h>
#include "tecnico/tecnico.h"
#include "admin/admin.h"
#include "incidentes/incidentes.h"
#include "utils/utils.h"
#include <time.h>

typedef struct {
    char username[100];
    char password[50];
} LOGIN;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    ADMIN admin = initAdmin();
    NODE_TECNICOS *tecnicos = initTecnicos();
    NODE_INCIDENTE *incidentes = initIncidentes();

    LOGIN login;
    INCIDENTE auxIncidente; int id;
    DATA_INCIDENTE data_incidente;

    char resposta[10];
    int sair = 0;

    while (!sair) {
        printf("\n--< Area de Login >--\nUsername: ");
        fgets(login.username, sizeof(login.username), stdin);
        login.username[strcspn(login.username, "\n")] = '\0';

        printf("%i", admin.firstTime);
        // ADMIN
        if (strcmp(login.username, "admin") == 0) {
            int opt = 1;
            char newPassword[100];
            if(admin.firstTime == 1) {
                printf("aaa");
                limparBuffer();
                printf("Parece que e a sua primeira vez a fazer login,\nnesse caso, aconcelhamos a trocar a password.\nInsira uma nova password\n-> ");
                getString(newPassword, sizeof(newPassword));
                strcpy(admin.password, newPassword);
                admin.firstTime = 0;
                saveAdminToFile(&admin);
            }
            while (opt != 0) {
                menuAdmin(&opt);
                limparBuffer();
                switch (opt) {
                    case 1: // Validar tecnico
                        printf("\nUsername do tecnico a validar: ");
                        getString(login.username, sizeof(login.username));
                        int res = validarTecnico(tecnicos, login.username);
                        if(res==1) {
                            printf("\nSucesso ao validar tecnico!");
                        } else if(res==0) {
                            printf("\nTecnico ja esta ativo!");
                        } else if(res==-1) {
                            printf("\nErro ao validar tecnico!");
                        }
                        break;
                    case 2: // Adicionar incidente
                        printf("\nNome do incidente:\n-> ");
                        getString(auxIncidente.nome, sizeof(auxIncidente.nome));
                        printf("\nTecnico responsavel:\n-> ");
                        getString(auxIncidente.tecnico_atribuido, sizeof(auxIncidente.tecnico_atribuido));
                        printf("\nSeveridade:\n-> ");
                        scanf("%i", &auxIncidente.severidade);
                        printf("\nTipo:\n-> ");
                        scanf("%i", &auxIncidente.tipo);
                        limparBuffer();

                        auxIncidente.id = getLastId(incidentes) + 1;

                        time_t t = time(NULL);
                        struct tm tm = *localtime(&t);  
                        data_incidente.dia = tm.tm_mday;
                        data_incidente.mes = tm.tm_mon + 1;
                        data_incidente.ano = tm.tm_year + 1900;

                        auxIncidente.data_criacao = data_incidente;
                        auxIncidente.estado = 0;
                        
                        addIncidente(&incidentes, auxIncidente);
                        printf("\nIncidente adicionado com sucesso!\n");
                        break;
                    case 3: // Listar incidentes
                        printIncidentes(incidentes);
                        break;
                    case 4: // Remover incidentes
                        printf("\nId do incidente a remover: ");
                        scanf("%i", &id);
                        removerIncidente(&incidentes, id);
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
                            printf("\nA sair...");
                            break;
                        case 1:
                            printIncidentes(incidentes);
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

                if (registerTecnico(login.username, login.password, &tecnicos)) {
                    printf("\nTecnico registado com sucesso!\n");
                } else {
                    printf("\nErro ao registar tecnico.\n");
                }
            } else {
                printf("\nOperacao cancelada.\n");
            }
        }
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
