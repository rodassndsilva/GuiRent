/* 
 * File:   structs.h
 * Author: Rodrigo Silva 21250068
 */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct ban {
    char nome[50];
    int nif; //unico
    char mot[100];
} Ban;

typedef struct data {
    int dia, mes, ano;
} Data;

typedef struct aluguer {
    int id; //id da guitarra
    int estado; // (0 – a decorrer / 1 – entregue /  2 – entregue danificada)
    Data data_i;
    Data data_f;
    struct aluguer *prox;
} Aluguer;

typedef struct cliente {
    char nome[50];
    int nif; //unico
    int cont_a; // cont de numero de alugueres
    int cont_estado; //cont guitarras danificadas
    struct aluguer *alu;
    struct cliente *prox;
} Cliente;
#define DEFAULT_EMPLOYEE { 000, 0, 0, 0, "none"}

typedef struct guitar {
    int id;
    float preco_dia; //preço por dia de aluguer
    float preco; //preço da guitarra
    int estado; // (0 - disponível / 1 - alugada / 2 - danificada)  
    char nome[50];
} Guitar;

#endif /* STRUCTS_H */

