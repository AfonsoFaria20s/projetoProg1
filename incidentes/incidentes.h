/**
 * @file incidentes.h
 * @brief Definições e protótipos para gestão de incidentes.
 */

#ifndef INCIDENTES_H
#define INCIDENTES_H

/**
 * @struct DATA_INCIDENTE
 * @brief Estrutura para armazenar datas (dia, mês, ano).
 */
typedef struct {
    int dia;
    int mes;
    int ano;
} DATA_INCIDENTE;

/**
 * @struct INCIDENTE
 * @brief Estrutura que representa um incidente.
 */
typedef struct {
    int id;
    char nome[100];
    char tecnico_atribuido[100];
    int severidade;
    int tipo;
    int estado;
    DATA_INCIDENTE data_criacao;
    DATA_INCIDENTE data_resolucao;
    char historico[10][200]; ///< Histórico de comentários/ações
    int historico_count;
    char ferramentas[10][50]; ///< Ferramentas usadas
    int ferramentas_count;
} INCIDENTE;

/**
 * @struct NODE_INCIDENTE
 * @brief Nó da lista ligada de incidentes.
 */
typedef struct node_incidente {
    INCIDENTE incidente;
    struct node_incidente *next;
} NODE_INCIDENTE;

// Protótipos das funções
NODE_INCIDENTE* initIncidentes();
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
int getLastId(NODE_INCIDENTE *incidentes);
int calculaDias(DATA_INCIDENTE inicio, DATA_INCIDENTE fim);
void atualizarEstadoIncidente(NODE_INCIDENTE *incidentes, int id, int novo_estado, DATA_INCIDENTE data_resolucao);

#endif