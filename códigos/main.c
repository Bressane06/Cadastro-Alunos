#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"

int main(void)
{
    int i, user, validacao, *quantidade_alunos;
    char user_char[13];
    reg_aluno aluno[50];

    /*O sistema começa com zero alunos*/
    i = 0;
    do
    {
        printf("\nInforme o numero da ação: \n");
        printf("1- Adiciona usuario;\n");
        printf("2- Remove usuario;\n");
        printf("3- Atualizar notas:\n");
        printf("4- Mostrar todos os alunos aprovados por ordem alfabetica;\n");
        printf("5- Mostrar todos os alunos reprovado por ordem descrescente de nota;\n");
        printf("6- Exibir alguma media, seja dos aprovados, reprovados, ou geral\n");
        printf("7- Finalizar programa;\n------------------------------------------\n-> ");
        scanf("%d", &user);

        switch (user)
        {
        case 1:

            system("clear");

            /*Confirmar que serã inseridos entre 1 a 50 alunos*/
            validacao = 0;
            while (validacao == 0)
            {

                printf("Informe o numero de alunos da turma: ");
                scanf("%d", &i);
                if (i >= 1 && i <= 50)
                    validacao = 1;
                else
                    printf("Quantidade inválida (1 - 50)");
            }

            /*Aloacando memória dinamicamente*/
            quantidade_alunos = (int *)malloc(i * sizeof(int));
            if (quantidade_alunos == NULL)
            {
                printf("Erro ao alocar memória!\n");

                /*O return 1 encerra o programa, pois achou um erro*/
                return 1;
            }

            ler_aluno(aluno, i);

            free(quantidade_alunos);

            break;
        case 2:
            system("clear");

            printf("Informe o RGA do aluno: ");
            scanf(" %s", user_char);
            remover_aluno(aluno, &i, user_char);
            break;
        case 3:
            system("clear");

            printf("Informe o RGA do aluno: ");
            scanf(" %s", user_char);
            notas(aluno, user_char, i);
            break;
        case 4:
            system("clear");

            if (i > 0)
                aprovados(aluno, i);
            else
                printf("Não há aluno registrados");
            break;
        case 5:
            system("clear");

            if (i > 0)
                reprovados(aluno, i);
            else
                printf("Nenhum aluno cadastrado!\n");
            break;
        case 6:    
            system("clear");

            if (i > 0)
            {
                printf("Deseja media de qual?\n1- Aprovados;\n2- Reprovados;\n3- Geral\n");
                scanf("%d", &user);
                switch (user)
                {
                case 1:
                    system("clear");
                    ma_aprovados(aluno, i);
                    break;
                case 2:
                    ma_reprovados(aluno, i);
                    break;
                case 3:
                    printf("A media dos %d aluno(s) foi %.2f\n", i, somarec(aluno, i) / i);
                    break;
                default:
                    printf("Comando inválido");
                    break;
                }
            }
            else
                printf("Nenhum aluno cadastrado!\n");
            break;
        case 7:
            printf("\nFinalizando programa...\n\n");
            break;
        default:
            system("clear");
            printf("Comando errado, insira outro\n");
            break;
        }
    } while (user != 7);

    return 0;
}