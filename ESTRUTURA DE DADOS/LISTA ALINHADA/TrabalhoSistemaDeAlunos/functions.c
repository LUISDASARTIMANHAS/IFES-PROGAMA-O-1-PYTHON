// Produzido por LUCAS GARCIA & LUIS AUGUSTO DE SOUZA
// ============================= BASE ======================
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
// #include "utils.c"
// Defina constantes para as sequências de escape ANSI das cores

// RED ERROR
#define RED "\x1b[31m"
// BLUE SISTEMA
#define BLUE "\x1b[34m"
// GREEN OK 
#define GREEN "\x1b[32m"
// YELLOW PERGUNTAS
#define YELLOW "\x1b[33m"
// RESET REDEFINIR
#define RESET "\x1b[0m"
#define SEPARETOR BLUE "\n================================================\n"  RESET

typedef char string[101];

typedef struct ClassDatabaseTipoDisciplina {
	string nome;
	int cargaHoraria;
	ClassDatabaseTipoDisciplina *prox;
}TDisciplina;

typedef struct ClassDatabaseTipoHistorico {
	TDisciplina *disciplina;
	float nota;
	float percentualFrequencia;
	string condicao; // Aprovado, Reprovado ou Cursando.
	ClassDatabaseTipoHistorico *prox;	
}THistorico;

typedef struct ClassDatabaseTipoAluno {
    string nome;
	char sexo;
	THistorico *historico;
	ClassDatabaseTipoAluno *ante, *prox;
}TAluno;

typedef struct ClassDatabaseTipoCurso {
    string nome;
	TAluno *alunos;
	ClassDatabaseTipoCurso *ante, *prox;
}TCurso;

typedef struct ClassDatabaseTipoLista {
    TCurso *inicioC;
    TCurso *fimC;
    TDisciplina *inicioD;
    TDisciplina *fimD;
	int total;
}TLista;


// ============================= FIM DO BASE ======================
int menu(){
	int op;
	printf("\n\n\t\t====| MENU |=====\n\n");
	printf("\t0 - Sair (Encerrar a Aplicacao).\n\n");
	printf("\t1 - Inserir DISCIPLINA.\n");
	printf("\t2 - Exibe Todas as DISCIPLINAS.\n\n");
	printf("\t3 - Inserir CURSO.\n");
	printf("\t4 - Exibir Todos os CURSOS.\n\n");
	printf("\t5 - Inserir ALUNO em CURSO.\n");
	printf("\t6 - Exibir Todos os ALUNOS de CURSO especifico.\n");
	printf("\t7 - Excluir ALUNO de CURSO.\n\n");
	printf("\t8 - Inserir HISTORICO para ALUNO.\n");
	printf("\t9 - Exibir HISTORICO de ALUNO.\n");
	printf("\t10 - Excluir HISTORICO de ALUNO.\n\n");
	do {
		printf("Escolha sua opção: ");
		scanf(" %d", &op);
	} while(op < 0 || op > 10);
	return op;
}
// void insereAtor(TLista *DB, string nome){
//     TAtor *novo = (TAtor *)malloc(sizeof(TAtor));
//     TAtor *atual = DB->inicioA;
//     TAtor *anterior = NULL;
//     int inseriu = 0;
    

//     novo->prox = NULL;
//     strcpy(novo->nome,nome);
//     printf("\nINSERINDO ATOR: %s...",nome);

//     if(DB->inicioA == NULL){
//         DB->inicioA = novo;
//         DB->fimA = novo;
//     }else{
//         while(atual != NULL){
//             if (strcmp(atual->nome,novo->nome) > 0)	{
//                 inseriu = 1;
//                 if(atual == DB->inicioA)	{
//                     novo->prox = atual;
//                     DB->inicioA = novo;	
//                 } else {
//                     novo->prox = anterior->prox;
//                     anterior->prox = novo;
//                 }
//                 break;
//             }
//             anterior = atual;
//             atual = atual->prox;
//         }
        
//         if(!inseriu){
//             DB->fimA->prox = novo;
//             DB->fimA = novo;
//         }
//     }
// }

// void insereFilme(TLista *DB, string titulo, int ano){
//     TFilme *novo = (TFilme *)malloc(sizeof(TFilme));
//     TFilme *atual = DB->inicioF;
//     TFilme *anterior = NULL;
//     int inseriu = 0;

//     novo->ante = NULL;
//     novo->prox = NULL;
//     novo->elenco = NULL;
//     novo->anoProducao = ano;
//     strcpy(novo->titulo,titulo);
//     printf("\nINSERINDO FILME: %s...",titulo);

//     if(DB->inicioF == NULL){
//         DB->inicioF = novo;
//         DB->fimF = novo;
//     }else{
//         inseriu = 0;
//         anterior = atual->ante;
//         while(atual != NULL){
//             if (strcmp(atual->titulo,novo->titulo) > 0)	{
//                 inseriu = 1;
//                 novo->prox = atual;
//                 atual->ante = novo;

//                 if(anterior == NULL){
//                     DB->inicioF = novo;	
//                 } else {
//                     anterior->prox = novo;
//                     novo->ante = anterior;
//                 }
//                 break;
//             }
//             atual = atual->prox;
//         }
        
//         if(!inseriu){
//             DB->fimF->prox = novo;
//             novo->ante = DB->fimF;
//             DB->fimF = novo;
//         }
//     }
// }

// void cadastraAtor(TLista *DB){
//     string nome;

//     printf("\n\n\t=====| INSERE ATOR|=====\n\n");
//     printf("\tInforme o nome do ator: ");
//     fflush(stdin);
//     inputS(nome);

//     insereAtor(DB, nome);
// }

// void cadastraFilme(TLista *DB){
//     string titulo;
//     int ano;


//     printf("\n\n\t=====| CADASTRO DE FILMES |=====\n\n");
//     printf(YELLOW"\tTITULO: ");
//     fflush(stdin);
//     inputS(titulo);

//     printf("\n\n\tANO DE PRODUÇÃO: "RESET);
//     fflush(stdin);
//     ano = input();

//     insereFilme(DB, titulo, ano);
// }

// void exibeAtores(TLista *DB){
// 	TAtor *atual = DB->inicioA;
// 	int cont = 0;
	
// 	printf("\n\n");
// 	printf("+----------------------------------------------------+\n");
// 	while (atual != NULL)	{
// 		printf("\t(%d) - %s.\n", ++cont, atual->nome);
// 		atual = atual->prox;
// 	}//while
// 	printf("+----------------------------------------------------+\n\n\n");
// }

// void exibeFilmes(TLista *DB){
// 	TFilme *atual = DB->inicioF;
//     TElenco *cursor;
//     TAtor *ator;
// 	int cont = 0;
	
// 	printf("\n\n");
// 	printf(BLUE"+----------------------------------------------------+\n");
// 	while (atual != NULL)	{
// 		printf("\t(%d) - %s [%d].\n", ++cont, atual->titulo, atual->anoProducao);
//         if (atual->elenco !=NULL){
//             printf("\n");
//             cursor = atual->elenco;
//             while (cursor != NULL){

//                 printf("\t\t%s\n",cursor->ator->nome);
//                 cursor = cursor->prox;
//             }
            
//         }
        
// 		atual = atual->prox;
// 	}//while
// 	printf("+----------------------------------------------------+\n\n\n"RESET);
// }

// TFilme *localizaFilme(TLista *DB, string titulo){
// 	TFilme *atual = DB->inicioF;
	
// 	while (atual != NULL){
// 		if(strcmp(atual->titulo, titulo) == 0){
// 			break;
// 		}//if
// 		atual = atual->prox;
// 	}//while
// 	return atual;
// }

// TAtor *localizaAtor(TLista *DB, string nome){
// 	TAtor *atual = DB->inicioA;
	
// 	while(atual != NULL)	{
// 		if(strcmp(atual->nome, nome) == 0) {
// 			break;
// 		}//if
// 		atual = atual->prox;
// 	}//while
// 	return atual;
// }

// void relacionarFilmeAtor(TFilme *filme, TAtor *a){
// 	TElenco *novo = (TElenco *)malloc(sizeof(TElenco));
	
// 	novo->prox = NULL;
// 	novo->ator = a;
	
// 	if(filme->elenco != NULL){
// 	   TElenco *atual = filme->elenco;
// 	   while(atual->prox != NULL){
// 			atual = atual->prox;
//        }//while
// 	   atual->prox = novo;		
// 	} else {
// 	   filme->elenco = novo;
// 	}//if
// }

// void criaElenco(TLista *DB, string titulo, string nomeAtor){
// 	TFilme *f = localizaFilme(DB,titulo);
// 	if(f != NULL){
// 		TAtor *a = localizaAtor(DB, nomeAtor);
		
// 		if(a != NULL)	{
// 			relacionarFilmeAtor(f,a);
// 		}//if
// 	}//if	
// }