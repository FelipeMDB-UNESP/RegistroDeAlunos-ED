#include <stdio.h>
#define TAM_ALUNO = 30


typedef struct{
    int RA;
    int nome[TAM_ALUNO]
    double nota_primeira_prova;
    double nota_segunda_prova;
    double nota_exercicios;
    double media;
    Aluno *prox;
}Aluno;

typedef struct{
    Aluno *ultimo;
     
}Lista_Alunos_ED1;

void matricula_aluno(Lista_Alunos_ED1 *lista, Aluno *al){

    Lista_Alunos_ED1->ultimo->prox = al;
}

double calcular_media(Aluno * aluno){

    return ((aluno->nota_primeira_prova 
            + aluno->nota_segunda_prova +
              aluno->nota_exercicios) / 3);
}

double qtdAlunos

int main(){

}