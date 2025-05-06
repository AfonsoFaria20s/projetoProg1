typedef struct {
    char user[100];
    char password[50];
} TECNICO;

typedef struct node {
    TECNICO tecnico;
    struct node *next;
} NODE;

NODE* initTecnicos();