#include "incidentes/incidentes.h"
#include "tecnico/tecnico.h"
#include "admin/admin.h"
#include "utils/utils.h"
#include <stdio.h>
#include <string.h>
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
    ADMIN *admins = initAdmins();
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

        // ADMIN
        ADMIN *admin = findAdmin(admins, login.username);
        if (admin) {
            int opt = 1;
            if (admin->firstTime == 1) {
                printf("Primeiro login, altere a password: ");
                getString(login.password, sizeof(login.password));
                updateAdminPassword(admins, login.username, login.password);
                printf("Password alterada!\n");
            }
            while (opt != 0) {
                menuAdmin(&opt);
                switch (opt) {
                    case 1: // Validar tecnico
                        printf("\nUsername do tecnico a validar: ");
                        getString(login.username, sizeof(login.username));
                        int res = ativarTecnico(tecnicos, login.username);
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
                        printIncidentes(incidentes, login.username, 0);
                        break;
                    case 4: // Remover incidentes
                        printf("\nId do incidente a remover: ");
                        scanf("%i", &id);
                        removerIncidente(&incidentes, id);
                        limparBuffer();
                        break;
                    case 5: // Listar por estado
                        printf("Estado (0=novo, 1=em analise, 2= resolvido): ");
                        int estado; scanf("%d", &estado); limparBuffer();
                        printIncidentesPorEstado(incidentes, estado);
                        break;
                    case 6: // Listar por severidade
                        printf("Severidade (1=baixa, 2=media, 3=alta): ");
                        int sev; scanf("%d", &sev); limparBuffer();
                        printIncidentesPorSeveridade(incidentes, sev);
                        break;
                    case 7: // Listar por tipo
                        printf("Tipo (1=Phishing, 2=Malware, 3=Acesso nao autorizado, 4=Falha conexao): ");
                        int tipo; scanf("%d", &tipo); limparBuffer();
                        printIncidentesPorTipo(incidentes, tipo);
                        break;
                    case 8: // Ordenar por severidade
                        incidentes = ordenarPorSeveridade(incidentes);
                        printf("Incidentes ordenados por severidade.\n");
                        break;
                    case 9: // Gerar relatório mensal
                        printf("Mes: "); int mes; scanf("%d", &mes);
                        printf("Ano: "); int ano; scanf("%d", &ano); limparBuffer();
                        gerarRelatorioMensal(incidentes, mes, ano, "relatorio.txt");
                        break;
                    case 10: // Tempo médio de resolução por técnico
                        printf("Username do tecnico: ");
                        char tecnico[100]; getString(tecnico, sizeof(tecnico));
                        tempoMedioResolucaoPorTecnico(incidentes, tecnico);
                        break;
                    case 11: // Filtrar por intervalo de datas
                        {
                            DATA_INCIDENTE inicio, fim;
                        printf("Data inicio (dd mm aaaa): ");
                        scanf("%d %d %d", &inicio.dia, &inicio.mes, &inicio.ano);
                        printf("Data fim (dd mm aaaa): ");
                        scanf("%d %d %d", &fim.dia, &fim.mes, &fim.ano); limparBuffer();
                        printIncidentesPorIntervalo(incidentes, inicio, fim);
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
        else if (tecnicoExists(login.username, tecnicos)) {
            printf("Password: ");
            fgets(login.password, sizeof(login.password), stdin);
            login.password[strcspn(login.password, "\n")] = '\0';
            if (validTecnicoLogin(login.username, login.password, tecnicos)) {
                int opt = 1;
                printf("\nBem-vindo, %s!\n", login.username);
                while (opt != 0) {
                    menuTecnico(&opt);
                    switch (opt) {
                        case 1: // Visualizar incidentes atribuídos
                            printIncidentes(incidentes, login.username, 1);
                            break;
                        case 2: // Atualizar estado de incidente
                            printf("Id do incidente: ");
                            int id; scanf("%d", &id); limparBuffer();
                            printf("Novo estado (0=novo, 1=em analise, 2= resolvido): ");
                            int novo_estado; scanf("%d", &novo_estado); limparBuffer();
                            DATA_INCIDENTE data_resolucao = {0,0,0};
                            if (novo_estado == 2) {
                                time_t t = time(NULL);
                                struct tm tm = *localtime(&t);
                                data_resolucao.dia = tm.tm_mday;
                                data_resolucao.mes = tm.tm_mon + 1;
                                data_resolucao.ano = tm.tm_year + 1900;
                            }
                            atualizarEstadoIncidente(incidentes, id, novo_estado, data_resolucao);
                            break;
                        case 3: // Adicionar comentário/ação
                            printf("Id do incidente: ");
                            scanf("%d", &id); limparBuffer();
                            printf("Comentario/acao: ");
                            char comentario[200]; getString(comentario, sizeof(comentario));
                            adicionarComentario(incidentes, id, comentario);
                            break;
                        case 4: // Delegar incidente
                            printf("Id do incidente: ");
                            scanf("%d", &id); limparBuffer();
                            printf("Novo tecnico: ");
                            char novo_tecnico[100]; getString(novo_tecnico, sizeof(novo_tecnico));
                            printf("Motivo: ");
                            char motivo[200]; getString(motivo, sizeof(motivo));
                            delegarIncidente(incidentes, id, novo_tecnico, motivo);
                            break;
                        case 5: // Registar ferramenta usada
                            printf("Id do incidente: ");
                            scanf("%d", &id); limparBuffer();
                            printf("Ferramenta: ");
                            char ferramenta[50]; getString(ferramenta, sizeof(ferramenta));
                            adicionarFerramenta(incidentes, id, ferramenta);
                            break;
                        case 6: // Consultar histórico dos seus incidentes resolvidos
                            {
                                NODE_INCIDENTE *tmp = incidentes;
                                while (tmp) {
                                    if (strcmp(tmp->incidente.tecnico_atribuido, login.username) == 0 && tmp->incidente.estado == 2) {
                                        printIncidentes(tmp, login.username, 1);
                                        for (int i = 0; i < tmp->incidente.historico_count; i++)
                                            printf(" - %s\n", tmp->incidente.historico[i]);
                                    }
                                    tmp = tmp->next;
                                }
                            }
                            break;
                        case 0:
                            printf("A sair do menu tecnico...\n");
                            break;
                        default:
                            printf("Opção inválida!\n");
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
    freeAdmins(admins);
    return 0;
}
