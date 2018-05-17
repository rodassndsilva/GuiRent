/* 
 * File:   aluguer.h
 * Author: Rodrigo Silva 21250068
 */

#ifndef ALUGUER_H
#define ALUGUER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "util.h"
#include "guitarras.h"
#include "cliente.h"

Aluguer * add_rent_from_file_to_node(Aluguer *aluguer, FILE *file);
void add_rent_to_cli_in_file(Cliente *cliente, char *nome_fich);
Cliente * add_rent_to_cli_in_node(Cliente *cliente, int nif, int id, Data aux_data);
void add_rent_to_file(Aluguer * aluguer, char *nome_fich);
Aluguer * add_rent_to_node(Aluguer *aluguer, Aluguer alu_aux);
int check_num_rents_of_cli(Cliente *c, int nif);
Cliente * conclude_rent_in_node(Cliente *cliente, Guitar *gui, int nif, int pos, int estado_gui, Data data_f);
void show_active_rents(Cliente *cliente, Guitar *gui, int tam);
void show_rents(Cliente *cliente, Guitar *gui, int tam);

#endif /* ALUGUER_H */

