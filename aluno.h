#ifndef ALUNO_H
#define ALUNO_H

#include "filme.h"

typedef int TipoChave;

// definicao de registro de um aluno na arvore
typedef struct TipoRegistro {
    char Nome[50];         // nome do aluno
    TipoChave nUSP;       // chave para busca
    FilmeLista Filmes;     // lista de filmes associada ao aluno
} TipoRegistro;

typedef enum {
    Vertical, Horizontal
} TipoInclinacao;

typedef struct TipoNo* TipoApontadorArvore;

typedef struct TipoNo {
    TipoRegistro Reg;
    TipoApontadorArvore Esq, Dir;
    TipoInclinacao BitE, BitD;
} TipoNo;

// Funções auxiliares para rotação
void EE(TipoApontadorArvore *Ap);
void ED(TipoApontadorArvore *Ap);
void DD(TipoApontadorArvore *Ap);
void DE(TipoApontadorArvore *Ap);

// Operações básicas na Árvore SBB
void Inicializa(TipoApontadorArvore *Dicionario);
void InsereArvore(TipoRegistro x, TipoApontadorArvore *Ap);
void RetiraArvore(TipoRegistro x, TipoApontadorArvore *Ap);
void AdicionaFilmeNaFolha(TipoApontadorArvore Ap, TipoChave chave, FilmeItem filme);
void ImprimeArvore(TipoApontadorArvore Ap);
TipoApontadorArvore RecomendaColega(TipoApontadorArvore Ap, TipoApontadorArvore Alvo, TipoApontadorArvore Melhor, int *MaiorSimilaridade);
int Altura(TipoApontadorArvore Ap);
int NumeroNos(TipoApontadorArvore Ap);
void MaiorDiferencaAlturas(TipoApontadorArvore Ap, int *maiorDiferenca);
void ExibeMaiorDiferencaAlturas(TipoApontadorArvore Ap);
void ExportaArvoreParaArquivo(FILE *arquivo, TipoApontadorArvore Ap);

// Funções internas auxiliares (não recomendadas para uso externo)
void IInsere(TipoRegistro x, TipoApontadorArvore *Ap, TipoInclinacao *IAp, short *Fim);
void IRetira(TipoRegistro x, TipoApontadorArvore *Ap, short *Fim);
void EsqCurto(TipoApontadorArvore *Ap, short *Fim);
void DirCurto(TipoApontadorArvore *Ap, short *Fim);
void Antecessor(TipoApontadorArvore q, TipoApontadorArvore *r, short *Fim);
void ImprimeFilmes(FilmeLista Lista);
int Similaridade(FilmeLista *Filmes1, FilmeLista *Filmes2);
TipoApontadorArvore BuscaAluno(TipoApontadorArvore Ap, TipoChave chave);
TipoApontadorArvore IndicaPerfilDiferente(TipoApontadorArvore Ap, TipoApontadorArvore Alvo, TipoApontadorArvore Diferente, int *MenorSimilaridade);


#endif // ALUNO_H
