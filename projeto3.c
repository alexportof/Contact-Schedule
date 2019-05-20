#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contato
{
    char nome[101];
    char telefone[11];
    char endereco[100];
    int cep;
    char data_nasc[11];
};
typedef struct elemento *Lista;

struct elemento
{
    struct elemento *ant;
    struct contato dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista *criaListaVazia();
void libera_lista(Lista *li);
int *le_arquivo();
void adiciona_na_lista(Lista *li, FILE *fp, struct contato contato);

int main()
{
    struct contato contato;
    Lista list;
    FILE *fp;
    list = criaListaVazia();
    fp = le_arquivo();
    adiciona_na_lista(list, fp, contato);
    libera_lista(list);
    return 0;
}

void adiciona_na_lista(Lista *li, FILE *fp, struct contato contato)
{
    char nome[101];
    char linha = "$";
    char telefone[11];
    char endereco[100];
    char cep[10];
    char data_nasc[11];
    while (linha = "$")
    {
        fgets(nome, sizeof(nome), fp);
        strcpy(contato.nome, nome);
        fgets(telefone, sizeof(telefone), fp);
        strcpy(contato.telefone, telefone);
        fgets(endereco, sizeof(endereco), fp);
        fgets(endereco, sizeof(endereco), fp);
        strcpy(contato.endereco, endereco);
        fgets(cep, sizeof(cep), fp);
        contato.cep = atoi(cep);
        fgets(data_nasc, sizeof(data_nasc), fp);
        strcpy(contato.data_nasc, data_nasc);
        fgets(linha, sizeof(linha), fp);
        printf("%c", contato.nome);
    }
}

int *le_arquivo()
{
    FILE *fp;
    fp = fopen("contatos.txt", "r");
    if (fp == NULL)
        exit(1);
    return fp;
}

Lista *criaListaVazia()
{
    Lista *li = (Lista *)malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}
void libera_lista(Lista *li)
{
    if (li != NULL)
    {
        Elem *no;
        while ((*li) != NULL)
        {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}