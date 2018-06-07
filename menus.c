/* 
 * File:   menus.c
 * Author: Rodrigo Silva 21250068
 */
#include <stdio.h>
#include <stdlib.h>
#include "menus.h"

int menu() {
    int op;
    printf(" -----------------------");
    printf("\n|    1 - Clientes       |");
    printf("\n|    2 - Guitarras      |");
    printf("\n|    3 - Aluguer        |");
    printf("\n|    4 - Terminar       |");
    printf("\n -----------------------");
    do {
        printf("\nOpcao: ");
        scanf("%d", &op);
    } while (op < 1 || op > 4);
    return op;
}

int submenu1() {
    int op;
    printf(" ---------------------------------------");
    printf("\n|     1 - Adicionar Cliente             |"); //feito
    printf("\n|     2 - Remover Cliente(Ativo)        |"); //feito
    printf("\n|     3 - Dados Cliente                 |"); // feito
    printf("\n|     4 - Lista de Clientes Ativos      |"); //feito
    printf("\n|     5 - Lista de Clientes Banidos     |"); //feito
    printf("\n|     6 - Voltar Atras                  |");
    printf("\n ---------------------------------------");
    do {
        printf("\nOpcao: ");
        scanf("%d", &op);
    } while (op < 1 || op > 6);
    return op;
}

int submenu2() {
    int op;
    printf(" ---------------------------------------------------");
    printf("\n|    1 - Adicionar Guitarra                         |"); //feito
    printf("\n|    2 - Mostra Historico de Guitarras              |"); //feito
    printf("\n|    3 - Lista de Todas as Guitarras                |"); //Feito
    printf("\n|    4 - Lista das Guitarras Alugadas               |"); //feito 
    printf("\n|    5 - Voltar Atras                               |"); //feito
    printf("\n ---------------------------------------------------");
    do {
        printf("\nOpcao: ");
        scanf("%d", &op);
    } while (op < 1 || op > 5);
    return op;
}

int submenu3() {
    int op;
    printf(" -------------------------------");
    printf("\n|    1 - Criar Aluguer          |"); //Feito 
    printf("\n|    2 - Concluir Aluguer       |"); //Feito, falta a multa
    printf("\n|    3 - Lista de Alugueres     |"); //feito
    printf("\n|    4 - Voltar Atras           |");
    printf("\n -------------------------------");
    do {
        printf("\nOpcao: ");
        scanf("%d", &op);
    } while (op < 1 || op > 4);
    return op;
}