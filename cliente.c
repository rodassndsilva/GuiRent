/* 
 * File:   cliente.c
 * Author: Rodrigo Silva 21250068
 */

#include "cliente.h"

char *search_name_with_nif(Cliente * cliente, int nif) {
    Cliente *aux = cliente;
    while (aux) {
        if (aux->nif == nif) {
            return aux->nome;
        }
        aux = aux->prox;
    }
}

void show_active_cli(Cliente * cliente) {
    Cliente *aux = cliente;
    if (aux == NULL) {
        printf("Nao existem clientes por mostrar...\n\n");
        return;
    }
    while (aux) {
        printf("Nome: %-20s\tNIF: %d\n", aux->nome, aux->nif);
        aux = aux->prox;
    }
}

void show_cli_data(Cliente * cliente) {
    Cliente *aux;
    aux = cliente;

    if (aux == NULL) {
        printf("Nao existem dados dos Clientes por mostrar...\n\n");
        return;
    }
    while (aux) {
        printf(" N_Alugueres: %-10d NIF: %d Nome: %s\n", aux->cont_a, aux->nif, aux->nome);

        Aluguer *aluguer = aux->alu;
        if (aluguer != NULL) {
            while (aluguer) {
                if (aluguer->data_f.dia != 0) {
                    printf("ID: %-10.2d Estado: %-10.2d Data Inicio: %.2d-%.2d-%-10d Data Final: %.2d-%.2d-%d\n",
                            aluguer->id, aluguer->estado,
                            aluguer->data_i.dia, aluguer->data_i.mes,
                            aluguer->data_i.ano, aluguer->data_f.dia,
                            aluguer->data_f.mes, aluguer->data_f.ano);
                    aluguer = aluguer->prox;
                } else {
                    printf("ID: %-10.2d Estado: %-10.2d Data Inicio: %.2d-%.2d-%-10d Data Final:\n",
                            aluguer->id, aluguer->estado,
                            aluguer->data_i.dia, aluguer->data_i.mes,
                            aluguer->data_i.ano);
                    aluguer = aluguer->prox;
                }
            }
        }
        aux = aux->prox;

        printf("\n");
    }
}

int check_if_cli_active(Cliente * cliente, int nif) {
    Cliente *tmp = cliente;

    while (tmp) {
        if (nif == tmp->nif) {
            return 1;
        }
        tmp = tmp->prox;
    }
    return 0;
}

void add_cli_file(Cliente aux, char *nome_fich) {
    FILE *file;
    if ((file = open_folder(nome_fich, "a")) == NULL) {
        return;
    }
    if (check_file_empty(file) == 1) {
        fprintf(file, "%d %d %s\n", aux.nif, aux.cont_a, aux.nome);
    } else {
        fseek(file, 0, SEEK_END);
        fprintf(file, "\n%d %d %s\n", aux.nif, aux.cont_a, aux.nome);
    }
    fclose(file);
}

void delete_cli_file(Cliente * cliente, char *nome_fich) {

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
    fclose(f);
}

Cliente * delete_cli_node(Cliente *cliente, int nif) {

    //verificar se esta nos banidos. se estiver returnar
    if (cliente != NULL) {
        if (nif == cliente->nif) {
            Cliente *temp;
            temp = cliente;
            cliente = cliente->prox;
            free(temp);
            printf("Cliente com NIF %d removido com sucesso!\n", nif);
            return cliente;
        }
        Cliente * current;
        current = cliente->prox;
        Cliente * previous;
        previous = cliente;

        while (current) {

            if (nif == current->nif) {

                Cliente * temp = current;
                previous->prox = current->prox;
                free(temp);
                printf("Cliente com NIF %d removido com sucesso!\n", nif);
                return cliente;
            }
            previous = current;
            current = current->prox;
        }
        printf("\nNao existe esse cliente na base de dados!\n");
    } else {
        printf("\nEsta vazia a base de dados!\n");
    }
    return cliente;
}

Cliente * add_one_cli_node(Cliente *cliente, Cliente cli_aux) {

    Cliente *new = (Cliente*) malloc(sizeof (Cliente)), *aux;

    if (new == NULL) {
        printf("Erro na alocacao de memoria\n\n");
        return NULL;
    }
    new->cont_a = cli_aux.cont_a;
    new->nif = cli_aux.nif;
    new->cont_estado = 0;
    strcpy(new->nome, cli_aux.nome);
    new->alu = NULL;
    new->prox = NULL;

    if (cliente == NULL) {
        cliente = new;
    } else {
        aux = cliente;

        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = new;
    }

    return cliente;
}

Cliente * add_cli_with_rent_node(Cliente *cliente, Aluguer *aluguer, Cliente cli_aux, FILE * file) { //adicionar um cliente com aluguer na lista
    Cliente *new = (Cliente*) malloc(sizeof (Cliente)), *aux;

    if (new == NULL) {
        printf("Erro na alocacao de memoria\n\n");
        return NULL;
    }

    new->cont_a = cli_aux.cont_a;
    new->nif = cli_aux.nif;
    strcpy(new->nome, cli_aux.nome);
    new->alu = add_rent_from_file_to_node(aluguer, file);
    new->cont_estado = count_damaged_gui(cliente, cli_aux.nif);
    new->prox = NULL;
    printf("%s\n\n", new->nome);
    if (cliente == NULL) {
        cliente = new;
    } else {
        aux = cliente;

        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = new;
    }

    return cliente;
}

Cliente * add_cli_file_to_node(Cliente *cliente, Aluguer *aluguer, char *nome) { //adicionar cliente do ficheiro para a lista
    FILE *file;
    Cliente aux;

    // Verificar se é possivel abrir o ficheiro
    if ((file = open_folder(nome, "r")) == NULL || check_file_empty(file) == 1) {
        return NULL;
    }
    char buf[150];
    while (!feof(file)) {

        fgets(buf, sizeof (buf), file);
        if (strcmp(buf, "\n") == 0 || strcmp(buf, " ") == 0) {
            fclose(file);
            return cliente;
        }
        sscanf(buf, "%d %d %49[^\n]", &aux.nif, &aux.cont_a, aux.nome);

        cliente = add_cli_with_rent_node(cliente, aluguer, aux, file);

    }
    fclose(file);

    return cliente;
}

Data search_inicial_date_cli(Cliente *cliente, int nif, int id) {
    Cliente *aux = cliente;
    while (aux) {
        if (nif == aux->nif) {
            Aluguer *aluguer = aux->alu;
            while (aluguer) {
                if (id == aluguer->id && aluguer->estado == 0) {
                    return aluguer->data_i;
                }
                aluguer = aluguer->prox;
            }
        }
        aux = aux->prox;
    }

}
