#ifndef TOP3_H
#define TOP3_H

#include <stdio.h>
#include <string.h>
#include "aluno.h"
#include "filme.h"

// Estrutura para armazenar o top 3
typedef struct {
    char Nome[50];
    int nUSP;
    int NumFilmes;
} AlunoFilmes;

// Declaração da variável global para armazenar o top 3 alunos
extern AlunoFilmes top3[3];

// Função para inicializar o top 3
void InicializaTop3();

// Função para verificar e atualizar o top 3 alunos
void AtualizaTop3(char *nome, int nUSP, int numFilmes);

// Função para percorrer a árvore e contar os filmes de cada aluno
void PercorreArvore(TipoApontadorArvore Ap);

// Função para exibir os 3 alunos com mais filmes cadastrados
void Top3AlunosMaisFilmes(TipoApontadorArvore Ap);

#endif // TOP3_H

