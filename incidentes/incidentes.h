#ifndef INCIDENTES_H
#define INCIDENTES_H

typedef struct data_incidente {
    int dia;
    int mes;
    int ano;
} DATA_INCIDENTE;

typedef struct incidente {
    char nome[100];
    char tecnico_atribuido[100];
    int estado; // 0=novo, 1=em analise, 2= resolvido
    int severidade; // 1=baixa, 2=media, 3=alta
    int tipo; // 1=Phishing, 2=Malware, 3=Acesso nao autorizado, 4=Falha conexao
    int id;
    DATA_INCIDENTE data_criacao;
    DATA_INCIDENTE data_resolucao;
    int tempo_estimado; // em dias
    char historico[10][200]; // comentários/ações
    int historico_count;
    char ferramentas[10][50];
    int ferramentas_count;
} INCIDENTE;

typedef struct node_incidente {
    INCIDENTE incidente;
    struct node_incidente *next;
} NODE_INCIDENTE;

NODE_INCIDENTE *initIncidentes();
int addIncidente(NODE_INCIDENTE **incidentes, INCIDENTE newIncidente);
void removerIncidente(NODE_INCIDENTE **incidentes, int id);
void saveIncidentesToFile(NODE_INCIDENTE *incidentes);

void printIncidentes(NODE_INCIDENTE *incidentes, char username[], int tecnicoSpecific);
void printIncidentesPorEstado(NODE_INCIDENTE *inc, int estado);
void printIncidentesPorSeveridade(NODE_INCIDENTE *inc, int severidade);
void printIncidentesPorTipo(NODE_INCIDENTE *inc, int tipo);
void printIncidentesPorIntervalo(NODE_INCIDENTE *inc, DATA_INCIDENTE inicio, DATA_INCIDENTE fim);

NODE_INCIDENTE* ordenarPorSeveridade(NODE_INCIDENTE *head);
NODE_INCIDENTE* ordenarPorData(NODE_INCIDENTE *head);
NODE_INCIDENTE* ordenarPorTecnico(NODE_INCIDENTE *head);

void gerarRelatorioMensal(NODE_INCIDENTE *inc, int mes, int ano, const char *ficheiro);
void tempoMedioResolucaoPorTecnico(NODE_INCIDENTE *inc, char *tecnico);

void adicionarComentario(NODE_INCIDENTE *incidentes, int id, const char *comentario);
void adicionarFerramenta(NODE_INCIDENTE *incidentes, int id, const char *ferramenta);
void delegarIncidente(NODE_INCIDENTE *incidentes, int id, const char *novo_tecnico, const char *motivo);
void atualizarEstadoIncidente(NODE_INCIDENTE *incidentes, int id, int novo_estado, DATA_INCIDENTE data_resolucao);

int getLastId(NODE_INCIDENTE *incidentes);

int calculaDias(DATA_INCIDENTE inicio, DATA_INCIDENTE fim);

#endif