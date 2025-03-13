#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"

/*Organizando o código em fuções primárias e secundarias*/
/*Prototipando todas as funções secundárias, pois não sofrerão muitas alterações*/

float somarec(reg_aluno aluno[], int n);

int buscarec(reg_aluno alunos[], int n, char rga_x[]);

float media(reg_aluno aluno[]);

void troca(reg_aluno *q, reg_aluno *s);

void inserir_ordenado(reg_aluno aluno[], int n, reg_aluno novoaluno);

void ordernar_ma(reg_aluno aluno[], int a);

int exibir_alunos(reg_aluno aluno[], int a);

/*FUNÇÕES PRINCIPAIS*/

/* Função para ler um aluno e evitar duplicação de RGA */
void ler_aluno(reg_aluno aluno[], int numero_alunos)
{
    reg_aluno alunonovo;
    char rga_temp[13];
    int pos, validacao, i;

    for (i = 0; i < numero_alunos; i++){

        printf("\nInforme o nome do aluno %d: ", i + 1);
        scanf(" %[^\n]", alunonovo.nome);

        validacao = 0;
        do{

            printf("Informe o RGA do aluno %d: ", i + 1);
            scanf("%s", rga_temp);
            pos = buscarec(aluno, i, rga_temp);

            if (pos != -1)
                printf("O RGA %s já está cadastrado. Insira um RGA diferente.\n", rga_temp);
            else{

                strcpy(alunonovo.rga, rga_temp);
                validacao = 1;
            }
        }while (validacao == 0);

        do{
            printf("Informe a nota da P1 (0 a 10): ");
            scanf("%f", &alunonovo.p1);
            if (alunonovo.p1 < 0 || alunonovo.p1 > 10)
                printf("Nota inválida! Digite um valor entre 0 e 10.\n");

        } while (alunonovo.p1 < 0 || alunonovo.p1 > 10);

        do
        {
            printf("Informe a nota da P2 (0 a 10): ");
            scanf("%f", &alunonovo.p2);
            if (alunonovo.p2 < 0 || alunonovo.p2 > 10)
                printf("Nota inválida! Digite um valor entre 0 e 10.\n");

        } while (alunonovo.p2 < 0 || alunonovo.p2 > 10);

        do
        {
            printf("Informe a nota do TP (0 a 10): ");
            scanf("%f", &alunonovo.tp);
            if (alunonovo.tp < 0 || alunonovo.tp > 10)
                printf("Nota inválida! Digite um valor entre 0 e 10.\n");

        } while (alunonovo.tp < 0 || alunonovo.tp > 10);

        alunonovo.ma = media(&alunonovo);

        system("clear");

        printf("Cadastro realizado com sucesso!\n\n");

        inserir_ordenado(aluno, i, alunonovo);


    }
}


/*Função que realiza a remoção dos alunos*/
void remover_aluno(reg_aluno aluno[], int *n, char rga_a_ser_encontrado[])
{
    int pos, i;

    pos = buscarec(aluno, *n, rga_a_ser_encontrado);

    /* Caso em que o aluno foi encontrado */
    if (pos != -1)
    {
        printf("Aluno %s removido com sucesso!\n\n", aluno[pos].nome);
        for (i = pos; i < *n - 1; i++)
            aluno[i] = aluno[i + 1];
        
        (*n)--;
    }
    else
        printf("Aluno não encontrado!\n\n");
}

void notas(reg_aluno aluno[], char rga_x[], int i)
{
    /*Essa função permite que o usuario altere e adicione novas notas*/
    int veri, pos;
    char resp[3];
    veri = 0;

    /*busca recursiva do rga*/
    pos = buscarec(aluno, i, rga_x);

    if (pos != -1)
    {
        veri = 0;
        while (veri == 0)
        {
            printf("\nQual dessas notas será?\np1\np2\ntp\n");
            scanf(" %s", resp);

            if (strcmp(resp, "p1") == 0)
            {
                do{
                    printf("Informe a nota da P1 (0 a 10): ");
                    scanf("%f", &aluno[pos].p1);
                    if (aluno[pos].p1 < 0 || aluno[pos].p1 > 10)
                        printf("Nota inválida! Digite um valor entre 0 e 10.\n");

                } while (aluno[pos].p1 < 0 || aluno[pos].p1 > 10);
                
                printf("P1 adicionada!\n");
            }
            else if (strcmp(resp, "p2") == 0)
            {
                do{
                    printf("Informe a nota da P2 (0 a 10): ");
                    scanf("%f", &aluno[pos].p2);
                    if (aluno[pos].p2 < 0 || aluno[pos].p2 > 10)
                        printf("Nota inválida! Digite um valor entre 0 e 10.\n");

                } while (aluno[pos].p2 < 0 || aluno[pos].p2 > 10);
                
                printf("P2 adicionada!\n");
            }
            else if (strcmp(resp, "tp") == 0)
            {
                do{
                    printf("Informe a nota do TP (0 a 10): ");
                    scanf("%f", &aluno[pos].tp);
                    if (aluno[pos].tp < 0 || aluno[pos].tp > 10)
                        printf("Nota inválida! Digite um valor entre 0 e 10.\n");

                } while (aluno[pos].tp < 0 || aluno[pos].tp > 10);
                
                printf("TP adicionado!\n");
            }

            aluno[pos].ma = media(&aluno[pos]);
            printf("Deseja continuar alterando? (s/n)\n");
            scanf(" %s", resp);
            if (strcmp(resp, "n") == 0)
                veri = 1;
        }
        system("clear");
    }
    else{
        system("clear");
        printf("RGA não encontrado\n");
    }

}



/*Uso de ponteiro para aluno*/
void aprovados(reg_aluno aluno[], int n)
{
    reg_aluno *aprovados;
    int conta_aprovado, b;

    conta_aprovado = 0;

    /*Alocação dinamica de memoria*/
    aprovados = (reg_aluno *)malloc(n * sizeof(reg_aluno));

    if (aprovados == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return;
    }

    for (b = 0; b < n; b++)
    {
        if (aluno[b].ma >= 6.0)
        {
            aprovados[conta_aprovado] = aluno[b];
            conta_aprovado++;
        }
    }

    if (exibir_alunos(aprovados, conta_aprovado) == 0)
        printf("Não há alunos aprovados\n");

    free(aprovados);
}
void reprovados(reg_aluno alunos[], int a)
{
    reg_aluno *reprovados;
    int contador_reprovados, b;

    contador_reprovados = 0;

    reprovados = (reg_aluno *)malloc(a * sizeof(reg_aluno));
    if (reprovados == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }

    for (b = 0; b < a; b++)
    {
        if (alunos[b].ma < 6.0)
        {
            reprovados[contador_reprovados] = alunos[b];
            contador_reprovados++;
        }
    }
    /*Funcão criado para ordernadas os reprovados em ordem crescente*/
    ordernar_ma(reprovados, contador_reprovados);
    /*exibir os reprovados*/
    if (exibir_alunos(reprovados, contador_reprovados) == 0)
        printf("Não há alunos reprovados!\n");

    free(reprovados);
}

void ma_aprovados(reg_aluno aluno[], int a)
{
    reg_aluno *aprovados;
    int conta_aprovado, b;

    conta_aprovado = 0;

    aprovados = (reg_aluno *)malloc(a * sizeof(reg_aluno));
    if (aprovados == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }

    for (b = 0; b < a; b++)
    {
        if (aluno[b].ma >= 6.0)
        {
            aprovados[conta_aprovado] = aluno[b];
            conta_aprovado++;
        }
    }
    if (conta_aprovado > 0)
    {
        printf("A media dos %d aprovado(s) foi de %.2f: \n", conta_aprovado, somarec(aprovados, conta_aprovado) / conta_aprovado);
    }
    else
    {
        printf("Não houve aprovados!\n");
    }

    free(aprovados);
}

void ma_reprovados(reg_aluno aluno[], int a)
{
    reg_aluno *reprovados;
    int conta_reprovado, b;

    conta_reprovado = 0;

    reprovados = (reg_aluno *)malloc(a * sizeof(reg_aluno));
    if (reprovados == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }

    for (b = 0; b < a; b++)
    {
        if (aluno[b].ma < 6.0)
        {
            reprovados[conta_reprovado] = aluno[b];
            conta_reprovado++;
        }
    }
    if (conta_reprovado > 0)
    {
        printf("A media dos %d reprovado(s) foi de %.2f: \n", conta_reprovado, somarec(reprovados, conta_reprovado) / conta_reprovado);
    }
    else
    {
        printf("Não houve reprovados!\n");
    }

    free(reprovados);
}


/*FUNÇÕES SECUNDÁRIAS*/

float somarec(reg_aluno aluno[], int n)
{
    /*função que realiza a soma de todas as medias finais registradas*/
    if (n == 0)
        return 0;
    return aluno[n - 1].ma + somarec(aluno, n - 1);
}

int buscarec(reg_aluno alunos[], int n, char rga_x[])
{
    /*Função que realiza a busca recursiva com base no RGA*/
    /*Caso n = 0, retorne 0*/
    if (n == 0)
    {
        return -1;
    }
    /*procura se o rga a ser achado é ihual a algum membro do vetor*/
    if (strcmp(alunos[n - 1].rga, rga_x) == 0)
    {
        return n - 1;
    }
    return buscarec(alunos, n - 1, rga_x);
}

/*Realiza a media dos alunos*/
float media(reg_aluno aluno[])
{
    return (0.4 * aluno->p1) + (0.3 * aluno->p2) + (0.3 * aluno->tp);
}

void inserir_ordenado(reg_aluno aluno[], int n, reg_aluno novoaluno)
{
    /*Esta função é feita para que a medida que o usario escreva o seu nome, já insira ordenado,
    sendo assim, não será preciso ordenar novamente*/
    int i, j;

    i = 0;
    while (i < n && strcmp(aluno[i].nome, novoaluno.nome) < 0)
    {
        i++;
    }

    for (j = n; j > i; j--)
    {
        aluno[j] = aluno[j - 1];
    }

    aluno[i] = novoaluno;
}

void troca(reg_aluno *q, reg_aluno *s)
{
    reg_aluno aux;
    aux = *q;
    *q = *s;
    *s = aux;
}

int exibir_alunos(reg_aluno aluno[], int a)
{
    int b, resp;
    resp = 0;
    
    if (a > 0)
    {
        printf("NOME\tP1\tP2\tTP\tMA\n");
        
        for (b = 0; b < a; b++)
        {
            printf("%s\t%.2f\t%.2f\t%.2f\t%.2f\n", 
                   aluno[b].nome, aluno[b].p1, aluno[b].p2, aluno[b].tp, aluno[b].ma);
        }
        resp = 1;
    }
    
    return resp;
}


void ordernar_ma(reg_aluno aluno[], int a)
{
    int b, c;
    for (b = 0; b < a; b++)
    {
        for (c = 0; c < a - b - 1; c++)
        {
            /*Em caso de empate, ele esta ordenando por nome*/
            if ((aluno[c].ma < aluno[c + 1].ma) || (aluno[c].ma == aluno[c + 1].ma && strcmp(aluno[c].nome, aluno[c + 1].nome) > 0))
                troca(&aluno[c], &aluno[c + 1]);
        }
    }
}