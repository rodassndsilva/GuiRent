/* 
 * File:   ban_cli.c
 * Author: Rodrigo Silva 21250068
 */

#include "ban_cli.h"

void show_ban_file(char *nome_fich) {
    Ban ban;
    FILE *f;

    if ((f = open_folder(nome_fich, "rb")) == NULL) {
        return;
    }

    while (fread(&ban, sizeof (Ban), 1, f) == 1) {
        printf("Nome: %-25s\tNIF: %6d\tMotivo: %s\n", ban.nome, ban.nif, ban.mot);
    }
    fclose(f);
}

int search_cli_on_ban_file(int nif, char *nome_fich) {
    Ban ban;
    FILE *f;

    if ((f = open_folder(nome_fich, "rb")) == NULL) {
        return 1;
    }

    while (fread(&ban, sizeof (Ban), 1, f) == 1) {
        if (ban.nif == nif) {
            printf("\nEste NIF encontra-se no ficheiro dos clientes banidos\n\n");
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;

}

void add_cli_to_ban_file(Cliente aux, char *mot, char * nome_fich) {
    FILE *f;
    Ban ban;

    strcpy(ban.nome, aux.nome);
    ban.nif = aux.nif;
    strcpy(ban.mot, mot);

    if ((f = open_folder(nome_fich, "ab")) == NULL) {
        fclose(f);
        printf("Erro ao criar o ficheiro %s\n", nome_fich);
        return;
    }
    fwrite(&ban, sizeof (Ban), 1, f);
    fclose(f);
}

