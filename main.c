/* 
 * File:   main.c
 * Author: Rodrigo Silva 21250068
 */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "structs.h"
#include "menus.h"
#include "cliente.h"
#include "aluguer.h"
#include "ban_cli.h"
#include "util.h"
#include "guitarras.h"

#define NumRents 5
#define nome_fich_cli "cli.txt"
#define nome_fich_gui "gui.txt"
#define nome_fich_ban "ban.dat"

int main(int argc, char** argv) {
    Cliente *head_c = NULL;
    Aluguer *head_a = NULL;
    Guitar *g;
    Cliente aux_cli;
    Guitar aux_gui;
    Data aux_data;
    Data aux_data_2;

    int tam = 0, pos, cont, flag = -2;

    head_c = add_cli_file_to_node(head_c, head_a, nome_fich_cli);
    g = read_gui_from_file(g, &tam, nome_fich_gui);

    int i, j;

    do {
        i = menu();
        switch (i) {
            case 1:
                do {
                    j = submenu1();
                    switch (j) {
                        case 1:
                            
                            flag = -2;
                            printf("\nIntruduza o cliente a adicionar: ");
                            scanf(" %49[^\n]", aux_cli.nome);
                            do {
                                if (flag == 1) {
                                    printf("\nJa existe um cliente com o mesmo NIF, tente outra vez!\n\n");
                                }
                                printf("Intruduza o NIF (9 digitos) do cliente: ");
                                scanf("%d", &aux_cli.nif);
                            } while (check_nif(aux_cli.nif) == 0 ||
                                    (flag = check_if_cli_active(head_c, aux_cli.nif)) == 1 ||
                                    search_cli_on_ban_file(aux_cli.nif, nome_fich_ban) == 1);
                            aux_cli.cont_a = 0;
                            aux_cli.cont_estado = 0;
                            head_c = add_one_cli_node(head_c, aux_cli);
                            add_cli_file(aux_cli, nome_fich_cli);

                            break;

                        case 2:
                            do {
                                if (flag == 1) {
                                    printf("\nEste NIF nao esta ativo, tente outra vez!\n\n");
                                }
                                printf("\nIntruduza o NIF do cliente a remover da base de dados: ");
                                scanf("%d", &aux_cli.nif);
                            } while (check_nif(aux_cli.nif) == 0 ||
                                    (flag = check_if_cli_active(head_c, aux_cli.nif) == 1) ||
                                    search_cli_on_ban_file(aux_cli.nif, nome_fich_ban) == 1);

                            head_c = delete_cli_node(head_c, aux_cli.nif);
                            delete_cli_file(head_c, nome_fich_cli);
                            break;

                        case 3:
                            show_cli_data(head_c);
                            break;
                        case 4:
                            show_active_cli(head_c);
                            break;
                        case 5:
                            show_ban_file(nome_fich_ban);
                            break;
                        case 6:
                            break;
                    }
                } while (j != 6);
                break;
            case 2:
                do {
                    j = submenu2();
                    switch (j) {
                        case 1:
                            aux_gui = get_gui(g, &tam, aux_gui);
                            g = add_gui(g, aux_gui, &tam);
                            add_gui_file(g, tam - 1, nome_fich_gui);
                            break;
                        case 2:
                            do {
                                printf("Insira o id da guitarra para ver o seu historio: ");
                                scanf("%d", &aux_gui.id);
                            } while (search_gui_with_id(g, aux_gui.id, tam) == -1);
                            gui_rent_history(aux_gui.id, head_c);
                            break;
                        case 3:
                            show_gui(g, tam);
                            break;
                        case 4:
                            show_rented_gui(g, head_c, &tam);
                            break;
                        case 5:
                            break;
                    }
                } while (j != 5);
                break;
            case 3:
                do {
                    j = submenu3();
                    switch (j) {
                        case 1:
                            printf("Clientes Activos:\n");
                            show_active_cli(head_c);
                            printf("\n");
                            printf("Guitarras Disponiveis:\n");
                            show_gui_available(g, tam);
                            flag = -2;
                            do {
                                if (flag == 0) {
                                    printf("\nEste NIF nao esta ativo, tente outra vez!\n\n");
                                }
                                printf("\n\nInsira o NIF do cliente que quer alugar: ");
                                scanf("%d", &aux_cli.nif);
                            } while (check_nif(aux_cli.nif) == 0 || (flag = check_if_cli_active(head_c, aux_cli.nif)) == 0);
                            flag = -2;
                            do {
                                if (flag == 1) {
                                    printf("\nA guitarra com este id esta indisponivel\n\n");
                                }
                                printf("Insira o ID da guitarra para alugar: ");
                                scanf("%d", &aux_gui.id);
                            } while ((pos = search_gui_with_id(g, aux_gui.id, tam)) == -1 ||
                                    (flag = check_gui_availability_by_id(g, aux_gui.id, tam)) != 0);

                            printf("Introduza a data inicial do aluguer (Neste formato DD-MM-AAAA): ");
                            scanf("%d-%d-%d", &aux_data.dia, &aux_data.mes, &aux_data.ano);

                            if ((cont = check_num_rents_of_cli(head_c, aux_cli.nif)) >= NumRents) {
                                printf("\nLimite maximo de alugueres: %d\nTem atualmente %d alugueres, logo nao pode criar mais alugueres!\n\n", NumRents, cont);
                            } else {
                                printf("\nLimite maximo de alugueres: %d\nTem atualmente %d alugueres, logo pode criar outro!\n\n", NumRents, cont);
                                head_c = add_rent_to_cli_in_node(head_c, aux_cli.nif, aux_gui.id, aux_data);
                                add_rent_to_cli_in_file(head_c, nome_fich_cli);
                                g = put_gui_as_rented_in_vector(g, tam, aux_gui.id);
                                put_gui_as_rented_in_file(g, tam, nome_fich_gui);
                                int valor_cobrar = g[pos].preco_dia * 7;
                                aux_data = expected_date(aux_data);

                                printf("\nValor maximo previsto a cobrar do aluguer: %d\nData limite: %02d-%02d-%04d\n\n",
                                        valor_cobrar, aux_data.dia, aux_data.mes, aux_data.ano);
                            }
                            break;

                        case 2:
                            printf("\nAluguer a decorrer:\n");
                            show_active_rents(head_c, g, tam);

                            printf("\n\nInsira o NIF do cliente que quer concluir o aluguer: ");
                            scanf("%d", &aux_cli.nif);
                            if (check_nif(aux_cli.nif) == 0 ||
                                    (flag = check_if_cli_active(head_c, aux_cli.nif)) == 0 ||
                                    (cont = check_num_rents_of_cli(head_c, aux_cli.nif)) == 0) {
                                if (cont == 0) {
                                    printf("\n\nEste cliente nao tem alugueres a decorrer");
                                }
                                if (flag == 0) {
                                    printf("\nEste NIF nao esta ativo, tente outra vez!\n\n");
                                }
                                break;
                            }

                            flag = -2;
                            int temp = -2;
                            printf("Insira o ID da guitarra que quer entregar: ");
                            scanf("%d", &aux_gui.id);
                            if ((pos = search_gui_with_id(g, aux_gui.id, tam)) == -1 ||
                                    (flag = check_gui_availability_by_id(g, aux_gui.id, tam)) != 1 ||
                                    (temp = check_if_id_exist_on_cli(head_c, aux_cli.nif, aux_gui.id)) != 1) {
                                if (temp == 0) {
                                    printf("\nEste cliente nao tem nenhuma guitarra alugada com esse id, tente outra vez!\n\n");
                                }
                                if (flag == 0) {
                                    printf("\nA guitarra com esse id esta disponivel logo nao esta nas guitarras alugadas, tente outra vez!\n\n");
                                }
                                break;
                            }

                            int est_gui;
                            do {
                                printf("Em que condicao foi entregue a guitarra (1 - entregue /  2 - entregue danificada): ");
                                scanf("%d", &est_gui);
                            } while (est_gui != 1 && est_gui != 2);

                            do {
                                if (flag == 0) {
                                    printf("\nA data inserida tem de ser maior ou igual a data inicial!\n\n");
                                }
                                aux_data = search_inicial_date_cli(head_c, aux_cli.nif, aux_gui.id);
                                printf("Data de entrega que esta a ser entregue a guitarra (tem de ser maior ou igual que a data inicial): ");
                                scanf("%d-%d-%d", &aux_data_2.dia, &aux_data_2.mes, &aux_data_2.ano);
                            } while ((flag = check_dates(aux_data, aux_data_2)) == 0);

                            head_c = conclude_rent_in_node(head_c, g, aux_cli.nif, pos, est_gui, aux_data_2);
                            put_gui_as_rented_in_file(g, tam, nome_fich_gui);
                            delete_cli_file(head_c, nome_fich_cli);

                            aux_data = expected_date(aux_data);
                            if ((flag = count_day_delay(aux_data, aux_data_2)) > 20) {
                                printf("\nCliente excedeu o limite de 20 dias de atraso! Sera Banido...\n");
                                char mot[100];
                                snprintf(mot, sizeof (mot), "Mais de 20 dias de atraso na entrega! %d dias de atraso.", flag);
                                char *name = search_name_with_nif(head_c, aux_cli.nif);
                                strcpy(aux_cli.nome, name);
                                add_cli_to_ban_file(aux_cli, mot, nome_fich_ban);
                                head_c = delete_cli_node(head_c, aux_cli.nif);
                                delete_cli_file(head_c, nome_fich_cli);
                                printf("\nCliente banido\n");
                                printf("\nAluguer Concluido\n");
                                break;
                            }
                            printf("Danificadas: %d\n\n", count_damaged_gui(head_c, aux_cli.nif));
                            if ((flag = count_damaged_gui(head_c, aux_cli.nif)) > 3) {
                                printf("\nCliente danificou mais de 3 guitarras! Sera Banido...\n");
                                char mot[100] = "Danificou mais de 3 guitarras!";
                                char *name = search_name_with_nif(head_c, aux_cli.nif);
                                strcpy(aux_cli.nome, name);
                                add_cli_to_ban_file(aux_cli, mot, nome_fich_ban);
                                head_c = delete_cli_node(head_c, aux_cli.nif);
                                delete_cli_file(head_c, nome_fich_cli);
                                printf("\nCliente banido\n");
                                printf("\nAluguer Concluido\n");
                                break;

                            }
                            printf("\nAluguer Concluido\n");

                            break;

                        case 3:
                            show_rents(head_c, g, tam);
                            break;

                        case 4:
                            break;
                    }
                } while (j != 4);
                break;
        }
    } while (i != 4);
    free(head_c);
    free(head_a);
    free(g);
    return 0;
}


