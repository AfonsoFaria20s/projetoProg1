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
} NODE;  /// FALTA MUDAR O RESTO PARA NODE_TECNICO

NODE* initTecnicos();
int isTecnicoRegistered(const char *username, NODE* tecnicos);
int registerTecnico(const char *username, const char *password, NODE** tecnicos);
void saveTecnicosToFile(NODE *tecnicos);
void freeTecnicos(NODE *head);
int verifyTecnico(char *username, char *password, NODE *tecnicos);
void printTecnicos(NODE *tecnicos);
void menuTecnico(int *opt);

#endif
