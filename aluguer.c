/* 
 * File:   aluguer.h
 * Author: Rodrigo Silva 21250068
 */

#include "aluguer.h"

Aluguer * add_rent_from_file_to_node(Aluguer *aluguer, FILE *file) {
    Aluguer aux;

    char buf[150];
    while (fgets(buf, sizeof (buf), file)) {
        if (strcmp(buf, "\n") == 0 || strcmp(buf, " ") == 0) {
            return aluguer;
        }

        if (sscanf(buf, "%d %d %d %d %d %d %d %d",
                &aux.id, &aux.estado,
                &aux.data_i.dia, &aux.data_i.mes,
                &aux.data_i.ano, &aux.data_f.dia,
                &aux.data_f.mes, &aux.data_f.ano) != 8) {
            aux.data_f.dia = 0;
            aux.data_f.mes = 0;
            aux.data_f.ano = 0;
        }
        aluguer = add_rent_to_node(aluguer, aux);
    }
    return aluguer;
}

void add_rent_to_cli_in_file(Cliente *cliente, char *nome_fich) {
    FILE *f;
    Cliente *aux = cliente;
    Cliente aux_2;

    remove(nome_fich);

    if ((f = open_folder(nome_fich, "w")) == NULL) {
        fclose(f);
        return;
    }
    while (aux) {

        aux_2.nif = aux->nif;
        aux_2.cont_a = aux->cont_a;
        strcpy(aux_2.nome, aux->nome);

        add_cli_file(aux_2, nome_fich);

        Aluguer *aluguer = aux->alu;

        while (aluguer) {
            add_rent_to_file(aluguer, nome_fich);
            aluguer = aluguer->prox;
        }
        if (aluguer != NULL) {
            fseek(f, 0, SEEK_END);
            fprintf(f, "\n");
        }
        aux = aux->prox;
    }

    printf("Aluguer adicionado corretamente!\n");
    fclose(f);
}

int check_num_rents_of_cli(Cliente *c, int nif) {
    Cliente *aux = c;
    int cont = 0;
    while (aux) {
        if (nif == aux->nif) {
            Aluguer *a = aux->alu;
            while (a) {
                if (a->estado == 0) {
                    cont++;
                }
                a = a->prox;
            }
            break;
        }
        aux = aux->prox;
    }
    return cont;
}

Cliente * add_rent_to_cli_in_node(Cliente *cliente, int nif, int id, Data aux_data) {
    Aluguer aux_2;
    Cliente *aux = cliente;
    
    if (aux == NULL)
        return NULL;


    while (aux) {
        if (nif == aux->nif) {

            aux->cont_a++;
            aux_2.id = id;
            aux_2.estado = 0;
            aux_2.data_i = aux_data;
            aux_2.data_f.dia = 0;
            aux_2.data_f.mes = 0;
            aux_2.data_f.ano = 0;

            aux->alu = add_rent_to_node(aux->alu, aux_2);
        }
        aux = aux->prox;
    }

    return cliente;
}

Aluguer * add_rent_to_node(Aluguer *aluguer, Aluguer alu_aux) {
    Aluguer *new = (Aluguer*) malloc(sizeof (Aluguer)), *aux;

    if (new == NULL) {
        printf("Erro na alocacao de memoria\n\n");
        return NULL;
    }

    new->id = alu_aux.id;
    new->estado = alu_aux.estado;
    new->data_i.dia = alu_aux.data_i.dia;
    new->data_i.mes = alu_aux.data_i.mes;
    new->data_i.ano = alu_aux.data_i.ano;
    new->data_f.dia = alu_aux.data_f.dia;
    new->data_f.mes = alu_aux.data_f.mes;
    new->data_f.ano = alu_aux.data_f.ano;
    new->prox = NULL;

    if (aluguer == NULL) {
        aluguer = new;
    } else {
        aux = aluguer;

        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = new;
    }
    return aluguer;
}

void show_rents(Cliente *cliente, Guitar *gui, int tam) {

    Cliente *aux;
    aux = cliente;
    Data data_aux;
    int pos, dias_atraso;

    if (aux == NULL) {
        printf("Nao existem Alugueres por mostrar...\n\n");
        return;
    }
    printf("\n");

    while (aux) {
        Aluguer *aluguer = aux->alu;
        printf("===============================================================\n");
        while (aluguer) {
            printf("Cliente:\nNome: %s\tNIF: %d\n", aux->nome, aux->nif);
            pos = search_gui_with_id(gui, aluguer->id, tam);
            printf("\nGuitarra:\nNome: %s\tID: %02d\n", gui[pos].nome, gui[pos].id);
            if (aluguer->data_f.dia == 0) {
                printf("\nAluguer a decorrer:\n");
                data_aux = expected_date(aluguer->data_i);
                printf("Data Inicio: %02d-%02d-%02d\tData Prevista: %02d-%02d-%02d\nDias de atraso: A decorrer...\n",
                        aluguer->data_i.dia, aluguer->data_i.mes,
                        aluguer->data_i.ano, data_aux.dia,
                        data_aux.mes, data_aux.ano);
            } else {
                printf("\nAluguer a terminado:\n");
                data_aux = expected_date(aluguer->data_i);
                dias_atraso = count_day_delay(data_aux, aluguer->data_f);
                printf("Data Inicio: %02d-%02d-%02d\tData final: %02d-%02d-%02d\tData Prevista: %02d-%02d-%02d\nDias de atraso: %d\n",
                        aluguer->data_i.dia, aluguer->data_i.mes,
                        aluguer->data_i.ano, aluguer->data_f.dia,
                        aluguer->data_f.mes, aluguer->data_f.ano,
                        data_aux.dia, data_aux.mes,
                        data_aux.ano, dias_atraso);
            }
            aluguer = aluguer->prox;
            printf("===============================================================\n");
        }
        aux = aux->prox;
    }
}

int show_active_rents(Cliente *cliente, Guitar *gui, int tam) { //mostra alugueres em curso
    Cliente *aux;
    aux = cliente;
    int pos;
    if (aux == NULL) {
        printf("Nao existem Alugueres por mostrar...\n\n");
        return 1;
    }
    printf("\n");
    while (aux) {
        Aluguer *aluguer = aux->alu;
        while (aluguer) {
            if (aluguer->data_f.dia == 0) {
                printf("===============================================================\n");
                printf("Cliente:\nNome: %s\tNIF: %d\n", aux->nome, aux->nif);
                pos = search_gui_with_id(gui, aluguer->id, tam);
                printf("\nGuitarra:\nNome: %s\tID: %02d\n", gui[pos].nome, gui[pos].id);
                printf("Data Inicio: %02d-%02d-%02d\n",
                        aluguer->data_i.dia, aluguer->data_i.mes,
                        aluguer->data_i.ano);
                printf("===============================================================\n");
            }
            aluguer = aluguer->prox;
        }
        aux = aux->prox;
    }
    return 0;
}

void add_rent_to_file(Aluguer * aluguer, char *nome_fich) { //adiciona aluguer no final do ficheiro
    FILE *file;

    if ((file = open_folder(nome_fich, "a")) == NULL) {
        return;
    }

    fseek(file, 0, SEEK_END);

    if (aluguer->data_f.dia != 0) {
        fprintf(file, "%02d %d %02d %02d %d %02d %02d %d\n",
                aluguer->id, aluguer->estado,
                aluguer->data_i.dia, aluguer->data_i.mes,
                aluguer->data_i.ano, aluguer->data_f.dia,
                aluguer->data_f.mes, aluguer->data_f.ano);
    } else {
        fprintf(file, "%02d %d %02d %02d %d\n",
                aluguer->id, aluguer->estado,
                aluguer->data_i.dia, aluguer->data_i.mes,
                aluguer->data_i.ano);
    }
    fclose(file);
}

Cliente * conclude_rent_in_node(Cliente *cliente, Guitar *gui, int nif, int pos, int estado_gui, Data data_f) { //concluir aluguer na lista
    Cliente *aux = cliente;

    while (aux) {
        if (nif == aux->nif) {
            Aluguer *aluguer = aux->alu;
            while (aluguer) {
                if (gui[pos].id == aluguer->id) {
                    aluguer->data_f = data_f;
                    aluguer->estado = estado_gui;
                    if (estado_gui == 2) {
                        gui[pos].estado = 2;
                    } else {
                        gui[pos].estado = 0;
                    }
                }
                aluguer = aluguer->prox;
            }
        }
        aux = aux->prox;
    }
    return cliente;
}


