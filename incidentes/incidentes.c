#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "incidentes.h"

#define INCIDENTES_PATH "dados/incidentes_list.dat"

// Funcao para inicializar a lista ligada a partir do ficheiro
NODE_INCIDENTE* initIncidentes() {
    FILE *fp = fopen(INCIDENTES_PATH, "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro 'incidentes_list.dat'!\n");
        return NULL;
    }

    NODE_INCIDENTE *head = NULL; // Cabeca da lista ligada
    NODE_INCIDENTE *current = NULL;

    INCIDENTE temp;
    int count = 0; // Contador para incidentes carregados

    while (fread(&temp, sizeof(INCIDENTE), 1, fp)) {
        // Criar um novo node
        NODE_INCIDENTE *newNode = (NODE_INCIDENTE *)malloc(sizeof(NODE_INCIDENTE));
        if (newNode == NULL) {
            printf("Erro ao alocar memória para um novo incidente!\n");
            fclose(fp);
            // Libertar memoria ja alocada
            while (head != NULL) {
                NODE_INCIDENTE *toFree = head;
                head = head->next;
                free(toFree);
            }
            return NULL;
        }

        // Copiar os dados do incidente
        newNode->incidente = temp;
        newNode->next = NULL;

        // Adicionar o node a lista ligada
        if (head == NULL) {
            head = newNode;
        } else {
            current->next = newNode;
        }
        current = newNode;
        count++;
    }

    fclose(fp);

    return head;
}

void removerIncidente(NODE_INCIDENTE **incidentes, int id) {
    NODE_INCIDENTE *incidente = *incidentes, *prev = NULL;
    while (incidente) {
        if (incidente->incidente.id == id) {
            if (prev) prev->next = incidente->next;
            else *incidentes = incidente->next;
            free(incidente);
            saveIncidentesToFile(*incidentes);
            printf("Incidente %d removido.\n", id);
            return;
        }
        prev = incidente;
        incidente = incidente->next;
    }
    printf("Incidente com id %d nao encontrado.\n", id);
}

void saveIncidentesToFile(NODE_INCIDENTE *incidentes) {
    FILE *fp = fopen("dados/incidentes.dat", "wb");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro 'incidentes.dat' para escrita!\n");
        return;
    }

    NODE_INCIDENTE *incidente = incidentes;
    while (incidente) {
        fwrite(&(incidente->incidente), sizeof(INCIDENTE), 1, fp);
        incidente = incidente->next;
    }

    fclose(fp);
    printf("\nIncidentes guardados com sucesso.");
}

void printIncidentes(NODE_INCIDENTE *incidentes) {
    while(incidentes) {
        printf("\nId: %i", incidentes->incidente.id);
        printf("\nNome: %s", incidentes->incidente.nome);
        printf("\nTecnico atribuido: %s", incidentes->incidente.tecnico_atribuido);

        //Estado
        if(incidentes->incidente.estado==0) printf("\nEstado: Nao Resolvido");
        else printf("\nEstado: Resolvido");

        // Severidade: 1, 2, 3 -> baixa, media, alta
        if(incidentes->incidente.severidade==1) printf("\nSeveridade: Baixa");
        if(incidentes->incidente.severidade==2) printf("\nSeveridade: Media");
        if(incidentes->incidente.severidade==3) printf("\nSeveridade: Alta");

        /* Tipo
            1 - Phishing
            2 - Malware
            3 - Acesso nao autorizado
            4 - Falha na conexao
        */
        if(incidentes->incidente.tipo==1) printf("\nTipo: Phishing");
        else if(incidentes->incidente.tipo==2) printf("\nTipo: Malware");
        else if(incidentes->incidente.tipo==3) printf("\nTipo: Acesso nao autorizado");
        else if(incidentes->incidente.tipo==4) printf("\nTipo: Falha na conexao");

        // Data
        printf("\nData: %i/%i/%i", incidentes->incidente.data_criacao.dia, incidentes->incidente.data_criacao.mes, incidentes->incidente.data_criacao.ano);
        printf("\n");
        incidentes = incidentes->next;
    }
}

int addIncidente(NODE_INCIDENTE **incidentes, INCIDENTE newIncidente) {
    NODE_INCIDENTE *novo = malloc(sizeof(NODE_INCIDENTE));
    if (!novo) return -1;
    
    novo->incidente = newIncidente;
    novo->next = NULL;

    if (*incidentes == NULL) {
        *incidentes = novo;
    } else {
        NODE_INCIDENTE *curr = *incidentes;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = novo;
    }
    saveIncidentesToFile(*incidentes); // Guarda logo após adicionar
    return 0;
}

int getLastId(NODE_INCIDENTE *incidentes) {
    if (incidentes == NULL) return 0; // Se a lista está vazia, começa no id 0

    NODE_INCIDENTE *curr = incidentes;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    return curr->incidente.id;
}