/* 
 * File:   menus.c
 * Author: Rodrigo Silva 21250068
 */
#include <stdio.h>
#include <stdlib.h>
#include "menus.h"

int menu() {
    int op;
    printf("1 - Clientes");
    printf("\n2 - Guitarras");
    printf("\n3 - Aluguer");
    printf("\n4 - Terminar");
    do {
        printf("\nOpcao: ");
        scanf("%d", &op);
    } while (op < 1 || op > 4);
    return op;
}

int submenu1() {
    int op;
    printf("1 - Adicionar Cliente"); //feito
    printf("\n2 - Remover Cliente(Ativo)"); //feito
    printf("\n3 - Dados Cliente"); // feito
    printf("\n4 - Lista de Clientes Ativos"); //feito
    printf("\n5 - Lista de Clientes Banidos"); //feito
    printf("\n6 - Voltar Atras");
    do {
        printf("\nOpcao: ");
        scanf("%d", &op);
    } while (op < 1 || op > 6);
    return op;
}

int submenu2() {
    int op;
    printf("1 - Adicionar Guitarra"); //feito
    printf("\n2 - Mostra Historico de Guitarras"); //feito
    printf("\n3 - Lista de Todas as Guitarras"); //Feito
    printf("\n4 - Lista das Guitarras Alugadas"); //feito 
    printf("\n5 - Voltar Atras"); //feito
    do {
        printf("\nOpcao: ");
        scanf("%d", &op);
    } while (op < 1 || op > 5);
    return op;
}

int submenu3() {
    int op;
    //system("cls");
    printf("1 - Criar Aluguer"); //Feito 
    printf("\n2 - Concluir Aluguer"); //Feito
    printf("\n3 - Lista de Alugueres"); //feito
    printf("\n4 - Voltar Atras");
    do {
        printf("\nOpcao: ");
        scanf("%d", &op);
    } while (op < 1 || op > 4);
    return op;
}