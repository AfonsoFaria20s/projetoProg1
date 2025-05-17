#ifndef ADMIN_H
#define ADMIN_H

typedef struct {
    char user[100];
    char password[100];
    int firstTime;
} ADMIN;

#include "../tecnico/tecnico.h"

// Inicializa o admin (carrega do ficheiro ou cria default)
ADMIN initAdmin();

// Guarda o admin no ficheiro
int saveAdminToFile(ADMIN *admin);

// Valida um técnico pelo username
int validarTecnico(NODE_TECNICOS *tecnicos, const char *username);

// Menu do administrador
void menuAdmin(int *opt);

#endif