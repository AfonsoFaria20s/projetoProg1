/**
 * @file tecnico.h
 * @brief Definições e protótipos para gestão de técnicos.
 */

#ifndef TECNICO_H
#define TECNICO_H

/**
 * @struct TECNICO
 * @brief Estrutura que representa um técnico.
 */
typedef struct {
    char user[100];
    char password[50];
    int isAtivo;
} TECNICO;

/**
 * @struct NODE_TECNICOS
 * @brief Nó da lista ligada de técnicos.
 */
typedef struct node_tecnicos {
    TECNICO tecnico;
    struct node_tecnicos *next;
} NODE_TECNICOS;

// Protótipos das funções
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
