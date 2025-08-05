#include <stdio.h>
#include <string.h>
#include "aluno.h"
#include "filme.h"
#include "top3.h"

int main() {
    TipoApontadorArvore Arvore = NULL;
    Inicializa(&Arvore);
    FilmeLista FilmesUnicos;
    FLVazia(&FilmesUnicos);
    int opcao;

    do {
        printf("\nMenu do Sistema:\n");
        printf("1. Criar cadastro de aluno\n");
        printf("2. Listar todos os alunos\n");
        printf("3. Buscar aluno no sistema\n");
        printf("4. Listar filmes diferentes cadastrados\n");
        printf("5. Buscar filme no sistema\n");
        printf("6. Indicar colega para ir ao cinema\n");
        printf("7. Indicar colega com perfil diferente\n");
        printf("8. Exportar dados para arquivo\n");
        printf("9. Exibir dados tecnicos da arvore\n");
        printf("10. Remover aluno do sistema\n");
        printf("11. Mostrar os 3 alunos com mais filmes cadastrados\n"); // funcao extra
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                TipoRegistro aluno;
                char filme[50];
                int continuar;

                // Coleta os dados do aluno
                printf("Informe o numero USP: ");
                scanf("%d", &aluno.nUSP);

                printf("Informe o nome: ");
                scanf(" %[^\n]", aluno.Nome);

                // Inicializa a lista de filmes do aluno
                FLVazia(&aluno.Filmes);

                printf("Digite os nomes dos filmes:\n");
                do {
                    FilmeItem filmeItem;

                    // Coleta o nome do filme
                    printf("Informe o nome do filme: ");
                    scanf(" %[^\n]", filme);

                    // Configura os dados do filme
                    filmeItem.Chave = aluno.Filmes.Ultimo != aluno.Filmes.Primeiro
                                      ? aluno.Filmes.Ultimo->Item.Chave + 1 : 1;
                    strcpy(filmeItem.Filme, filme);

                    // Insere o filme na lista de filmes do aluno
                    Insere(filmeItem, &aluno.Filmes);

                    printf("Deseja adicionar mais filmes? (1 - Sim / 0 - Nao): ");
                    scanf("%d", &continuar);
                } while (continuar == 1);

                // Verificar a lista de filmes antes de salvar na árvore
                printf("Filmes cadastrados para o aluno %s:\n", aluno.Nome);
                Imprime(aluno.Filmes);

                // Copia o aluno para a árvore
                InsereArvore(aluno, &Arvore);

                printf("Aluno cadastrado com sucesso!\n");
                break;
            }

            case 2:
                printf("Lista de alunos:\n");
                ImprimeArvore(Arvore);
                break;

            case 3: {
                int chave;
                printf("Informe o nUSP do aluno a buscar: ");
                scanf("%d", &chave);
                TipoApontadorArvore Alvo = BuscaAluno(Arvore, chave);
                if (Alvo != NULL) {
                    printf("Aluno encontrado: %d - %s\n", Alvo->Reg.nUSP, Alvo->Reg.Nome);
                } else {
                    printf("Aluno nao encontrado!\n");
                }
                break;
            }

            case 4:
                printf("Filmes diferentes cadastrados:\n");
                ListaFilmesUnicos(Arvore, &FilmesUnicos);
                Imprime(FilmesUnicos);
                break;

            case 5: {
                char filme[50];
                printf("Informe o nome do filme a buscar: ");
                scanf(" %[^\n]", filme);
                if (FilmeExiste(&FilmesUnicos, filme)) {
                    printf("Filme '%s' esta cadastrado.\n", filme);
                } else {
                    printf("Filme '%s' nao esta cadastrado.\n", filme);
                }
                break;
            }

            case 6: {
                int chave;
                printf("Informe o nUSP do aluno para recomendacao: ");
                scanf("%d", &chave);
                TipoApontadorArvore Alvo = BuscaAluno(Arvore, chave);
                if (Alvo != NULL) {
                    int MaiorSimilaridade = -1;
                    TipoApontadorArvore Melhor = RecomendaColega(Arvore, Alvo, NULL, &MaiorSimilaridade);
                    if (Melhor != NULL) {
                        printf("Colega recomendado: %s\n", Melhor->Reg.Nome);
                    } else {
                        printf("Nenhum colega recomendado.\n");
                    }
                } else {
                    printf("Aluno nao encontrado.\n");
                }
                break;
            }

            case 7: {
                int chave;
                printf("Informe o nUSP do aluno para recomendacao de perfil diferente: ");
                scanf("%d", &chave);
                TipoApontadorArvore Alvo = BuscaAluno(Arvore, chave);
                if (Alvo != NULL) {
                    int MenorSimilaridade = 10000;
                    TipoApontadorArvore Diferente = IndicaPerfilDiferente(Arvore, Alvo, NULL, &MenorSimilaridade);
                    if (Diferente != NULL) {
                        printf("Colega com perfil diferente: %s\n", Diferente->Reg.Nome);
                    } else {
                        printf("Nenhum colega encontrado.\n");
                    }
                } else {
                    printf("Aluno nao encontrado.\n");
                }
                break;
            }

            case 8: {
                FILE *arquivo = fopen("dados_alunos.txt", "w");
                if (arquivo != NULL) {
                    ExportaArvoreParaArquivo(arquivo, Arvore);
                    fclose(arquivo);
                    printf("Dados exportados com sucesso para 'dados_alunos.txt'.\n");
                } else {
                    printf("Erro ao criar o arquivo!\n");
                }
                break;
            }

            case 9:
                printf("Dados tacnicos da arvore:\n");
                printf("Numero de nos: %d\n", NumeroNos(Arvore));
                printf("Altura da arvore: %d\n", Altura(Arvore));
                ExibeMaiorDiferencaAlturas(Arvore);
                break;

            case 10: {
                int nUSP;
                printf("Informe o nUSP do aluno a remover: ");
                scanf("%d", &nUSP);
                TipoRegistro Alvo;
                Alvo.nUSP = nUSP;
                RetiraArvore(Alvo, &Arvore);
                printf("Aluno removido com sucesso.\n");
                break;
            }

            case 11:
                Top3AlunosMaisFilmes(Arvore);
                break;

            case 0:
                printf("Encerrando o sistema.\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
