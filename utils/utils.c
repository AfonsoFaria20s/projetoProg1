/**
 * @file utils.c
 * @brief Implementação de funções utilitárias.
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

/**
 * @brief Limpa o buffer do stdin para evitar problemas de leitura.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Lê uma string do stdin de forma segura.
 * @param str Ponteiro para o buffer de destino.
 * @param size Tamanho máximo do buffer.
 */
void getString(char *str, int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}