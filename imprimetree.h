#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

void imprime_arvore(){
    
     FILE * binary;

    if ((binary = fopen("btree.dat", "r")) == NULL)
    {
        printf("Falha ao abrir arquivo!\n");
        exit(EXIT_FAILURE);
    }

    rewind(binary);
    char buffer[TAM_PAGE_STR];
    char marcador = '\0';
    fread(buffer, 1, sizeof(int), binary);
    int rrnraiz = atoi(buffer);

    int rrnatual = 4;
    int rrnpag = 0;

    while (marcador != EOF)
    {
        if (rrnatual == rrnraiz)
        {
            printf("\n\n ------- Pagina Raiz -------");
        }

        fread(buffer, 1, TAM_PAGE_STR, binary);
        char *fragmento = strtok(buffer, DELIM_STR);
        int filhos[ORDEM];
        int chaves[ORDEM-1];
        int marcafilho = 0;
        int marcachave = 0;

        for (int i = 0; i < TAM_PAGE; i++)
        {
           if (i%2 == 0)
           {
                filhos[marcafilho] = atoi(fragmento);
                marcafilho++;
           }
           else
           {
               chaves[marcachave] = atoi(fragmento);
               marcachave++;
           }

           fragmento = strtok(NULL, DELIM_STR);
        }
        printf("\n\nRRN: %i ", rrnpag);
        rrnpag++;
        printf("\n");
        printf("Chaves: ");
        for (int i = 0; i < ORDEM-1; i++)
        {
            if (chaves[i] != -1)
            {
                if (i != 0)
                {
                    printf(" | ");
                }
                printf("%i", chaves[i]);
            }
            else
            {
                break;
            }
        }
        printf("\n");
        printf("Filhos: ");
        for (int i = 0; i < ORDEM; i++)
        {
            if (filhos[i] != -1)
            {
                if(i != 0)
                {
                    printf(" | ");
                }
                printf("%i", filhos[i]);
            }
            else if (filhos[i] == -1)
            {
                
                if(i != 0)
                {
                    printf(" | ");
                }
                printf(" -1 ");
            }
            else{
                printf("\n");
                break;
            } 
        }

        if (rrnatual == rrnraiz)
        {
            printf("\n\n ---------------------------");
        }

        marcador = fgetc(binary);
        fseek(binary, TAM_PAGE_STR+rrnatual, SEEK_SET);
        rrnatual += TAM_PAGE_STR;

    }
    
}