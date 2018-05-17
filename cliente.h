/* 
 * File:   cliente.h
 * Author: Rodrigo Silva 21250068
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "aluguer.h"
#include "util.h"
#include "structs.h"

char *search_name_with_nif(Cliente * cliente, int nif);
Cliente * add_cli_file_to_node(Cliente *cliente, Aluguer *aluguer, char *nome);
void add_cli_file(Cliente aux, char *nome_fich);
Cliente * add_cli_with_rent_node(Cliente *cliente, Aluguer *aluguer, Cliente cli_aux, FILE * file);
Cliente * add_one_cli_node(Cliente *cliente, Cliente cli_aux);
int check_if_cli_active(Cliente * cliente, int nif);
void delete_cli_file(Cliente * cliente, char *nome_fich);
Cliente * delete_cli_node(Cliente *cliente, int nif);
Data search_inicial_date_cli(Cliente *cliente, int nif, int id);
void show_active_cli(Cliente * cliente);
void show_cli_data(Cliente * cliente);

#endif /* CLIENTE_H */

