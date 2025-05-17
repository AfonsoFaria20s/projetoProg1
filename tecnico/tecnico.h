#ifndef TECNICO_H
#define TECNICO_H

typedef struct {
    char user[100];
    char password[50];
    int isAtivo;    // 0 = não validado, 1 = validado
} TECNICO;

typedef struct node {
    TECNICO tecnico;
    struct node *next;
} NODE_TECNICOS;  /// FALTA MUDAR O RESTO PARA NODE_TECNICO

NODE_TECNICOS* initTecnicos();
int isTecnicoRegistered(const char *username, NODE_TECNICOS* tecnicos);
int registerTecnico(const char *username, const char *password, NODE_TECNICOS** tecnicos);
void saveTecnicosToFile(NODE_TECNICOS *tecnicos);
void freeTecnicos(NODE_TECNICOS *head);
int verifyTecnico(char *username, char *password, NODE_TECNICOS *tecnicos);
void printTecnicos(NODE_TECNICOS *tecnicos);
void menuTecnico(int *opt);

#endif
