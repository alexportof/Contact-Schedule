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
void insere_inicio(Lista *li, struct contato contato);
//int consulta_lista(Lista *li, int pos, struct contato *cont);

int main()
{
    struct contato contato;
    Lista list;
    FILE *fp;
    list = criaListaVazia();
    fp = le_arquivo();
    carrega_arquivo(list, fp, contato);
    int x = tamanho_lista(list);
    printf("%d", x);
    libera_lista(list);
    return 0;
}

// int consulta_lista(Lista *li, int pos, struct contato *cont)
// {
//     if (li == NULL || pos <= 0)
//         return 0;
//     Elem *no = *li;
//     int i = 1;
//     while (no != NULL && i < pos)
//     {
//         no = no->prox;
//         i++;
//     }
//     if (no == NULL)
//         return 0;
//     else
//     {
//         *cont = no->dados;
//         return 1;
//     }
// }
void insere_inicio(Lista *li, struct contato contato)
{
    if (li == NULL)
        exit(1);
    Elem *no = (Elem *)malloc(sizeof(Elem));
    if (no == NULL)
        exit(1);
    no->dados = contato;
    no->prox = (*li);
    no->ant = NULL;
    if (*li != NULL)
        (*li)->ant = no;
    *li = no;
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
        insere_inicio(li, contato);
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