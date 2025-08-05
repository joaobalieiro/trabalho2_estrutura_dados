#include <stdio.h>
#include <string.h>
#include "aluno.h"
#include "filme.h"

// estrutura para armazenar o top 3
typedef struct {
    char Nome[50];
    int nUSP;
    int NumFilmes;
} AlunoFilmes;

// variavel global para armazenar o top 3 alunos
AlunoFilmes top3[3];

// funcao para inicializar o top 3
void InicializaTop3() {
    for (int i = 0; i < 3; i++) {
        strcpy(top3[i].Nome, "");
        top3[i].nUSP = 0;
        top3[i].NumFilmes = 0;
    }
}

// funcao para verificar e atualizar o top 3 alunos
void AtualizaTop3(char *nome, int nUSP, int numFilmes) {
    for (int i = 0; i < 3; i++) {
        if (numFilmes > top3[i].NumFilmes) {
            for (int j = 2; j > i; j--) {
                top3[j] = top3[j - 1];
            }
            strcpy(top3[i].Nome, nome);
            top3[i].nUSP = nUSP;
            top3[i].NumFilmes = numFilmes;
            break;
        }
    }
}

// funcao para percorrer a arvore e contar os filmes de cada aluno
void PercorreArvore(TipoApontadorArvore Ap) {
    if (Ap == NULL) return;

    // conta o numero de filmes do aluno atual
    int contagem_filmes = 0;
    FilmeApontador Aux = Ap->Reg.Filmes.Primeiro->Prox;
    while (Aux != NULL) {
        contagem_filmes++;
        Aux = Aux->Prox;
    }

    // atualiza o top 3 com os dados do aluno atual
    AtualizaTop3(Ap->Reg.Nome, Ap->Reg.nUSP, contagem_filmes);

    // percorre as subarvores
    PercorreArvore(Ap->Esq);
    PercorreArvore(Ap->Dir);
}

// funcao para exibir os 3 alunos com mais filmes cadastrados
void Top3AlunosMaisFilmes(TipoApontadorArvore Ap) {
    InicializaTop3();
    PercorreArvore(Ap);

    // exibe os resultados
    printf("\ntop 3 alunos com mais filmes cadastrados:\n");
    for (int i = 0; i < 3; i++) {
        if (top3[i].NumFilmes > 0) {
            printf("%d. %s (usp: %d) - %d filmes\n", i + 1, top3[i].Nome, top3[i].nUSP, top3[i].NumFilmes);
        }
    }
}
