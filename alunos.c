#include <stdio.h>
#include <stdlib.h>
#include "filme.h"
#include "aluno.h"

// define a estrutura de uma arvore sbb

typedef int TipoChave;

// realiza rotacao simples para a esquerda corrigindo a arvore sbb
void EE(TipoApontadorArvore *Ap) {
    TipoApontadorArvore Ap1;
    Ap1 = (*Ap)->Esq;
    (*Ap)->Esq = Ap1->Dir;
    Ap1->Dir = *Ap;
    Ap1->BitE = Vertical;
    (*Ap)->BitE = Vertical;
    *Ap = Ap1;
}

// realiza rotacao dupla esquerda direita corrigindo a arvore sbb
void ED(TipoApontadorArvore *Ap) {
    TipoApontadorArvore Ap1, Ap2;
    Ap1 = (*Ap)->Esq;
    Ap2 = Ap1->Dir;
    Ap1->BitD = Vertical;
    (*Ap)->BitE = Vertical;
    Ap1->Dir = Ap2->Esq;
    Ap2->Esq = Ap1;
    (*Ap)->Esq = Ap2->Dir;
    Ap2->Dir = *Ap;
    *Ap = Ap2;
}

// realiza rotacao simples para a direita corrigindo a arvore sbb
void DD(TipoApontadorArvore *Ap) {
    TipoApontadorArvore Ap1;
    Ap1 = (*Ap)->Dir;
    (*Ap)->Dir = Ap1->Esq;
    Ap1->Esq = *Ap;
    Ap1->BitD = Vertical;
    (*Ap)->BitD = Vertical;
    *Ap = Ap1;
}

// realiza rotacao dupla direita esquerda corrigindo a arvore sbb
void DE(TipoApontadorArvore *Ap) {
    TipoApontadorArvore Ap1, Ap2;
    Ap1 = (*Ap)->Dir;
    Ap2 = Ap1->Esq;
    Ap1->BitE = Vertical;
    (*Ap)->BitD = Vertical;
    Ap1->Esq = Ap2->Dir;
    Ap2->Dir = Ap1;
    (*Ap)->Dir = Ap2->Esq;
    Ap2->Esq = *Ap;
    *Ap = Ap2;
}

// insere um novo registro na arvore sbb ajustando apontadores e inclinacoes
void IInsere(TipoRegistro x, TipoApontadorArvore *Ap, TipoInclinacao *IAp, short *Fim) {
    if (*Ap == NULL) {
        *Ap = (TipoApontadorArvore) malloc(sizeof(TipoNo));
        (*Ap)->Reg = x; // Copia o registro do aluno
        (*Ap)->BitE = Vertical;
        (*Ap)->BitD = Vertical;
        (*Ap)->Esq = NULL;
        (*Ap)->Dir = NULL;

        // Inicializa a lista de filmes na folha
        FLVazia(&((*Ap)->Reg.Filmes));
        FilmeApontador Aux = x.Filmes.Primeiro->Prox;
        while (Aux != NULL) {
            FilmeItem filme;
            filme.Chave = Aux->Item.Chave;
            strcpy(filme.Filme, Aux->Item.Filme);
            Insere(filme, &((*Ap)->Reg.Filmes));
            Aux = Aux->Prox;
        }

        *Fim = 1;
        return;
    }

    if (x.nUSP < (*Ap)->Reg.nUSP) {
        IInsere(x, &(*Ap)->Esq, &(*Ap)->BitE, Fim);
        return;
    } else if (x.nUSP > (*Ap)->Reg.nUSP) {
        IInsere(x, &(*Ap)->Dir, &(*Ap)->BitD, Fim);
        return;
    } else {
        printf("Erro: Chave duplicada na árvore.\n");
        *Fim = 1;
    }
}

// insere um registro na arvore sbb inicializando o processo de insercao
void InsereArvore(TipoRegistro x, TipoApontadorArvore *Ap) {
    short Fim;
    TipoInclinacao IAp;
    IInsere(x, Ap, &IAp, &Fim);
}

// inicializa a arvore definindo a raiz como null
void Inicializa(TipoApontadorArvore *Dicionario) {
    *Dicionario = NULL;
}

// realiza balanceamento apos remocao na subarvore esquerda
void EsqCurto(TipoApontadorArvore *Ap, short *Fim) {
    TipoApontadorArvore Ap1;
    if ((*Ap)->BitE == Horizontal) {
        (*Ap)->BitE = Vertical;
        *Fim = 1;
        return;
    }
    if ((*Ap)->BitD == Horizontal) {
        Ap1 = (*Ap)->Dir;
        (*Ap)->Dir = Ap1->Esq;
        Ap1->Esq = *Ap;
        *Ap = Ap1;
        if ((*Ap)->Esq->Dir->BitE == Horizontal) {
            DE(&(*Ap)->Esq);
            (*Ap)->BitE = Horizontal;
        } else if ((*Ap)->Esq->Dir->BitD == Horizontal) {
            DD(&(*Ap)->Esq);
            (*Ap)->BitE = Horizontal;
        }
        *Fim = 1;
        return;
    }
    (*Ap)->BitD = Horizontal;
    if ((*Ap)->Dir->BitE == Horizontal) {
        DE(Ap);
        *Fim = 1;
        return;
    }
    if ((*Ap)->Dir->BitD == Horizontal) {
        DD(Ap);
        *Fim = 1;
    }
}

// realiza balanceamento apos remocao na subarvore direita
void DirCurto(TipoApontadorArvore *Ap, short *Fim) {
    TipoApontadorArvore Ap1;
    if ((*Ap)->BitD == Horizontal) {
        (*Ap)->BitD = Vertical;
        *Fim = 1;
        return;
    }
    if ((*Ap)->BitE == Horizontal) {
        Ap1 = (*Ap)->Esq;
        (*Ap)->Esq = Ap1->Dir;
        Ap1->Dir = *Ap;
        *Ap = Ap1;
        if ((*Ap)->Dir->Esq->BitD == Horizontal) {
            ED(&(*Ap)->Dir);
            (*Ap)->BitD = Horizontal;
        } else if ((*Ap)->Dir->Esq->BitE == Horizontal) {
            EE(&(*Ap)->Dir);
            (*Ap)->BitD = Horizontal;
        }
        *Fim = 1;
        return;
    }
    (*Ap)->BitE = Horizontal;
    if ((*Ap)->Esq->BitD == Horizontal) {
        ED(Ap);
        *Fim = 1;
        return;
    }
    if ((*Ap)->Esq->BitE == Horizontal) {
        EE(Ap);
        *Fim = 1;
    }
}

// encontra o antecessor de um no durante a remocao
void Antecessor(TipoApontadorArvore q, TipoApontadorArvore *r, short *Fim) {
    if ((*r)->Dir != NULL) {
        Antecessor(q, &(*r)->Dir, Fim);
        if (!*Fim) DirCurto(r, Fim);
        return;
    }
    q->Reg = (*r)->Reg;
    q = *r;
    *r = (*r)->Esq;
    free(q);
    if (*r != NULL) *Fim = 1;
}

// remove um registro da arvore ajustando apontadores e inclinacoes
void IRetira(TipoRegistro x, TipoApontadorArvore *Ap, short *Fim) {
    TipoNo *Aux;
    if (*Ap == NULL) {
        printf("chave nao esta na arvore\n");
        *Fim = 1;
        return;
    }
    if (x.nUSP < (*Ap)->Reg.nUSP) {
        IRetira(x, &(*Ap)->Esq, Fim);
        if (!*Fim) EsqCurto(Ap, Fim);
        return;
    }
    if (x.nUSP < (*Ap)->Reg.nUSP) {
        IRetira(x, &(*Ap)->Dir, Fim);
        if (!*Fim) DirCurto(Ap, Fim);
        return;
    }
    *Fim = 0;
    Aux = *Ap;
    if (Aux->Dir == NULL) {
        *Ap = Aux->Esq;
        free(Aux);
        if (*Ap != NULL) *Fim = 1;
        return;
    }
    if (Aux->Esq == NULL) {
        *Ap = Aux->Dir;
        free(Aux);
        if (*Ap != NULL) *Fim = 1;
        return;
    }
    Antecessor(Aux, &Aux->Esq, Fim);
    if (!*Fim) EsqCurto(Ap, Fim);
}

// remove um registro da arvore sbb
void RetiraArvore(TipoRegistro x, TipoApontadorArvore *Ap) {
    short Fim;
    IRetira(x, Ap, &Fim);
}

// adiciona um filme na lista associada a uma folha com a chave especificada
void AdicionaFilmeNaFolha(TipoApontadorArvore Ap, TipoChave chave, FilmeItem filme) {
    if (Ap == NULL) {
        printf("chave %d nao encontrada na arvore\n", chave);
        return;
    }
    if (chave < Ap->Reg.nUSP) {
        AdicionaFilmeNaFolha(Ap->Esq, chave, filme);
    } else if (chave > Ap->Reg.nUSP) {
        AdicionaFilmeNaFolha(Ap->Dir, chave, filme);
    } else {
        Insere(filme, &(Ap->Reg.Filmes));
    }
}


// imprime todos os filmes de uma lista associada a uma folha
void ImprimeFilmes(FilmeLista Lista) {
    FilmeApontador Aux = Lista.Primeiro->Prox; // utiliza o novo tipo FilmeApontador
    while (Aux != NULL) {
        printf("  - %s\n", Aux->Item.Filme); // imprime o nome do filme
        Aux = Aux->Prox; // avanca para a proxima celula
    }
}

// percorre e imprime a arvore exibindo os registros e suas listas de filmes
void ImprimeArvore(TipoApontadorArvore Ap) {
    if (Ap == NULL) return;
    ImprimeArvore(Ap->Esq);
    printf("no nusp = %d nome = %s\n", Ap->Reg.nUSP, Ap->Reg.Nome);
    printf("lista de filmes:\n");
    ImprimeFilmes(Ap->Reg.Filmes);
    ImprimeArvore(Ap->Dir);
}

int Similaridade(FilmeLista *Filmes1, FilmeLista *Filmes2) {
    FilmeApontador Aux1 = Filmes1->Primeiro->Prox;
    int Similares = 0;

    while (Aux1 != NULL) {
        if (FilmeExiste(Filmes2, Aux1->Item.Filme)) {
            Similares++;
        }
        Aux1 = Aux1->Prox;
    }

    return Similares;
}

TipoApontadorArvore RecomendaColega(TipoApontadorArvore Ap, TipoApontadorArvore Alvo, TipoApontadorArvore Melhor, int *MaiorSimilaridade) {
    if (Ap == NULL) return Melhor;

    if (Ap != Alvo) {
        int Similar = Similaridade(&(Ap->Reg.Filmes), &(Alvo->Reg.Filmes)); // calcula similaridade
        if (Similar > *MaiorSimilaridade) { // usa a variavel Similar
            *MaiorSimilaridade = Similar; // atualiza MaiorSimilaridade
            Melhor = Ap; // atualiza Melhor
        }
    }

    Melhor = RecomendaColega(Ap->Esq, Alvo, Melhor, MaiorSimilaridade);
    Melhor = RecomendaColega(Ap->Dir, Alvo, Melhor, MaiorSimilaridade);

    return Melhor;
}

TipoApontadorArvore BuscaAluno(TipoApontadorArvore Ap, TipoChave chave) {
    if (Ap == NULL) return NULL;
    if (chave < Ap->Reg.nUSP) return BuscaAluno(Ap->Esq, chave);
    if (chave > Ap->Reg.nUSP) return BuscaAluno(Ap->Dir, chave);
    return Ap; // encontrou o aluno
}

TipoApontadorArvore IndicaPerfilDiferente(TipoApontadorArvore Ap, TipoApontadorArvore Alvo, TipoApontadorArvore Diferente, int *MenorSimilaridade) {
    if (Ap == NULL) return Diferente;

    if (Ap != Alvo) {
        int Similar = Similaridade(&(Ap->Reg.Filmes), &(Alvo->Reg.Filmes)); // calcula similaridade
        if (Similar < *MenorSimilaridade) { // verifica menor similaridade
            *MenorSimilaridade = Similar;
            Diferente = Ap; // atualiza o perfil mais diferente
        }
    }

    Diferente = IndicaPerfilDiferente(Ap->Esq, Alvo, Diferente, MenorSimilaridade);
    Diferente = IndicaPerfilDiferente(Ap->Dir, Alvo, Diferente, MenorSimilaridade);

    return Diferente;
}

int Altura(TipoApontadorArvore Ap) {
    if (Ap == NULL) return 0;
    int AlturaEsq = Altura(Ap->Esq);
    int AlturaDir = Altura(Ap->Dir);
    return 1 + (AlturaEsq > AlturaDir ? AlturaEsq : AlturaDir);
}

int NumeroNos(TipoApontadorArvore Ap) {
    if (Ap == NULL) return 0;
    return 1 + NumeroNos(Ap->Esq) + NumeroNos(Ap->Dir);
}

void MaiorDiferencaAlturas(TipoApontadorArvore Ap, int *maiorDiferenca) {
    if (Ap == NULL) return;

    int alturaEsq = Altura(Ap->Esq);
    int alturaDir = Altura(Ap->Dir);
    int diferenca = abs(alturaEsq - alturaDir);

    if (diferenca > *maiorDiferenca) {
        *maiorDiferenca = diferenca;
    }

    MaiorDiferencaAlturas(Ap->Esq, maiorDiferenca);
    MaiorDiferencaAlturas(Ap->Dir, maiorDiferenca);
}

void ExibeMaiorDiferencaAlturas(TipoApontadorArvore Ap) {
    int maiorDiferenca = 0;
    MaiorDiferencaAlturas(Ap, &maiorDiferenca);
    printf("A maior diferença de alturas entre subarvores de qualquer no e: %d\n", maiorDiferenca);
}

void ExportaArvoreParaArquivo(FILE *arquivo, TipoApontadorArvore Ap) {
    if (Ap == NULL) return;
    ExportaArvoreParaArquivo(arquivo, Ap->Esq);
    fprintf(arquivo, "Aluno: %d - %s\n", Ap->Reg.nUSP, Ap->Reg.Nome);
    fprintf(arquivo, "Filmes:\n");
    FilmeApontador Aux = Ap->Reg.Filmes.Primeiro->Prox;
    while (Aux != NULL) {
        fprintf(arquivo, "  - %s\n", Aux->Item.Filme);
        Aux = Aux->Prox;
    }
    ExportaArvoreParaArquivo(arquivo, Ap->Dir);
}
