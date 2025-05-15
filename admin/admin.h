#ifndef ADMIN_H
#define ADMIN_H

#include "../tecnico/tecnico.h"

typedef struct {
    char user[100];
    char password[50];
   
} ADMIN;

typedef struct node_admin {
    ADMIN admin;
    struct node_admin *next;
} NODE_ADMIN;

// Inicializa lista de admins
NODE_ADMIN* initAdmins();

// Valida técnico (ativa técnico registado)
void validarTecnico(NODE *tecnicos, const char *username);

// Menu do administrador
void menuAdmin(NODE *tecnicos); // Nao sei se é incidente ou incidentes








#endif
