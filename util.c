/* 
 * File:   util.c
 * Author: Rodrigo Silva 21250068
 */

#include "util.h"

int check_nif(int num) { //verificar se tem 9 digitos o NIF
    int count = 0;
    while (num > 0) {
        num = num / 10;
        count = count + 1;
    }
    if (count != 9) {
        printf("\nO NIF tem de ter 9 digitos!\n");
        return 0;
    }
    return 1;
}

int check_file_empty(FILE *fp1) {
    int size;
    fseek(fp1, 0, SEEK_END);
    size = ftell(fp1);

    if (size == 0) {
        return 1;
    }
    rewind(fp1);
    return 0;
}

FILE * open_folder(char *nome, char *mode) {
    FILE *fp1;
    fp1 = fopen(nome, mode);
    if (fp1 == NULL) {
        printf("Não existe ficheiro %s...\n\n", nome);
    }
    return fp1;
}

Data expected_date(Data data) {
    Data aux;

    if (data.mes == 2) {
        if (data.dia >= 22 && data.dia <= 28) {
            aux.dia = (data.dia + 7) - 28;
            aux.mes = data.mes + 1;
            aux.ano = data.ano;
        } else {
            aux.dia = data.dia + 7;
            aux.mes = data.mes;
            aux.ano = data.ano;
        }
    } else {
        if (data.mes == 12) {
            if (data.dia >= 25 && data.dia <= 31) {
                aux.dia = (data.dia + 7) - 31;
                aux.mes = 1;
                aux.ano = data.ano + 1;
            } else {
                aux.dia = data.dia + 7;
                aux.mes = data.mes;
                aux.ano = data.ano;
            }
        } else {
            if (data.mes == 1 || data.mes == 3 || data.mes == 5 || data.mes == 7 || data.mes == 8 || data.mes == 10) {
                if (data.dia >= 25 && data.dia <= 31) {
                    aux.dia = (data.dia + 7) - 31;
                    aux.mes = data.mes + 1;
                    aux.ano = data.ano;
                } else {
                    aux.dia = data.dia + 7;
                    aux.mes = data.mes;
                    aux.ano = data.ano;
                }
            } else {
                if (data.dia >= 24 && data.dia <= 30) {
                    aux.dia = (data.dia + 7) - 30;
                    aux.mes = data.mes;
                    aux.ano = data.ano;
                } else {
                    aux.dia = data.dia + 7;
                    aux.mes = data.mes;
                    aux.ano = data.ano;
                }
            }
        }
    }
    return aux;
}

int dater(int x) {
    int y = 0;
    switch (x) {
        case 1: y = 0;
            break;
        case 2: y = 31;
            break;
        case 3: y = 59;
            break;
        case 4: y = 90;
            break;
        case 5: y = 120;
            break;
        case 6: y = 151;
            break;
        case 7: y = 181;
            break;
        case 8: y = 212;
            break;
        case 9: y = 243;
            break;
        case 10:y = 273;
            break;
        case 11:y = 304;
            break;
        case 12:y = 334;
            break;
        default: printf("Invalid Inputnnnn");
            exit(1);
    }
    return (y);
}

int count_day_delay(Data data_prev, Data data_f) {
    int ref, dd1, dd2, i, delaydays;
    ref = data_prev.ano;

    if (data_f.ano < data_prev.ano)
        ref = data_f.ano;

    dd1 = 0;
    dd1 = dater(data_prev.mes);

    for (i = ref; i < data_prev.ano; i++) {
        if (i % 4 == 0)
            dd1 += 1;
    }

    dd1 = dd1 + data_prev.dia + (data_prev.ano - ref)*365;
    dd2 = 0;

    for (i = ref; i < data_f.ano; i++) {
        if (i % 4 == 0)
            dd2 += 1;
    }

    dd2 = dater(data_f.mes) + dd2 + data_f.dia + ((data_f.ano - ref)*365);

    delaydays = abs(dd2 - dd1);

    if (dd2 - dd1 < 0) {
        return delaydays = 0;
    }
    return delaydays;
}

int check_dates(Data data_i, Data data_f) {
    if (data_f.ano < data_i.ano) {
        return 0;
    } else {
        if (data_f.ano == data_i.ano) {
            if (data_f.mes < data_i.mes) {
                return 0;
            } else {
                if (data_f.mes == data_i.mes) {
                    if (data_f.dia < data_i.dia) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

void cls() {
    system("pause");
    system("cls");
}
