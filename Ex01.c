#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define TAM_ALUNO 30


typedef struct aluno{
    int RA;
    char nome[TAM_ALUNO];
    double nota_primeira_prova;
    double nota_segunda_prova;
    double nota_exercicios;
    struct aluno *prox;
}Aluno;

typedef struct{
    Aluno *ultimo;
    Aluno *primeiro;

}Lista_Alunos_ED1;

double calcular_media(Aluno * aluno){

    return ((aluno->nota_primeira_prova
            + aluno->nota_segunda_prova +
              aluno->nota_exercicios) / 3);
}

int calcular_qtd_alunos(Lista_Alunos_ED1 *lista){

    if(lista == NULL){
        return 0;
    }

    int qtdAlunos = 0;
    Aluno *aux = lista->primeiro;
    while(aux != NULL){
        qtdAlunos++;
        aux = aux->prox;
    }
    return qtdAlunos;
}

bool inserir_registro(Lista_Alunos_ED1 *lista, Aluno *al){

    if(lista == NULL || al == NULL){
        return false;
    }

    if(lista->primeiro == NULL){
        lista->primeiro = al;
        lista->ultimo = al;
    }
    else{
        lista->ultimo->prox = al;
        lista->ultimo = al;
    }

    return true;
}

Aluno *deletar_registro(Lista_Alunos_ED1 *lista, int RA){
   Aluno *atual = lista->primeiro;
   Aluno *anterior = NULL;

   while(atual !=NULL && atual->RA != RA){

    anterior = atual;
    atual = atual->prox;
   }

   if(atual != NULL){
    if(anterior != NULL){
        lista->primeiro = atual->prox;
    }else{
        anterior->prox = atual->prox;
    }
   }
   free(atual);
   return lista->primeiro;
}

void calcular_aprovacoes(Lista_Alunos_ED1 *lista){

    if(lista == NULL || lista->primeiro == NULL){
        printf("A lista esta vazia\n");
        return;
    }

    Aluno *aux = lista->primeiro;
    while(aux != NULL){
        double media = calcular_media(aux);
        if(media < 5.00){
            printf("O aluno %c nao passou pois obteve media %.2f\n", aux->nome, media);
        }else{
            printf("O aluno %c passou pois obteve media %.2f\n", aux->nome, media);
        }
        aux = aux->prox;
    }
}

limparEntradaDeTeclado(){
    fflush(stdin);
}

int main(){

    while(true){

        int qtdAlunos = 0;
        printf("Digite 0 para encerrar o programa\n");
        printf("Quantos alunos deseja inserir:\n");
        scanf(" %d", &qtdAlunos);
        if(qtdAlunos > 50){
            printf("O numero maximo permitido de alunos eh 50\n");
        }
        else if(qtdAlunos == 0){
            return 0;
        }
        else{
            Lista_Alunos_ED1 *lista_alunos_ed1 = malloc(sizeof(Lista_Alunos_ED1));
            for(int i = 0; i < qtdAlunos; i++){

                Aluno *aluno = malloc(sizeof(Aluno));
                printf("\nDigite o RA do aluno \n");
                scanf(" %d", &aluno->RA);

                printf("Digite o nome do aluno\n");
                scanf(" %[^\n]", &aluno->nome);

                printf("Digite a nota da primeira prova do aluno \n");
                scanf(" %f", &aluno->nota_primeira_prova);

                printf("Digite a nota da segunda prova do aluno \n");
                scanf(" %f", &aluno->nota_segunda_prova);

                printf("Digite a nota de exercicios do aluno \n");
                scanf(" %f", &aluno->nota_exercicios);

                if(inserir_registro(lista_alunos_ed1, aluno)){
                    printf("\nRegistro inserido\n");
                    printf("%s\n", aluno->nome);
                }
            }
        }
    }
}
