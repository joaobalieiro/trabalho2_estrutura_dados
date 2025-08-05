#include "filme.h"
#include "aluno.h"
#include <string.h>

// inicializa uma lista de filmes vazia criando a celula cabeca
void FLVazia(FilmeLista *Lista) {
    Lista->Primeiro = (FilmeApontador) malloc(sizeof(FilmeCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

// insere um filme na lista de forma ordenada em ordem alfabetica pelo nome do filme
void Insere(FilmeItem x, FilmeLista *Lista) {
    FilmeApontador Aux = Lista->Primeiro;
    FilmeApontador Novo = (FilmeApontador) malloc(sizeof(FilmeCelula));
    Novo->Item = x;

    while (Aux->Prox != NULL && strcmp(Aux->Prox->Item.Filme, x.Filme) < 0) {
        Aux = Aux->Prox;
    }

    Novo->Prox = Aux->Prox;
    Aux->Prox = Novo;

    if (Novo->Prox == NULL) {
        Lista->Ultimo = Novo;
    }
}

// percorre e imprime os filmes na lista
void Imprime(FilmeLista Lista) {
    FilmeApontador Aux = Lista.Primeiro->Prox;

    while (Aux != NULL) {
        printf("  - %s\n", Aux->Item.Filme);
        Aux = Aux->Prox;
    }
}

// verifica se um filme ja existe na lista
int FilmeExiste(FilmeLista *Lista, char *Filme) {
    FilmeApontador Aux = Lista->Primeiro->Prox;
    while (Aux != NULL) {
        if (strcmp(Aux->Item.Filme, Filme) == 0) return 1; // encontrou o filme
        Aux = Aux->Prox;
    }
    return 0; // nao encontrou o filme
}

// lista todos os filmes unicos da arvore em ordem alfabetica
void ListaFilmesUnicos(TipoApontadorArvore Ap, FilmeLista *FilmesUnicos) {
    if (Ap == NULL) return;

    ListaFilmesUnicos(Ap->Esq, FilmesUnicos);

    FilmeApontador Aux = Ap->Reg.Filmes.Primeiro->Prox;
    while (Aux != NULL) {
        if (!FilmeExiste(FilmesUnicos, Aux->Item.Filme)) {
            Insere(Aux->Item, FilmesUnicos);
        }
        Aux = Aux->Prox;
    }

    ListaFilmesUnicos(Ap->Dir, FilmesUnicos);
}
