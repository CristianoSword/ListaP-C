/*********************************************

ListaP 1.2 - Um programa de lista postal
E-mail: originalvgo@gmail.com

Autor: Cristiano Camacho
Data: 27/01/2022 20:34
Desc: Um programa de lista postal
      simples com escrita de arquivo txt

*********************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100 //tamanho da lista postal

//estrutura base
struct list_type{
    char nome[40];
    char rua[40];
    char cidade[30];
    char estado[3];
    char cep[10];
}list[SIZE];

//proto
int menu(void);
void init_list(void), enter(void);
void display(void), save(void);
void load(void);

int main(void)
{
    char choice;
    printf("Programa Lista Postal C\n");

    for (;;){
        choice = menu();
            switch(choice){
                case 'i': enter();
                    break;
                case 'v': display();
                    break;
                case 's': save();
                    break;
                case 'c': load();
                    break;
                case 't': exit(0);
            }
    }

}

//inicializa a lista
void init_list(void)
{
    register int t;
    for (t=0; t<SIZE; t++) *list[t].nome = '\0';
    //um nome de comprimento zero significa vazio
}

// poe os nomes na lista
void enter(void)
{
    register int i;
    for (i=0; i<SIZE; i++) if(!*list[i].nome) break;
    if(i == SIZE){
        printf("Lista Cheia\n");
        return;
    }

    printf("\nNome: ");
    gets(list[i].nome);

    printf("Rua: ");
    gets(list[i].rua);

    printf("Cidade: ");
    gets(list[i].cidade);

    printf("Estado: ");
    gets(list[i].estado);

    printf("Cep: ");
    gets(list[i].cep);

    //printf("\n\n");//dar linha
}

//mostra a lista
void display(void)
{
    register int t;

    for(t=0; t<SIZE; t++){
        if(*list[t].nome){
            printf("\nNome: %s\n", list[t].nome);
            printf("Rua: %s\n", list[t].rua);
            printf("Cidade: %s\n", list[t].cidade);
            printf("Estado: %s\n", list[t].estado);
            printf("Cep: %s\n\n", list[t].cep);
        }
    }
}

//salva a lista em um arquivo de texto
void save(void)
{
    FILE *fp;
    register int i;
    if((fp=fopen("maillist", "w"))==NULL){
        printf("O arquivo não pode ser aberto.\n");
        return;
    }

    for(i=0; i<SIZE; i++)
        if(*list[i].nome)

          if(fwrite(&list[i],sizeof(struct list_type), 1, fp)!=1)
             printf("Erro de escrita no arquivo.\n");
    fclose(fp);
}

//carrega o arquivo
void load(void)
{
    FILE *fp;
    register int i;

    if((fp=fopen("maillist", "rb"))==NULL){
        printf("O arquivo não pode ser aberto.\n");
        return;
    }

    init_list();
    for(i=0; i<SIZE; i++)
       if(fread(&list[i], sizeof(struct list_type), 1, fp)!=1){
            if(feof(fp)) break;
            printf("Erro de leitura no arquivo.\n");
    }
    fclose(fp);
}

//obtem uma seleção do menu
menu(void)
{
    char s[80];

    do{
        printf("\n(I)nserir\n");
        printf("(V)isualizar\n");
        printf("(C)arregar\n");
        printf("(S)alvar\n");
        printf("(T)erminar\n");
        printf("escolha: ");
        gets(s);
    }while(!strchr("ivcst", tolower(*s)));
    return tolower(*s);
}
