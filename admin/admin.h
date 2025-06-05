/**
 * @file admin.h
 * @brief Definições e protótipos para gestão de administradores.
 */

#ifndef ADMIN_H
#define ADMIN_H

/**
 * @struct ADMIN
 * @brief Estrutura que representa um administrador.
 */
typedef struct admin {
    char username[100];
    char password[50];
    int firstTime;
    struct admin *next;
} ADMIN;

// Protótipos das funções
ADMIN* initAdmins();
void freeAdmins(ADMIN *head);
ADMIN* findAdmin(ADMIN *admins, const char *username);
int saveAdminsToFile(ADMIN *admins);
int updateAdminPassword(ADMIN *admins, const char *username, const char *newPassword);
void menuAdmin(int *opt);

#endif