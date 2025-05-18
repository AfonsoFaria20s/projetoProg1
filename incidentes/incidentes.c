#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "incidentes.h"

#define INCIDENTES_PATH "dados/incidentes.dat"

// Inicializa a lista ligada de incidentes a partir do ficheiro binário
NODE_INCIDENTE* initIncidentes() {
    FILE *fp = fopen(INCIDENTES_PATH, "rb");
    if (fp == NULL) {
        return NULL;
    }

    NODE_INCIDENTE *head = NULL;
    NODE_INCIDENTE *current = NULL;
    INCIDENTE temp;

    while (fread(&temp, sizeof(INCIDENTE), 1, fp)) {
        NODE_INCIDENTE *newNode = (NODE_INCIDENTE *)malloc(sizeof(NODE_INCIDENTE));
        if (newNode == NULL) {
            fclose(fp);
            while (head != NULL) {
                NODE_INCIDENTE *toFree = head;
                head = head->next;
                free(toFree);
            }
            return NULL;
        }
        newNode->incidente = temp;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            current->next = newNode;
        }
        current = newNode;
    }

    fclose(fp);
    return head;
}

// Adiciona um novo incidente à lista ligada
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
    saveIncidentesToFile(*incidentes);
    return 0;
}

// Remove um incidente pelo id
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

// Guarda a lista de incidentes no ficheiro binário
void saveIncidentesToFile(NODE_INCIDENTE *incidentes) {
    FILE *fp = fopen(INCIDENTES_PATH, "wb");
    if (fp == NULL) return;

    NODE_INCIDENTE *incidente = incidentes;
    while (incidente) {
        fwrite(&(incidente->incidente), sizeof(INCIDENTE), 1, fp);
        incidente = incidente->next;
    }
    fclose(fp);
}

// Listagem e filtragem
void printIncidentes(NODE_INCIDENTE *incidentes, char username[], int tecnicoSpecific) {
    while (incidentes) {
        if (tecnicoSpecific == 1 && strcmp(incidentes->incidente.tecnico_atribuido, username) != 0) {
            incidentes = incidentes->next;
            continue;
        }
        printf("\nId: %i", incidentes->incidente.id);
        printf("\nNome: %s", incidentes->incidente.nome);
        printf("\nTecnico atribuido: %s", incidentes->incidente.tecnico_atribuido);
        printf("\nEstado: %d", incidentes->incidente.estado);
        printf("\nSeveridade: %d", incidentes->incidente.severidade);
        printf("\nTipo: %d", incidentes->incidente.tipo);
        printf("\nData: %i/%i/%i", incidentes->incidente.data_criacao.dia, incidentes->incidente.data_criacao.mes, incidentes->incidente.data_criacao.ano);
        printf("\n");
        incidentes = incidentes->next;
    }
}

void printIncidentesPorEstado(NODE_INCIDENTE *inc, int estado) {
    while (inc) {
        if (inc->incidente.estado == estado)
            printIncidentes(inc, "", 0);
        inc = inc->next;
    }
}
void printIncidentesPorSeveridade(NODE_INCIDENTE *inc, int severidade) {
    while (inc) {
        if (inc->incidente.severidade == severidade)
            printIncidentes(inc, "", 0);
        inc = inc->next;
    }
}
void printIncidentesPorTipo(NODE_INCIDENTE *inc, int tipo) {
    while (inc) {
        if (inc->incidente.tipo == tipo)
            printIncidentes(inc, "", 0);
        inc = inc->next;
    }
}
void printIncidentesPorIntervalo(NODE_INCIDENTE *inc, DATA_INCIDENTE inicio, DATA_INCIDENTE fim) {
    while (inc) {
        if (calculaDias(inicio, inc->incidente.data_criacao) >= 0 &&
            calculaDias(inc->incidente.data_criacao, fim) >= 0)
            printIncidentes(inc, "", 0);
        inc = inc->next;
    }
}

// Ordenação (bubble sort simples, troca INCIDENTE)
NODE_INCIDENTE* ordenarPorSeveridade(NODE_INCIDENTE *head) {
    int trocado;
    NODE_INCIDENTE *ptr1;
    NODE_INCIDENTE *lptr = NULL;
    if (head == NULL) return NULL;
    do {
        trocado = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->incidente.severidade > ptr1->next->incidente.severidade) {
                INCIDENTE temp = ptr1->incidente;
                ptr1->incidente = ptr1->next->incidente;
                ptr1->next->incidente = temp;
                trocado = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (trocado);
    return head;
}
NODE_INCIDENTE* ordenarPorData(NODE_INCIDENTE *head) {
    int trocado;
    NODE_INCIDENTE *ptr1;
    NODE_INCIDENTE *lptr = NULL;
    if (head == NULL) return NULL;
    do {
        trocado = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (calculaDias(ptr1->incidente.data_criacao, ptr1->next->incidente.data_criacao) > 0) {
                INCIDENTE temp = ptr1->incidente;
                ptr1->incidente = ptr1->next->incidente;
                ptr1->next->incidente = temp;
                trocado = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (trocado);
    return head;
}
NODE_INCIDENTE* ordenarPorTecnico(NODE_INCIDENTE *head) {
    int trocado;
    NODE_INCIDENTE *ptr1;
    NODE_INCIDENTE *lptr = NULL;
    if (head == NULL) return NULL;
    do {
        trocado = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->incidente.tecnico_atribuido, ptr1->next->incidente.tecnico_atribuido) > 0) {
                INCIDENTE temp = ptr1->incidente;
                ptr1->incidente = ptr1->next->incidente;
                ptr1->next->incidente = temp;
                trocado = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (trocado);
    return head;
}

// Relatório mensal
void gerarRelatorioMensal(NODE_INCIDENTE *inc, int mes, int ano, const char *ficheiro) {
    FILE *fp = fopen(ficheiro, "w");
    while (inc) {
        if (inc->incidente.data_criacao.mes == mes && inc->incidente.data_criacao.ano == ano)
            fprintf(fp, "Id: %d, Nome: %s, Estado: %d\n", inc->incidente.id, inc->incidente.nome, inc->incidente.estado);
        inc = inc->next;
    }
    fclose(fp);
    printf("Relatorio gerado!\n");
}

// Tempo médio de resolução por técnico
void tempoMedioResolucaoPorTecnico(NODE_INCIDENTE *inc, char *tecnico) {
    int total = 0, count = 0;
    while (inc) {
        if (strcmp(inc->incidente.tecnico_atribuido, tecnico) == 0 && inc->incidente.estado == 2) {
            int dias = calculaDias(inc->incidente.data_criacao, inc->incidente.data_resolucao);
            total += dias;
            count++;
        }
        inc = inc->next;
    }
    if (count > 0)
        printf("Tempo medio: %.2f dias\n", (float)total/count);
    else
        printf("Nenhum incidente resolvido por esse tecnico.\n");
}

// Adicionar comentário/ação
void adicionarComentario(NODE_INCIDENTE *incidentes, int id, const char *comentario) {
    while (incidentes) {
        if (incidentes->incidente.id == id) {
            if (incidentes->incidente.historico_count < 10) {
                strncpy(incidentes->incidente.historico[incidentes->incidente.historico_count], comentario, 199);
                incidentes->incidente.historico[incidentes->incidente.historico_count][199] = '\0';
                incidentes->incidente.historico_count++;
                saveIncidentesToFile(incidentes);
            }
            break;
        }
        incidentes = incidentes->next;
    }
}

// Adicionar ferramenta usada
void adicionarFerramenta(NODE_INCIDENTE *incidentes, int id, const char *ferramenta) {
    while (incidentes) {
        if (incidentes->incidente.id == id) {
            if (incidentes->incidente.ferramentas_count < 10) {
                strncpy(incidentes->incidente.ferramentas[incidentes->incidente.ferramentas_count], ferramenta, 49);
                incidentes->incidente.ferramentas[incidentes->incidente.ferramentas_count][49] = '\0';
                incidentes->incidente.ferramentas_count++;
                saveIncidentesToFile(incidentes);
            }
            break;
        }
        incidentes = incidentes->next;
    }
}

// Delegar incidente
void delegarIncidente(NODE_INCIDENTE *incidentes, int id, const char *novo_tecnico, const char *motivo) {
    while (incidentes) {
        if (incidentes->incidente.id == id) {
            strncpy(incidentes->incidente.tecnico_atribuido, novo_tecnico, 99);
            incidentes->incidente.tecnico_atribuido[99] = '\0';
            char comentario[200];
            snprintf(comentario, 200, "Incidente delegado para %s. Motivo: %s", novo_tecnico, motivo);
            adicionarComentario(incidentes, id, comentario);
            saveIncidentesToFile(incidentes);
            break;
        }
        incidentes = incidentes->next;
    }
}

// Obter último id
int getLastId(NODE_INCIDENTE *incidentes) {
    if (incidentes == NULL) return 0;
    NODE_INCIDENTE *curr = incidentes;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    return curr->incidente.id;
}

// Calcula diferença de dias entre duas datas (simples, não considera meses diferentes corretamente)
int calculaDias(DATA_INCIDENTE inicio, DATA_INCIDENTE fim) {
    return (fim.ano - inicio.ano) * 365 + (fim.mes - inicio.mes) * 30 + (fim.dia - inicio.dia);
}

void atualizarEstadoIncidente(NODE_INCIDENTE *incidentes, int id, int novo_estado, DATA_INCIDENTE data_resolucao) {
    while (incidentes) {
        if (incidentes->incidente.id == id) {
            incidentes->incidente.estado = novo_estado;
            if (novo_estado == 2) // resolvido
                incidentes->incidente.data_resolucao = data_resolucao;
            saveIncidentesToFile(incidentes);
            break;
        }
        incidentes = incidentes->next;
    }
}