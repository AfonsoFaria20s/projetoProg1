#ifndef TECNICO_H
#define TECNICO_H

typedef struct tecnico {
    char user[100];
    char password[50];
    int isAtivo;
} TECNICO;

typedef struct node_tecnico {
    TECNICO tecnico;
    struct node_tecnico *next;
} NODE_TECNICOS;

NODE_TECNICOS* initTecnicos();
int saveTecnicosToFile(NODE_TECNICOS *tecnicos);
int tecnicoExists(const char *username, NODE_TECNICOS *tecnicos);
int registerTecnico(const char *username, const char *password, NODE_TECNICOS **tecnicos);
int validTecnicoLogin(char *username, char *password, NODE_TECNICOS *tecnicos);
void freeTecnicos(NODE_TECNICOS *head);
void menuTecnico(int *opt);
int ativarTecnico(NODE_TECNICOS *tecnicos, char username[]);
void listarTecnicos(NODE_TECNICOS *tecnicos);

#endif
