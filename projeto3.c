#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
int carregar_menu();
void menu(int opcao, Lista *li);
void criar_contato(Lista *li);
int tamanho_lista(Lista *li);
void buscar_consulta_lista(Lista *li, char string[100]);
void consultar_lista(Lista *li);
void remover_contato(Lista *li);
void remover_contato_lista(Lista *li, char string[100]);

int main()
{
    struct contato contato;
    Lista list;
    int opcao = 0;
    FILE *fp;
    list = criaListaVazia();
    fp = le_arquivo();
    carrega_arquivo(list, fp, contato);
    opcao = carregar_menu();
    menu(opcao, list);
    return 0;
}
void remover_contato_lista(Lista *li, char string[100])
{
    if (li == NULL)
    {
        printf("Lista Vazia");
        exit(1);
    }
    Elem *no = *li;
    int cont = 0;
    while (no != NULL)
    {
        if (strcmp(no->dados.nome, string) == 0)
        {
            free(no);
        }

        *li = no->prox;
    }
}
void remover_contato(Lista *li)
{
    int opcao = 0;
    char string[100];
    printf("Escreva a String que Deseja Eliminar nos Registros: ");
    scanf("%s", string);
    buscar_consulta_lista(li, string);
    opcao = carregar_menu();
    menu(opcao, li);
}
void buscar_consulta_lista(Lista *li, char string[100])
{
    if (li == NULL)
    {
        printf("Lista Vazia");
        exit(1);
    }
    Elem *no = *li;
    int cont = 0;
    while (no != NULL)
    {

        printf("\t\t%d\n\n\n\n", strcmp(no->dados.nome, string));
        if (strcmp(no->dados.nome, string) == 0)
            printf("POTTAAAAAA");
        no = no->prox;
    }
}
void consultar_lista(Lista *li)
{
    int opcao = 0;
    char string[100];
    printf("Escreva a String que Deseja Visualizar os Registros: ");
    scanf("%s", string);
    buscar_consulta_lista(li, string);
    opcao = carregar_menu();
    menu(opcao, li);
}
int tamanho_lista(Lista *li)
{
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem *no = *li;
    while (no != NULL)
    {
        cont++;
        no = no->prox;
    }
    return cont;
}
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

void menu(int opcao, Lista *li)
{
    if (opcao > 5 || opcao <= 0)
    {
        printf("\nNumero Invalido!\n");
        exit(1);
    }
    switch (opcao)
    {
    case 1:
        criar_contato(li);

    case 2:
        remover_contato(li);

    case 3:
        consultar_lista(li);

    case 4:

    case 5:
        libera_lista(li);
    }
}
int carregar_menu()
{
    int opcao;
    printf("-----------------------------\nMenu Da Agenda de Contatos\n-----------------------------\n");
    printf("1 - Inserir Novo Registro\n2 - Remover Registros Que Contenham Certa String no Nome\n3 - Visualizar Registros Que Contenham Certa String No Nome\n4 - Visualizar Os Registros em Ordem Alfabética\n5 - Sair\n");
    printf("\n\nTecle a Opcao Escolhida: ");
    scanf("%d", &opcao);
    return opcao;
}
void criar_contato(Lista *li)
{
    struct contato contato;
    char nome[101];
    char sobrenome[101];
    char linha[2];
    char telefone1[6];
    char telefone2[5];
    char endereco[100];
    int cep, opcao = 0;
    char data_nasc[11], mes[11], ano[11];

    printf("Nome: ");
    scanf("%s", &nome);
    printf("Sobrenome: ");
    scanf("%s", &sobrenome);
    strcat(nome, " ");
    strcat(nome, sobrenome);
    strcpy(contato.nome, nome);
    printf("5 Primeiros Dígitos do Telefone: ");
    scanf("%s", &telefone1);
    printf("4 Ultimos Números do Telefone: ");
    scanf("%s", &telefone2);
    strcat(telefone1, "-");
    strcat(telefone1, telefone2);
    strcpy(contato.telefone, telefone1);
    printf("Endereco: ");
    scanf("%s;", &endereco);
    strcpy(contato.endereco, endereco);
    printf("CEP: ");
    scanf("%d", &cep);
    contato.cep = cep;
    printf("Dia de Nascimento: ");
    scanf("%s", &data_nasc);
    strcat(data_nasc, "/");
    printf("Mes: ");
    scanf("%s", &mes);
    strcat(data_nasc, mes);
    strcat(data_nasc, "/");
    printf("Ano: ");
    scanf("%s", &ano);
    strcat(data_nasc, ano);
    strcpy(contato.data_nasc, data_nasc);
    insere_inicio(li, contato);
    opcao = carregar_menu();
    menu(opcao, li);
}