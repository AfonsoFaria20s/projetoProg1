typedef struct data_incidente {
    int dia;
    int mes;
    int ano;
} DATA_INCIDENTE;

typedef struct incidente {
    char tecnico_atribuido[100];
    int estado;
    int severidade;
    int tipo;
    DATA_INCIDENTE data;
} INCIDENTE;

typedef struct node_incidente {
    INCIDENTE incidente;
    struct node_incidente *next;
} NODE_INCIDENTE;