#ifndef FILME_H
#define FILME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definicao de TipoChave
typedef int TipoChave;

// estrutura de um item da lista de filmes
typedef struct {
    TipoChave Chave;
    char Filme[50];
} FilmeItem;

// estrutura de uma celula da lista de filmes
typedef struct FilmeCelula *FilmeApontador;

typedef struct FilmeCelula {
    FilmeItem Item;
    FilmeApontador Prox;
} FilmeCelula;

// estrutura da lista de filmes
typedef struct {
    FilmeApontador Primeiro, Ultimo;
} FilmeLista;

// declaracao antecipada de TipoApontadorArvore
typedef struct TipoNo *TipoApontadorArvore;

// prototipos das operacoes sobre a lista de filmes
void FLVazia(FilmeLista *Lista);
int Vazia(FilmeLista Lista);
void Insere(FilmeItem x, FilmeLista *Lista);
void Retira(FilmeApontador p, FilmeLista *Lista, FilmeItem *Item);
void Imprime(FilmeLista Lista);
int FilmeExiste(FilmeLista *Lista, char *Filme);
void ListaFilmesUnicos(TipoApontadorArvore Ap, FilmeLista *FilmesUnicos);

#endif // FILME_H

