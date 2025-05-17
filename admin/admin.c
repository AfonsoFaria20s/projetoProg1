#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "admin.h"
#include "../tecnico/tecnico.h"
#include "../incidentes/incidentes.h"

// Inicializa o admin (carrega do ficheiro ou cria default)
ADMIN initAdmin() {
    FILE *fp = fopen("dados/admin_list.dat", "rb");
    ADMIN admin;

    if (fp != NULL) {
        fread(&admin, sizeof(ADMIN), 1, fp);
        fclose(fp);
    } else {
        // Se não existir, cria admin default
        strcpy(admin.user, "admin");
        strcpy(admin.password, "admin");
        admin.firstTime = 1;
        saveAdminToFile(&admin);
    }
    return admin;
}

// Valida um técnico pelo username
int validarTecnico(NODE_TECNICOS *tecnicos, const char *username) {
    NODE_TECNICOS *node = tecnicos;
    while (node) {
        if (strcmp(node->tecnico.user, username) == 0) {
            if(node->tecnico.isAtivo == 1) {
                return 0; // Já está ativo
            }
            node->tecnico.isAtivo = 1;
            printf("Tecnico %s validado!\n", username);
            saveTecnicosToFile(tecnicos);
            return 1; // Validado com sucesso
        }
        node = node->next;
    }
    return -1; // Não encontrado
}

// Guarda o admin no ficheiro
int saveAdminToFile(ADMIN *admin) {
    FILE *fp = fopen("dados/admin_list.dat", "wb");
    if (fp == NULL) {
        printf("\nErro ao abrir o ficheiro 'admin_list.dat'!\n");
        return -1;
    }
    fwrite(admin, sizeof(ADMIN), 1, fp); // <-- CORRIGIDO
    fclose(fp);
    printf("\nAdmin salvo.");
    return 0;
}

// Menu do administrador
void menuAdmin(int *opt) {
    printf("\n--- Menu Administrador ---");
    printf("\n1 - Validar Tecnico");
    printf("\n2 - Adicionar incidente");
    printf("\n3 - Listar incidentes");
    printf("\n4 - Remover incidente");
    printf("\n0 - Sair");
    printf("\nOpcao: ");
    scanf("%d", opt);
    while (getchar() != '\n'); // Limpa o buffer
    printf("\n------------------------");
}