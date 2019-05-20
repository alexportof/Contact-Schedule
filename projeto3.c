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
void carrega_arquivo(Lista *li, FILE *fp, struct contato contato);
Lista *insere_inicio(Lista *list, struct contato contato);

int main()
{
    struct contato contato;
    Lista list;
    FILE *fp;
    list = criaListaVazia();
    fp = le_arquivo();
    carrega_arquivo(list, fp, contato);
    libera_lista(list);
    return 0;
}
Lista *insere_inicio(Lista *list, struct contato contato)
{
}

void carrega_arquivo(Lista *li, FILE *fp, struct contato contato)
{
    char nome[101];
    char sobrenome[101];
    char linha[2];
    char telefone[11];
    char endereco[100];
    int cep;
    char data_nasc[11];
    while (!feof(fp))
    {
        fscanf(fp, "%s%s\n", &nome, &sobrenome);
        strcat(nome, " ");
        strcat(nome, sobrenome);
        fscanf(fp, "%s\n", &telefone);
        fgets(endereco, sizeof(endereco), fp);
        fscanf(fp, "%d\n", &cep);
        fscanf(fp, "%s\n", &data_nasc);
        fscanf(fp, "%c\n", &linha);
        strcpy(contato.nome, nome);
        strcpy(contato.telefone, telefone);
        strcpy(contato.endereco, endereco);
        strcpy(contato.data_nasc, data_nasc);
        contato.cep = cep;
        li = insere_inicio(li, contato);
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