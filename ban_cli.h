/* 
 * File:   ban_cli.h
 * Author: Rodrigo Silva 21250068
 */

#ifndef BAN_CLI_H
#define BAN_CLI_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "util.h"

void add_cli_to_ban_file(Cliente aux, char *mot, char * nome_fich);
int search_cli_on_ban_file(int nif, char *nome_fich);
void show_ban_file(char *nome_fich);
void check_ban_file_existence(char *nome_fich);

#endif /* BAN_CLI_H */

