typedef struct{
    char nome[100];
    char rga[13];
    float p1;
    float p2;
    float tp;
    float ma;
} reg_aluno;

void ler_aluno(reg_aluno aluno[], int numero_alunos);
void remover_aluno(reg_aluno aluno[], int *n, char rga_a_ser_encontrado[]);
void ler_aluno(reg_aluno aluno[], int numero_alunos);
void notas(reg_aluno aluno[], char rga_x[], int i);
void aprovados(reg_aluno aluno[], int n);
void reprovados(reg_aluno alunos[], int a);
void ma_aprovados(reg_aluno aluno[], int a);
void ma_reprovados(reg_aluno aluno[], int a);
float somarec(reg_aluno aluno[], int n);


