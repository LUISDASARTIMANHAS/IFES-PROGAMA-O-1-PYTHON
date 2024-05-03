/*
  Rede Neural Artificial Evolutiva (RNA-E)

  Os pesos são atualizados a partir de um algoritmo
  genético que busca minimizar os erros na fase de
  treinamento.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_Entradas 2
#define MAX_Pesos 6

//===| Estrutura de Dados |==========================
typedef char string[60];

typedef struct tipoLicao
{
    int p;                 // proposição P
    int q;                 // Proposição Q
    int resultadoEsperado; // Proposição Composta P "E" Q (A Classe)
    tipoLicao *prox;
} TLicao;

typedef struct tipoIndividuo
{
    float genes[MAX_Pesos];
    int erros;
    int numero; // numero identificador
    tipoIndividuo *prox;
} TIndividuo;

typedef struct tipoSinapse
{
    int camada;
    int neuronio_origem;
    int neuronio_destino;
    float peso;
    tipoSinapse *prox;
} TSinapse;

typedef struct tipoNeuronio
{
    int neuronio;
    float soma;
    float peso;
    tipoNeuronio *prox;
} TNeuronio;

typedef struct tipoLista
{
    FILE *fp; // Arquivo de Saída (Relatório).
    string objetivo;
    TLicao *licoes; // Conjunto de lições a serem aprendidas
    float entradas[MAX_Entradas];
    TNeuronio *neuronios;
    TSinapse *pesos;
    TIndividuo *populacao;
    TIndividuo *individuoAtual;
    int totalIndividuos;
    int Qtd_Populacao;
    int Qtd_Mutacoes_por_vez;
    int Total_geracoes;
    int geracao_atual;
    int Qtd_Geracoes_para_Mutacoes;
    float sinapseThreshold;
    float learningRate;
} TLista;

TLista lista;

//====| Assinatura de Funções |=======================+
void inicializa(TLista *L);
void geraIndividuos(TLista *L);
void geraLicoes(TLista *L);
void insereLicao(TLista *L, int p, int q, int resultado);
void insereNeuronio(TLista *L, int neuronio);
void estabelecendoSinapse(TLista *L, int neuronioDe, int neuronioAte, int camada);
void treinamento(TLista *L);
void cruzamento(TLista *L);
void avaliacaoIndividuos(TLista *L);
void ordenamentoIndividuos(TLista *L);
void promoveMutacoes(TLista *L);
void poda(TLista *L);
//===| Programa Principal |===========================
int main()
{
    inicializa(&lista);
    treinamento(&lista);
}
//===| Funções |======================================
void inicializa(TLista *L)
{
    int i;

    L->licoes = NULL;
    L->populacao = NULL;
    L->individuoAtual = NULL;
    L->totalIndividuos = 0;

    for (i = 0; i < MAX_Entradas; i++)
    {
        L->entradas[i] = 0;
    } // for

    L->neuronios = NULL;
    L->pesos = NULL;

    printf("\t\t=====| REDE NEURAL ARTIFICIAL EVOLUTIVA |=====");
    printf("\n\n\t\t=====| Configuracao da RNA |=====\n\n");
    printf("\tInforme o TAMANHO da POPULACAO (em termos de individuos):\n");
    printf("\t\tSugestao: 300 individuos.\n\t\tValor: ");
    scanf("%d", &L->Qtd_Populacao);

    geraIndividuos(L);

    printf("\n\n\tInforme a QUANTIDADE de GERACOES maxima:");
    printf("\n\tSugestao: 100 geracoes no total.\n\tValor: ");
    scanf("%d", &L->Total_geracoes);

    L->geracao_atual = 0;

    printf("\n\n\tInforme o INTERVALO de GERACOES para a ocorrencia de MUTACOES:");
    printf("\n\tSugestao: 5 (a cada 5 geracoes devem ocorrer mutacoes).\n\tValor: ");
    scanf("%d", &L->Qtd_Geracoes_para_Mutacoes);

    printf("\n\n\tInforme a QUANTIDADE de MUTACOES que devem ocorrer POR VEZ:");
    printf("\n\tSugestao: 3 mutacoes por intervalo.\n\tValor: ");
    scanf("%d", &L->Qtd_Mutacoes_por_vez);

    printf("\n\nSINAPSE THRESHOLD (Limiar das Conexoes entre Neuronios):\n");
    printf("Define a intensidade do sinal que sensibiliza cada neuronio.\n\n");
    printf("\tInforme o SINAPSE THRESHOLD:\n\tSugestao: 0.60\n\tValor: ");
    scanf("%f", &L->sinapseThreshold);

    printf("\n\nLEARNING RATE (Taxa de Aprendizado): variacao dos pesos em cada ajuste (Aprendizado).\n");
    printf("\n\tLEARNING RATE:\n\tSugestao: 0.20\n\tValor: ");
    scanf("%f", &L->learningRate);

    strcpy(L->objetivo, "Aprendizado da Funcao Logica P E Q");

    printf("\n\n\tDefinindo as LICOES a serem aprendidas pela Rede Neural Artificial.\n\n");
    geraLicoes(L);

    printf("\n\n\tDefinindo os NEURONIOS que compoem a REDE NEURAL ARTIFICIAL.");
    insereNeuronio(L, 1);
    insereNeuronio(L, 2);
    insereNeuronio(L, 3);
    insereNeuronio(L, 4);
    insereNeuronio(L, 5);

    printf("\n\n\tEstabelecendo as CONEXOES (Sinapses) entre os NEURONIOS.");
    estabelecendoSinapse(L, 1, 3, 0);
    estabelecendoSinapse(L, 1, 4, 0);
    estabelecendoSinapse(L, 2, 3, 0);
    estabelecendoSinapse(L, 2, 4, 0);
    estabelecendoSinapse(L, 3, 5, 1);
    estabelecendoSinapse(L, 4, 5, 1);

    L->fp = fopen("RNA_EVOLUTIVA_RELATORIO.TXT", "w");

    fprintf(L->fp, "\n\t\t=====| REDE NEURAL ARTIFICIAL EVOLUTIVA |=====\n\n");
    fprintf(L->fp, "\tOBJETIVO: %s.\n\n\tLicoes:\n", L->objetivo);
    fprintf(L->fp, "\t LICAO    P    Q  (Resultado Esperado)\n");
    fprintf(L->fp, "\t+------+----+----+---------------------+\n");

    TLicao *licao = L->licoes;
    int cont = 0;
    while (licao != NULL)
    {
        fprintf(L->fp, "\t(%d) - %d   %d   %d\n", ++cont, licao->p, licao->q, licao->resultadoEsperado);
        licao = licao->prox;
    } // while

    fprintf(L->fp, "\n\n");
    fprintf(L->fp, "\tLearning Rate: %.2f\n", L->learningRate);
    fprintf(L->fp, "\tSinapse Threshold: %.2f\n", L->sinapseThreshold);
    fprintf(L->fp, "\tPopulacao MAXIMA: %d.\n", L->Qtd_Populacao);
    fprintf(L->fp, "\t%d MUTACOES a cada sequencia de %d GERACOES.\n", L->Qtd_Mutacoes_por_vez, L->Qtd_Geracoes_para_Mutacoes);
    fprintf(L->fp, "\tTOTAL de GERACOES: %d.\n\n\n", L->Total_geracoes);

    printf("\n\n\tConfiguracao FINALIZADA!!!\n\n");
}
//====================================================
void geraIndividuos(TLista *L)
{
    TIndividuo *novo;
    int i, x;

    srand((unsigned)time(NULL));

    for (i = 0; i < L->Qtd_Populacao; i++)
    {
        novo = (TIndividuo *)malloc(sizeof(TIndividuo));

        novo->prox = NULL;
        novo->numero = i + 1;
        novo->erros = -1;

        for (x = 0; x < MAX_Pesos; x++)
        {
            novo->genes[x] = rand() % 101;
            novo->genes[x] = novo->genes[x] / 100;
        } // for

        if (L->populacao == NULL)
        {
            L->populacao = novo;
        }
        else
        {
            TIndividuo *atual = L->populacao;

            while (atual->prox != NULL)
            {
                atual = atual->prox;
            } // while

            atual->prox = novo;
        } // if

        L->totalIndividuos++;
    } // for
}
//=====================================================
void geraLicoes(TLista *L)
{
    TLicao *novo;
    int p, q;

    insereLicao(L, 0, 0, 0);
    insereLicao(L, 0, 1, 0);
    insereLicao(L, 1, 0, 0);
    insereLicao(L, 1, 1, 1);
}
//=====================================================
void insereLicao(TLista *L, int p, int q, int resultado)
{
    TLicao *novo = (TLicao *)malloc(sizeof(TLicao));

    novo->prox = NULL;
    novo->p = p;
    novo->q = q;
    novo->resultadoEsperado = resultado;

    if (L->licoes == NULL)
    {
        L->licoes = novo;
    }
    else
    {
        TLicao *atual = L->licoes;

        while (atual->prox != NULL)
        {
            atual = atual->prox;
        } // while
        atual->prox = novo;
    } // if
}
//======================================================
void insereNeuronio(TLista *L, int neuronio)
{
    TNeuronio *novo = (TNeuronio *)malloc(sizeof(TNeuronio));
    novo->prox = NULL;
    novo->neuronio = neuronio;
    novo->peso = 0;
    novo->soma = 0;

    if (L->neuronios == NULL)
    {
        L->neuronios = novo;
    }
    else
    {
        TNeuronio *atual = L->neuronios;

        while (atual->prox != NULL)
        {
            atual = atual->prox;
        } // while
        atual->prox = novo;
    } // if
}
//======================================================
void estabelecendoSinapse(TLista *L, int neuronioDe, int neuronioAte, int camada)
{
    TSinapse *novo = (TSinapse *)malloc(sizeof(TSinapse));
    TSinapse *atual;

    novo->prox = NULL;
    novo->neuronio_origem = neuronioDe;
    novo->neuronio_destino = neuronioAte;
    novo->camada = camada;
    novo->peso = 0;

    if (L->pesos == NULL)
    {
        L->pesos = novo;
    }
    else
    {
        atual = L->pesos;

        while (atual->prox != NULL)
        {
            atual = atual->prox;
        } // while
        atual->prox = novo;
    } // if
}
//=============================================================
void printIndividuos(TLista *L) {
    TIndividuo *atual = L->populacao;
    int i = 1;

    printf("\nList of individuals:\n");
    while (atual!= NULL) {
        printf("Individual %d: number = %d, address = %p, errors = %d\n", i, atual->numero, (void *)atual, atual->erros);
        atual = atual->prox;
        i++;
    }
}
//=============================================================
void treinamento(TLista *L)
{
    printf("\n\n\t\t=====| INICIADO TREINAMENTO |=====\n\n");
    fprintf(L->fp, "\n\n\tINICIO DO TREINAMENTO: ");
    // ponteiro para a struct que armazena data e hora:
    struct tm *data_hora_atual;
    // variável do tipo time_t para armazenar o tempo em segundos.
    time_t segundos;
    // Obetendo o tempo em segundos.
    time(&segundos);
    // Para converter de segundos para o tempo local
    // utilizamos a função localtime().
    data_hora_atual = localtime(&segundos);

    fprintf(L->fp, "Dia: %d", data_hora_atual->tm_mday);
    fprintf(L->fp, "   Mes: %d", data_hora_atual->tm_mon);
    fprintf(L->fp, "   Ano: %d\n\n", data_hora_atual->tm_year);

    fprintf(L->fp, "Dia da Semana: %d.\n", data_hora_atual->tm_wday);

    fprintf(L->fp, "%d", data_hora_atual->tm_hour);
    fprintf(L->fp, ":%d", data_hora_atual->tm_min);
    fprintf(L->fp, ":%d.\n\n", data_hora_atual->tm_sec);

    // int i;
    // for (i = 0; i < L->Total_geracoes; i++)
    // {
    //     printf("etapa cruzamento\n");
    //     cruzamento(L);
    //     printIndividuos(L);
    //     if ((i % L->Qtd_Geracoes_para_Mutacoes) == 0)
    //     {
    //         printf("promovel mutacao\n");
    //         promoveMutacoes(L);
    //     } // if
    //     printf("etapa da avaliacao de indivíduos\n");
    //     avaliacaoIndividuos(L);
    //     printf("etapa do ordenamento\n");
    //     ordenamentoIndividuos(L);
    //     printf("etapa da poda\n");
    //     poda(L);
    //     printf("Fim do primeiro loop\n");
    // } // for
    printf("etapa cruzamento\n");
    cruzamento(L);
    printIndividuos(L);
    printf("etapa da avaliacao de indivíduos\n");
    avaliacaoIndividuos(L);
    printIndividuos(L);

}
//=============================================================
void cruzamento(TLista *L)
{
    TIndividuo *pai1, *pai2, *descendente1, *descendente2, *fimLista;

    // Inicializa o ponteiro fimLista no final da lista de individuos
    fimLista = L->populacao;
    while (fimLista->prox != NULL)
    {
        fimLista = fimLista->prox;
    }

    // Começa com o primeiro indivíduo original
    pai1 = L->populacao;
    while (pai1 != NULL)
    {
        // Verifica se há outro indivíduo original após pai1
        pai2 = pai1->prox;
        if (pai2 != NULL)
        {
            printf("Cruzando os individuos %d e %d\n", pai1->numero, pai2->numero);
            // Cria os descendentes
            descendente1 = (TIndividuo *)malloc(sizeof(TIndividuo));
            descendente2 = (TIndividuo *)malloc(sizeof(TIndividuo));

            // Realiza o cruzamento na metade dos genes
            for (int i = 0; i < MAX_Pesos; i++)
            {
                if (i < MAX_Pesos / 2)
                {
                    descendente1->genes[i] = pai1->genes[i];
                    descendente2->genes[i] = pai2->genes[i];
                }
                else
                {
                    descendente1->genes[i] = pai2->genes[i];
                    descendente2->genes[i] = pai1->genes[i];
                }
            }

            // Define outros atributos dos descendentes
            descendente1->prox = descendente2;
            descendente2->prox = NULL;
            descendente1->numero = L->totalIndividuos + 1;
            descendente2->numero = L->totalIndividuos + 2;
            descendente1->erros = -1;
            descendente2->erros = -1;

            // Insere os descendentes na população
            if (L->populacao == NULL)
            {
                L->populacao = descendente1;
            }
            else
            {
                fimLista->prox = descendente1;
            }

            // Atualiza o número total de indivíduos na população
            L->totalIndividuos += 2;
            printf("Individuo %d adicionado\n", descendente1->numero);
            printf("Individuo %d adicionado\n", descendente2->numero);
        }
        else
        {
            // Se não houver outro indivíduo original, termina a iteração
            break;
        }
        // Avança para o próximo indivíduo original na lista
        pai1 = pai1->prox;
    }
    //printIndividuos(L);
}
//==============================================================
void avaliacaoIndividuos(TLista *L)
{
    TIndividuo *atual = L->populacao;
    TLicao *licaoAtual;
    int erros;

    // Itera sobre cada indivíduo na população
    while (atual != NULL)
    {
        // Verifica se o indivíduo já foi avaliado
        if (atual->erros == -1)
        {
            erros = 0;
            licaoAtual = L->licoes;
            printf("Avaliando o individuo %d\n", atual->numero);
            // Para cada indivíduo, calcula a quantidade de erros cometidos
            while (licaoAtual != NULL)
            {
                // Calcula a saída da RNA-E para as entradas da lição atual
                // Comparando com o resultado esperado e contando os erros
                printf("Testando liçao\n");
                float n1, n2, n3, n4, n5;
                float peso13 = atual->genes[0];
                float peso23 = atual->genes[2];
                float peso35 = atual->genes[4];
                float peso45 = atual->genes[5];

                n1 = licaoAtual->p;
                n2 = licaoAtual->q;

                // Calcula a soma ponderada nos neurônios da primeira camada
                float soma_n3 = (n1 * peso13) + (n2 * peso23);
                float soma_n4 = (n1 * peso13) + (n2 * peso23);

                // Aplica a função de ativação nos neurônios da primeira camada
                int excitado_n3 = (soma_n3 >= L->sinapseThreshold) ? 1 : 0;
                int excitado_n4 = (soma_n4 >= L->sinapseThreshold) ? 1 : 0;

                // Calcula a saída do neurônio de saída
                n3 = excitado_n3;
                n4 = excitado_n4;
                n5 = n3 * peso35 + n4 * peso45;

                // Aplica a função de ativação no neurônio de saída
                int saida_n5 = (n5 >= L->sinapseThreshold) ? 1 : 0;

                // Verifica se a saída está correta
                if (saida_n5 != licaoAtual->resultadoEsperado)
                {
                    erros++;
                }

                licaoAtual = licaoAtual->prox;
            }

            // Atualiza a quantidade de erros do indivíduo
            atual->erros = erros;
        }
        // if(total de erros para repassar)
        //  Avança para o próximo indivíduo na população
        atual = atual->prox;
    }
    //printIndividuos(L);
}
//==============================================================
void ordenamentoIndividuos(TLista *L)
{
    TIndividuo *atual, *proximo, *menor;
    int temp;

    if (L->populacao == NULL)
    {
        return; // Retorna se a população estiver vazia
    }

    atual = L->populacao;

    // Percorre a lista de indivíduos
    while (atual->prox != NULL)
    {
        proximo = atual->prox;
        menor = atual;

        // Encontra o indivíduo com menor quantidade de erros
        while (proximo != NULL)
        {
            if (proximo->erros < menor->erros)
            {
                menor = proximo;
            }
            proximo = proximo->prox;
        }

        // Troca o indivíduo atual pelo menor encontrado
        if (menor != atual)
        {
            // Troca o número de erros
            temp = menor->erros;
            menor->erros = atual->erros;
            atual->erros = temp;

            // Troca os genes
            for (int i = 0; i < MAX_Pesos; i++)
            {
                temp = menor->genes[i];
                menor->genes[i] = atual->genes[i];
                atual->genes[i] = temp;
            }
        }

        // Avança para o próximo indivíduo na lista
        atual = atual->prox;
    }
    //printIndividuos(L);
}
//==============================================================
void promoveMutacoes(TLista *L)
{
    int num_mutacoes = 0;
    TIndividuo *atual = L->populacao;

    while (atual != NULL)
    {
        if (num_mutacoes < L->Qtd_Mutacoes_por_vez && atual->erros > 0)
        {
            atual->genes[rand() % MAX_Pesos] += (rand() % 2 == 0) ? -L->learningRate : L->learningRate;
            num_mutacoes++;
        }

        atual = atual->prox;
    }
}
//==============================================================
void poda(TLista *L)
{
    int num_excesso = L->totalIndividuos - L->Qtd_Populacao;

    if (num_excesso <= 0)
    {
        printf("Não tem excesso\n");
        return; // Não há excesso de indivíduos na população
    }

    // Encontra o último indivíduo da população
    TIndividuo *atual = L->populacao;
    TIndividuo *anterior = NULL;
    while (atual->prox != NULL)
    {
        anterior = atual;
        atual = atual->prox;
    }
    printf("O ultimo individuo e %p\n", (void *)atual);
    // Remove os indivíduos menos aptos até que o número de indivíduos volte ao limite
    for (int i = 0; i < num_excesso; i++)
    {
        if (atual == L->populacao)
        {
            // Caso especial: a lista de indivíduos tem apenas um elemento
            L->populacao = atual->prox;
            free(atual);
            atual = L->populacao;
            anterior = NULL;
        }
        else
        {
            printf("Removendo individuo %d\n", atual->numero);
            TIndividuo *temp = atual;
            atual = atual->prox;
            if (anterior != NULL)
            {
                anterior->prox = atual;
            }
            free(temp);
        }

        L->totalIndividuos--; // Atualiza o número total de indivíduos na população

        // Atualiza o último indivíduo para o anterior
        if (anterior != NULL)
        {
            while (anterior->prox != NULL)
            {
                anterior = anterior->prox;
            }
        }
    }

}
//=============================================================
