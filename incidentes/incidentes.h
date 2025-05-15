typedef struct data_incidente {
    int dia;
    int mes;
    int ano;
} DATA_INCIDENTE;

typedef struct incidente {
    char nome[100];
    char tecnico_atribuido[100];
    int estado;
    int severidade;
    int tipo;
    int id;
    DATA_INCIDENTE data_criacao;
} INCIDENTE;

typedef struct node_incidente {
    INCIDENTE incidente;
    struct node_incidente *next;
} NODE_INCIDENTE;

NODE_INCIDENTE *initIncidentes();

//Adicionar um novo incidente
void adicionarIncidente(NODE_INCIDENTE **incidentes, INCIDENTE novo);

//Remover um incidente pelo ID
void removerIncidente(NODE_INCIDENTE **incidentes, int id);

//Consultar os Incidentes
void listarIncidentesEstado(NODE_INCIDENTE *incidente, int estado);
void listarIncidentesSeveridade(NODE_INCIDENTE *incidente, int severidade);
void listarIncidentesTipo(NODE_INCIDENTE *incidente, int tipo);

//Salvar os incidentes para o ficheiro
int addIncidente(NODE_INCIDENTE *incidentes, INCIDENTE newIncidente);
void saveIncidentesToFile(NODE_INCIDENTE *incidentes);

void printIncidentes(NODE_INCIDENTE *incidentes);
int getLastId(NODE_INCIDENTE *incidentes);