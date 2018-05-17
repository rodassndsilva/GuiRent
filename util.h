/* 
 * File:   util.h
 * Author: Rodrigo Silva 21250068
 */

#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include "structs.h"

int check_dates(Data data_i, Data data_f);
int check_file_empty(FILE *fp1);
int check_nif(int num);
int count_day_delay(Data data_prev, Data data_f);
int dater(int x);
Data expected_date(Data data);
FILE * open_folder(char *nome, char *mode);

#endif /* UTIL_H */

