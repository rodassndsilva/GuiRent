/* 
 * File:   guitarras.h
 * Author: Rodrigo Silva 21250068
 */

#ifndef GUITARRAS_H
#define GUITARRAS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "util.h"

void add_gui_file(Guitar *gui, int pos, char *nome_fich);
Guitar * add_gui(Guitar gui[], Guitar aux_2, int *tam);
int check_gui_availability_by_id(Guitar *gui, int id, int pos);
int check_if_id_exist_on_cli(Cliente *cliente, int nif, int id);
int count_damaged_gui(Cliente *cliente, int nif);
Guitar * create_vector(Guitar *gui, int *tam);
Guitar get_gui(Guitar *gui, int *tam, Guitar aux);
void gui_rent_history(int id, Cliente *cliente);
void put_gui_as_rented_in_file(Guitar *gui, int tam, char *nome_fich);
Guitar * put_gui_as_rented_in_vector(Guitar *gui, int tam, int id);
Guitar * read_gui_from_file(Guitar *gui, int *tam, char *nome_fich);
int search_gui_with_id(Guitar *gui, int id, int pos);
void show_gui_available(Guitar *gui, int tam);
void show_gui(Guitar *v, int tam);
void show_rented_gui(Guitar *gui, Cliente *cli, int *tam);

#endif /* GUITARRAS_H */

