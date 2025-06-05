#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "admin.h"

#define ADMIN_FILE "dados/admin_list.dat"

ADMIN* initAdmins() {
    FILE *fp = fopen(ADMIN_FILE, "rb");
    ADMIN *head = NULL, *tail = NULL;

    if (fp) {
        ADMIN temp;
        while (fread(&temp, sizeof(ADMIN) - sizeof(ADMIN*), 1, fp)) {
            ADMIN *newNode = malloc(sizeof(ADMIN));
            if (!newNode) break;
            memcpy(newNode, &temp, sizeof(ADMIN) - sizeof(ADMIN*));
            newNode->next = NULL;
            if (!head) head = tail = newNode;
            else { tail->next = newNode; tail = newNode; }
        }
        fclose(fp);
    }

    if (!head) {
        ADMIN *newAdmin = malloc(sizeof(ADMIN));
        strcpy(newAdmin->username, "admin");
        strcpy(newAdmin->password, "admin");
        newAdmin->firstTime = 1;
        newAdmin->next = NULL;
        head = newAdmin;
        saveAdminsToFile(head);
    }
    return head;
}

int saveAdminsToFile(ADMIN *admins) {
    FILE *fp = fopen(ADMIN_FILE, "wb");
    if (!fp) return -1;
    while (admins) {
        fwrite(admins, sizeof(ADMIN) - sizeof(ADMIN*), 1, fp);
        admins = admins->next;
    }
    fclose(fp);
    return 0;
}

ADMIN* findAdmin(ADMIN *admins, const char *username) {
    while (admins) {
        if (strcmp(admins->username, username) == 0)
            return admins;
        admins = admins->next;
    }
    return NULL;
}

int updateAdminPassword(ADMIN *admins, const char *username, const char *newPassword) {
    ADMIN *admin = findAdmin(admins, username);
    if (!admin) return 0;
    strcpy(admin->password, newPassword);
    admin->firstTime = 0;
    saveAdminsToFile(admins);
    return 1;
}

void freeAdmins(ADMIN *admins) {
    while (admins) {
        ADMIN *tmp = admins;
        admins = admins->next;
        free(tmp);
    }
}

void menuAdmin(int *opt) {
    printf("\n--- Menu Administrador ---");
    printf("\n1 - Validar Tecnico");
    printf("\n2 - Listar tecnicos");
    printf("\n3 - Adicionar incidente");
    printf("\n4 - Listar incidentes");
    printf("\n5 - Remover incidente");
    printf("\n6 - Listar incidentes por estado");
    printf("\n7 - Listar incidentes por severidade");
    printf("\n8 - Listar incidentes por tipo");
    printf("\n9 - Ordenar por severidade");
    printf("\n10 - Gerar relatorio mensal");
    printf("\n11 - Tempo medio de resolucao por tecnico");
    printf("\n12 - Filtrar por intervalo de datas");
    printf("\n0 - Sair");
    printf("\nOpcao: ");
    scanf("%d", opt);
    while (getchar() != '\n');
    printf("\n------------------------");
}