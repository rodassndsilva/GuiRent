/* 
 * File:   guitarras.h
 * Author: Rodrigo Silva 21250068
 */
#include "guitarras.h"

Guitar * create_vector(Guitar *gui, int *tam) {
    gui = (Guitar*) malloc(*tam * sizeof (Guitar));
    if (gui == NULL) {
        printf("Debug: \n");
        *tam = 0;
        return NULL;
    }
    return gui;
}

Guitar * add_gui(Guitar gui[], Guitar aux_2, int *tam) {

    Guitar *aux;
    aux = (Guitar *) realloc(gui, (*tam + 1) * sizeof (Guitar));

    if (aux == NULL)
        return gui;

    gui = aux;
    (*tam)++;
    gui[*tam - 1].id = aux_2.id;
    gui[*tam - 1].estado = aux_2.estado;
    strcpy(gui[*tam - 1].nome, aux_2.nome);
    gui[*tam - 1].preco = aux_2.preco;
    gui[*tam - 1].preco_dia = aux_2.preco_dia;

    return gui;
}

void add_gui_file(Guitar *gui, int pos, char *nome_fich) {
    FILE *file;
    if ((file = open_folder(nome_fich, "a")) == NULL) {
        return;
    }
    if (check_file_empty(file) == 1) {
        fprintf(file, "%02d %.2f %.2f %d %s", gui[pos].id, gui[pos].preco_dia, gui[pos].preco, gui[pos].estado, gui[pos].nome);
    } else {
        fseek(file, 0, SEEK_END);
        fprintf(file, "\n%02d %.2f %.2f %d %s", gui[pos].id, gui[pos].preco_dia, gui[pos].preco, gui[pos].estado, gui[pos].nome);
    }
    fclose(file);
}

Guitar * read_gui_from_file(Guitar *gui, int *tam, char *nome_fich) {
    Guitar aux;
    FILE *file;
    char buf[150];

    if ((file = open_folder(nome_fich, "r")) == NULL ||
            (gui = create_vector(gui, tam)) == NULL ||
            check_file_empty(file) == 1) {
        return NULL;
    }
    while (!feof(file)) {
        fgets(buf, sizeof (buf), file);
        sscanf(buf, "%d %f %f %d %49[^\n]", &aux.id, &aux.preco_dia, &aux.preco, &aux.estado, aux.nome);
        gui = add_gui(gui, aux, tam);
    }
    fclose(file);
    return gui;
}

Guitar get_gui(Guitar *gui, int *tam, Guitar aux) {
    printf("\nIntruduza o nome da guitarra: ");
    scanf(" %49[^\n]", aux.nome);
    printf("\nIntruduza o preco por dia da guitarra: ");
    scanf("%f", &aux.preco_dia);
    printf("\nIntruduza o preco da guitarra: ");
    scanf("%f", &aux.preco);
    if (gui != NULL) {
        aux.id = gui[*tam - 1].id + 1;
    } else
        aux.id = 00;

    aux.estado = 0;

    return aux;
}

void show_gui(Guitar *v, int tam) {
    if (v != NULL) {
        printf("ID:\t\t Preco por dia:\t\t Preco:\t\t Estado:\t Nome: \n\n");
        for (int i = 0; i < tam; i++) {
            printf("%02d\t %-15.2f\t %-10.2f\t %-10d\t %s\n", v[i].id, v[i].preco_dia, v[i].preco, v[i].estado, v[i].nome);
        }
        return;
    }
    printf("Nada a mostrar, o ficheiro esta vazio!\n\n");
}

void show_rented_gui(Guitar *gui, Cliente *cli, int *tam) {
    printf("Guitarras Alugadas\n\n");
    int flag = 0;
    if (gui != NULL) {
        for (int i = 0; i<*tam; i++) {

            if (gui[i].estado == 1) {

                Cliente *aux = cli;

                while (aux) {
                    Aluguer *aluguer = aux->alu;
                    while (aluguer) {
                        if (gui[i].id == aluguer->id && aluguer->data_f.dia == 0) {
                            printf("Nome do Cliente: %s\tNIF: %d\n", aux->nome, aux->nif);
                            printf("Nome da guitarra: %s\tID: %d\tPreco por dia: %.2f\tValor: %.2f\n\n", gui[i].nome, gui[i].id, gui[i].preco_dia, gui[i].preco);
                        }
                        aluguer = aluguer->prox;
                    }
                    aux = aux->prox;
                }
                flag = 1;
            }
        }
        if (flag == 0)
            printf("Nao existem guitarras alugadas\n\n");
        return;
    }
    printf("Nao existem guitarras na base de dados\n\n");
}

void gui_rent_history(int id, Cliente *cliente) {
    printf("\n\nHistorico da guitarra com id: %02d\n\n", id);
    int dias_atraso, flag = 0;
    while (cliente) {
        Aluguer *aluguer = cliente->alu;
        while (aluguer) {
            if (aluguer->id == id) {
                if (aluguer->data_f.dia != 0) {

                    dias_atraso = count_day_delay(expected_date(aluguer->data_i), aluguer->data_f);
                    printf("Cliente: %s\tData Inicio: %02d-%02d-%d\tData Final: %02d-%02d-%02d\tDias de atraso: %d\n",
                            cliente->nome,
                            aluguer->data_i.dia, aluguer->data_i.mes,
                            aluguer->data_i.ano, aluguer->data_f.dia,
                            aluguer->data_f.mes, aluguer->data_f.ano,
                            dias_atraso);
                } else {
                    printf("Cliente: %s\tData Inicio: %02d-%02d-%02d\tAluguer ainda em curso!\n",
                            cliente->nome,
                            aluguer->data_i.dia, aluguer->data_i.mes,
                            aluguer->data_i.ano);
                }
                flag = 1;
            }
            aluguer = aluguer->prox;
        }
        cliente = cliente->prox;
    }
    if (flag == 0)
        printf("A guitarra com o id: %02d nao tem historico de alugueres\n\n", id);

}

int search_gui_with_id(Guitar *gui, int id, int pos) {
    if (gui != NULL) {
        for (int i = 0; i < pos; i++) {
            if (gui[i].id == id) {
                return i;
            }
        }
    }

    printf("Esse ID nao existe!\n\n");
    return -1;
}

int count_damaged_gui(Cliente *cliente, int nif) {
    int cont = 0;
    while (cliente) {
        if (nif == cliente->nif) {
            Aluguer *aluguer = cliente->alu;
            while (aluguer) {
                if (aluguer->estado == 2) {
                    cont++;
                }
                aluguer = aluguer->prox;
            }
        }
        cliente = cliente->prox;
    }
    return cont;
}

int check_gui_availability_by_id(Guitar *gui, int id, int pos) {
    if (gui != NULL) {
        for (int i = 0; i < pos; i++) {

            if (gui[i].id == id) {
                if (gui[i].estado == 2) {
                    printf("A guitarra com ID %d esta danificada\n\n", id);
                    return 2;
                }
                if (gui[i].estado == 1) {
                    return 1;
                }
                if (gui[i].estado == 0) {
                    return 0;
                }
            }
        }
    }
    printf("\nNao existe a Guitarra com ID %d em stock\n\n", id);
    return 3;
}

void show_gui_available(Guitar *gui, int tam) {

    if (gui != NULL) {
        printf("ID:\t\t Preco por dia:\t\t Preco:\t Nome: \n\n");
        for (int i = 0; i < tam; i++) {
            if (gui[i].estado == 0) {
                printf("%02d\t %-15.2f\t %-10.2f\t %s\n", gui[i].id, gui[i].preco_dia, gui[i].preco, gui[i].nome);
            }
        }
        return;
    }
    printf("Nao existem guitarras na base de dados\n\n");
}

Guitar * put_gui_as_rented_in_vector(Guitar *gui, int tam, int id) {

    for (int i = 0; i < tam; i++) {
        if (gui[i].id == id) {
            gui[i].estado = 1;
            return gui;
        }
    }
}

void put_gui_as_rented_in_file(Guitar *gui, int tam, char *nome_fich) {
    FILE *f;

    remove(nome_fich);
    if ((f = open_folder(nome_fich, "w")) == NULL) {
        fclose(f);
        return;
    }

    for (int i = 0; i < tam; i++) {
        if (check_file_empty(f) == 1) {
            fprintf(f, "%02d %.2f %.2f %d %s",
                    gui[i].id, gui[i].preco_dia,
                    gui[i].preco, gui[i].estado,
                    gui[i].nome);
        } else {
            fseek(f, 0, SEEK_END);
            fprintf(f, "\n%02d %.2f %.2f %d %s",
                    gui[i].id, gui[i].preco_dia,
                    gui[i].preco, gui[i].estado,
                    gui[i].nome);
        }
    }
    fclose(f);
}

int check_if_id_exist_on_cli(Cliente *cliente, int nif, int id) {
    Cliente *aux = cliente;
    if (aux == NULL) {
        printf("Nao existem clientes na base de dados\n\n");
        return 0;
    }

    while (aux) {
        if (aux->nif == nif) {
            Aluguer *aluguer = aux->alu;
            while (aluguer) {
                if (id == aluguer->id) {
                    return 1;
                }
                aluguer = aluguer->prox;
            }
        }
        aux = aux->prox;
    }
    return 0;
}