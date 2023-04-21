#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define TAM_ALUNO 30


typedef struct aluno{
    int RA;
    char nome[TAM_ALUNO];
    float nota_primeira_prova;
    float nota_segunda_prova;
    float nota_exercicios;
    struct aluno *prox;
}Aluno;

typedef struct{
    Aluno *ultimo;
    Aluno *primeiro;

}Lista_Alunos_ED1;

float calcular_media(Aluno * aluno){

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

Aluno *inserir_registro(Lista_Alunos_ED1 *lista, Aluno *al){

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

    return lista->primeiro;
}

Aluno *deletar_registro(Lista_Alunos_ED1 *lista, int RA){
    Aluno *atual = lista->primeiro;
    Aluno *anterior = NULL;

    while(atual != NULL && atual->RA != RA){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual != NULL){
        if(anterior != NULL){
            anterior->prox = atual->prox;
        }else{
            lista->primeiro = atual->prox;
        }
        printf("Registro de %s deletado\n", atual->nome);
        free(atual);
    }else{
        printf("Registro de RA %d não encontrado\n", RA);
    }

    return lista->primeiro;
}

void calcular_aprovacoes(Aluno *primeiro_aluno){

    if(primeiro_aluno == NULL){
        printf("A lista esta vazia\n");
        return;
    }

    Aluno *aux = primeiro_aluno;
    while(aux != NULL){
        float media = calcular_media(aux);
        if(media < 5.00){
            printf("O aluno %s nao passou pois obteve media %.2f\n", aux->nome, media);
        }else if(media >= 5.00){
            printf("O aluno %s passou pois obteve media %.2f\n", aux->nome, media);
        }
        aux = aux->prox;
    }
}

void limpar_entrada_de_teclado(){
    fflush(stdin);
}


void copiar_dados_aluno(Aluno *a, Aluno *b){
    strcpy(a->nome, b->nome);
    a->nota_exercicios = b->nota_exercicios;
    a->nota_primeira_prova = b->nota_primeira_prova;
    a->nota_segunda_prova = b->nota_segunda_prova;
    a->RA = b->RA;
}

void medias_notas_discrepantes(Lista_Alunos_ED1 *lista){

    Aluno *aluno_menor_media = malloc(sizeof(Aluno));
    aluno_menor_media->nota_exercicios = 11;
    aluno_menor_media->nota_primeira_prova = 11;
    aluno_menor_media->nota_segunda_prova = 11;

    Aluno *aluno_maior_media = malloc(sizeof(Aluno));
    aluno_maior_media->nota_exercicios = -1;
    aluno_maior_media->nota_primeira_prova = -1;
    aluno_maior_media->nota_segunda_prova = -1;

    Aluno *aluno_maior_nota_primeira_prova = malloc(sizeof(Aluno));
    aluno_maior_nota_primeira_prova->nota_primeira_prova = 0;

    if(lista == NULL || lista->primeiro == NULL){
        printf("A lista esta vazia\n");
        return;
    }
    Aluno *aux = lista->primeiro;
    while (aux != NULL){
        float aux_media = calcular_media(aux);
        if(aux_media < calcular_media(aluno_menor_media)){
            copiar_dados_aluno(aluno_menor_media, aux);
        }
        if(aux_media > calcular_media(aluno_maior_media)){
            copiar_dados_aluno(aluno_maior_media, aux);
        }

        if(aux->nota_primeira_prova > aluno_maior_nota_primeira_prova->nota_primeira_prova){
            copiar_dados_aluno(aluno_maior_nota_primeira_prova, aux);
        }
        aux = aux->prox;
    }

    printf("\n O aluno com a maior media foi: %s\nCom media: %.2f\n",
     aluno_maior_media->nome, calcular_media(aluno_maior_media));
    printf("\n O aluno com a menor media foi: %s\nCom media: %.2f\n",
     aluno_menor_media->nome, calcular_media(aluno_menor_media));
    printf("\n O aluno com a maior nota na primeira prova foi: %s\nCom nota: %.2f\n",
     aluno_maior_nota_primeira_prova->nome, aluno_maior_nota_primeira_prova->nota_primeira_prova);
     
}

void esperar(){

    char var_de_espera[100];
    printf("Pressione [ENTER] para continuar\n");
    scanf("%c", &var_de_espera);
    getchar();
}

int main(){
    
    Lista_Alunos_ED1 *lista_alunos_ed1 = malloc(sizeof(Lista_Alunos_ED1));
    int qtdAlunos = 0;
    while(true){
        printf("Digite [0] para encerrar o programa\n");
        printf("----------\n");
        printf("Digite [51] para deletar registros\n");
        printf("----------\n");
        printf("Digite [52] para calcular aprovacoes\n");
        printf("----------\n");
        printf("Digite [53] para ver quais sao os alunos com maiores medias e notas\n");
        printf("----------\n");
        printf("Digite qualquer outro numero < 50 para quantos alunos deseja inserir:\n");
        scanf(" %d", &qtdAlunos);
        if(qtdAlunos > 53 || qtdAlunos < 0){
            printf("O numero maximo permitido de alunos eh 50\n");
            esperar();
        }
        if(qtdAlunos == 0){
            return 0;
        }
        else if(qtdAlunos == 51){
            printf("\n----------------------------\n");
            printf("\nInforme o RA do aluno a ser deletado:\n");
            int ra_para_deletar;
            limpar_entrada_de_teclado();
            scanf(" %d", &ra_para_deletar);
            lista_alunos_ed1->primeiro = deletar_registro(lista_alunos_ed1, ra_para_deletar);
            printf("\n----------------------------\n");
            esperar();
            
        }
        else if(qtdAlunos == 52){
            printf("\n----------------------------\n");
            calcular_aprovacoes(lista_alunos_ed1->primeiro);
            printf("\n----------------------------\n");
            esperar();
        }
        else if(qtdAlunos == 53){
            printf("\n----------------------------\n");
            medias_notas_discrepantes(lista_alunos_ed1);
            printf("\n----------------------------\n");
            esperar();
        }
        else{
            if(calcular_qtd_alunos(lista_alunos_ed1) > 50){

                printf("\n NUMERO MAXIMO DE ALUNOS CADASTRADOS JA FOI ATINGIDO");
            }
            for(int i = 0; i < qtdAlunos; i++){

                printf("Insercao %d de %d:", i, qtdAlunos);

                Aluno *aluno = malloc(sizeof(Aluno));
                printf("\nDigite o RA do aluno: \n");
                scanf(" %d", &aluno->RA);

                printf("Digite o nome do aluno:\n");
                scanf(" %[^\n]", &aluno->nome);

                printf("Digite a nota da primeira prova do aluno: \n");
                scanf("%f", &aluno->nota_primeira_prova);

                printf("Digite a nota da segunda prova do aluno: \n");
                scanf("%f", &aluno->nota_segunda_prova);

                printf("Digite a nota de exercicios do aluno: \n");
                scanf("%f", &aluno->nota_exercicios);

                lista_alunos_ed1->primeiro = inserir_registro(lista_alunos_ed1, aluno);
                    printf("\nRegistro inserido %d de %d\n", i+1, qtdAlunos);
                    printf("Segue abaixo listados os dados inseridos:\n\n");
                    printf("Nome: %s\n", aluno->nome);
                    printf("RA: %d\n", aluno->RA);
                    printf("Nota da primeira prova: %.2f\n", aluno->nota_primeira_prova);
                    printf("Nota da segunda prova: %.2f\n", aluno->nota_segunda_prova);
                    printf("Nota de exercicios: %.2f\n", aluno->nota_exercicios);
                
            }
            qtdAlunos = 0;
            printf("\n-------------------------------------\n");
        }
    }
}
