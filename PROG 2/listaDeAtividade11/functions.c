#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Defina constantes para as sequências de escape ANSI das cores
#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"

#define SEPARETOR BLUE "\n================================================\n"  RESET

struct ClassDatabase {
    int codigo;
    char nome[101];
    float preco;
    int qtde;
};
typedef struct ClassDatabase Database;

void gerarAleatorio(long int * vetor, long int tam) {
    long int i;
    for(i=0; i< tam; i++){
          vetor[i] = ( rand() % tam) * ( rand() % tam) + 1;
  //      vetor[i] = ( rand() % (3*n) ) + 1;
 //       printf("\n %ld", vetor[i]);
    }
}

void trocar(int vet[],int i,int f){
    int aux;
    aux = vet[i];
    vet[i] = vet[f];
    vet[f] = aux;
}

// inputs personalizados e modificados
float input(){
    float value;
    scanf("%f", &value);
    return value;
}
void inputS(char destino[]){
    scanf(" %100[^\n]s", destino);
}

void alocarMEM(int **database,int *maxSpace){
    printf("Entre com a quantidade de números: ");
    int quant_numeros = input();
    *database = (int *) malloc (quant_numeros * sizeof (int) );
    *maxSpace = quant_numeros;
}

void reAlocarMEM(int **database, int *maxSpace){
    printf("\nVoce tem alocado: %d \n",*maxSpace);
    printf("Entre com a quantidade a mais de elementos: ");
    int qtdeNova = input();
    *maxSpace = (qtdeNova+(*maxSpace));
    int tam = (*maxSpace) * sizeof (int);

    *database = (int *) realloc (*database , tam );
}

int pesqMaiorElemento(int vet[],int tam){
    int maior = 0;
    int i;

    for (i = 0; i <= tam; i++){
        if (vet[i] > vet[maior]){
            maior = i;
        }
    }
    return maior;
}

int pesqMenorElemento(int vet[],int tam){
    int menor = 0;
    int i;

    for (i = 0; i <= tam; i++){
        if (vet[i] < vet[menor]){
            menor = i;
        }
    }
    return menor;
}

FILE * abrirArquivo(char * nomeArq, char * modo) {
    // ABRIR o arquivo
    FILE * arq;
    arq = fopen( nomeArq, modo );
    if ( arq == NULL) {
        printf(RED "ERRO ao abrir o arquivo." RESET);
        exit(-1);
    }
    return arq;
}
void carregarArquivo(FILE * arquivo, Database * vetProd, int *qtde) {
    fread( qtde, sizeof(int), 1, arquivo  );
    fread( vetProd, sizeof(Database), *qtde, arquivo  );
}
void gravarArquivo(FILE * arquivo, Database * vetProd, int qtde) {
    fwrite( &qtde, sizeof(int), 1, arquivo  );
    fwrite( vetProd, sizeof(Database), qtde, arquivo  );
}

int correct(){
    SetConsoleOutputCP(65001);
    return 0;
}
void head(){
    correct();
    FILE * logs;
    logs = abrirArquivo("../data/logs.txt","a+");
    printf(SEPARETOR);
    printf(BLUE"\n\t LUIS_DAS_ARTIMANHAS & PINGOBRAS S.A");
    printf("\n\t Iniciando o programa....." RESET);
    printf(SEPARETOR);
    // save in logs
    fprintf(logs,SEPARETOR);
    fprintf(logs,"\n\t LUIS_DAS_ARTIMANHAS & PINGOBRAS S.A");
    fprintf(logs,"\n\t Iniciando programa.....");
    fprintf(logs,SEPARETOR);
    fclose(logs);
}

void copy(){
    FILE *logs;
    logs = abrirArquivo("../data/logs.txt","a+");
    correct();
    printf(SEPARETOR);
    printf(BLUE "\n\t DEVS:");
    printf("\n\t LUIS_DAS_ARTIMANHAS.");
    printf("\n\t PINGOBRAS S.A" RESET);
    printf(SEPARETOR);
    // save in logs
    fprintf(logs,"\n----------------------------------------------------");
    fprintf(logs,"\n\t DEVS:");
    fprintf(logs,"\n\t LUIS_DAS_ARTIMANHAS.");
    fprintf(logs,"\n\t PINGOBRAS S.A");
    fprintf(logs,"\n----------------------------------------------------\n");
    fclose(logs);
}

// validadores
void validNome(char destino[]){
    do{
        printf(YELLOW "\nInsira o nome do Produto: " RESET);
        inputS(destino);
    }while (strlen(destino) < 3);
}

int validCod(){
    int cod;
    do{
        printf(YELLOW "\nInsira o código do Produto: " RESET);
        cod = input();
    }while (cod < 1);
    return cod;
}

float validTaxa(){
    float porcent;
    printf(YELLOW "\nInsira a porcentagem de aumento ou desconto: " RESET);
    int tax = input();

    while((tax <= 0 ) || (tax > 100)){
        printf(RED "\nA taxa não pode ser menor do que 0 ou maior que 100!\n" RESET);
        printf(YELLOW "\nInsira a porcentagem de aumento ou desconto: " RESET);
        tax = input();
    }
    porcent = (tax/100);
    return porcent;
}

int validQuantidade(){
    int qtd;
    do{
        printf(YELLOW "\nInsira a quantidade do Produto: " RESET);
        qtd = input();
    }while (qtd < 0);
    return qtd;
}

int validDia(){
    int dia;
    do{
        printf(YELLOW "\nInsira o dia de validade: " RESET);
        dia = input();
    }while ((dia < 1) || (dia > 31));
    return dia;
}

int validMes(){
    int mes;
    do{
        printf(YELLOW "\nInsira o mês de validade: " RESET);
        mes = input();
    }while ((mes < 1)||(mes > 12));
    return mes;
}

int validAno(){
    int ano;
    do{
        printf(YELLOW "\nInsira o Ano de validade: " RESET);
        ano = input();
    }while ((ano < 1900)||(ano > 3050));
    return ano;
}
int validNum(){
    printf("Insira um numero: ");
    int num = input();

    while(num < 0){
        printf("Salario invalido.");
        printf("Insira Seu salario: ");
        num = input();
    }
    return num;
}
int validNota(){
    float nota;
    do{
        printf("Insira uma Nota: ");
        nota = input();
    }while ((nota < 0) || ( nota > 10));
    return nota;
}
int validMatricula(){
    float matricula;
    do{
        printf("Insira sua matricula: ");
        matricula = input();
    }while (matricula < 0);
    return matricula;
}
float validPreco(){
    float prise;
    do{
        printf(YELLOW "\nInsira o preço do Produto: " RESET);
        prise = input();
    }while (prise < 0);
    return prise;
}
int validIdade(){
    printf("Insira sua idade: ");
    int idade = input();
    while((idade <= 0) || (idade >= 50)){
        printf("Idade invalida.");
        printf("Insira sua idade: ");
        idade = input();
        
    }
    return idade;
}
int validSalario(){
    printf("Insira seu salario: ");
    int salario = input();
    
    while(salario < 0){
        printf("Salario invalido.");
        printf("Insira Seu salario: ");
        salario = input();
    }
    return salario;
}
int validAltura(){
    float alt;
    do{
        printf("Insira a altura: ");
        alt = input();
    }while (alt < 0);
    return alt;
}
int validBase(){
    float base;
    do{
        printf("Insira a base: ");
        base = input();
    }while (base < 0);
    return base;
}
int validRaio(){
    float raio;
    do{
        printf("Insira o raio: ");
        raio = input();
    }while (raio < 0);
    return (raio*raio);
}

int validQTD(){
    float qtd;
    do{
        printf("Insira a quantidade de produto: ");
        qtd = input();
    }while (qtd < 0);
    return qtd;
}
void imprimirArray(int array[], int qtde){
    int i;

    for (i = 0; i < qtde; i++){
        printf("%d ",array[i]);
    }
}
int fatorial(){
    int i,num, fat;
    printf("Informe o número: ");
    scanf("%d", &num);
    fat = 1;
    for(i=num; i > 1 ; i--) {
        fat = fat * i;
    }
    return fat;
}
int fatorialRec (int n) {
    if ( n == 0) {
        return 1;
    }
    else {
        return (n * fatorialRec(n-1) );
    }
    }

int multiplicComSoma (int a, int b) {
    if ( a == 0 || b == 0 ) {
        return 0;
    }
    else if ( b == 1) {
        return a;
    }
    else {
        return (a + multiplicComSoma (a, b-1) );
    }
}

int lerOpcaoCalc() {
    int op;
    printf("\n\nCALCULAR A ÁREA:\n");
    printf("1-Retângulo\n");
    printf("2-Círculo\n");
    printf("0-Sair\n");
    printf("Informe sua opção: ");
    scanf("%d", &op);
    // VALIDAR a opção entre 0, 1 e 2
    return op;
}
int somar(int num1, int num2){
    int total = num1 + num2;
    printf("\nSomando os numeros: %d + %d\n", num1,num2);
    return total;
}
int diminuir(int num1, int num2){
    int total = num1 - num2;
    printf("\n Subtraindo os numeros: %d - %d\n", num1,num2);
    return total;
}
float calcMedia3(float n1,float n2,float n3){
    float media = (n1 + n2 + n3 )/3;
    return media;
}
int menuPay(){
    printf("\n=======SELECIONAR FORMA DE PAGAMENTO=======\n");
    printf("1-A vista\n");
    printf("2-A prazo\n");
    printf("=====================\n");
    printf("Forma: ");
    int opc = input();

    return opc;
}

int calcArRetangulo(){
    float base = validBase();
    float altura = validAltura();
    float area = base * altura;
    return area;
}
int calcArCirculo(){
    float raio = validRaio();
    float area = M_PI * raio;
    return area;
}

void removerArray(int *qtde, int *array, int pos){
    int i;
    for (i = pos; i < (*qtde)-1; i++){
        array[i] = array[i+1];
    }
    (*qtde)--;
}

// funções do trabalho

struct Date{
    int dia;
    int mes;
    int ano;
};typedef struct Date Data;
struct ClassProduto{
    int cod;
    char nome[101];
    float prise;
    int quantidade;
    Data validade;
};typedef struct ClassProduto Produto;

void carregarDatabase( Produto * vetProd, int *qtde) {
    printf(BLUE "\nSISTEMA: Carregando Autosave..." RESET);
    FILE * databaseR;
    databaseR = abrirArquivo("../data/database.bin", "rb");
    fread( qtde, sizeof(int), 1, databaseR  );
    fread( vetProd, sizeof(Produto), *qtde, databaseR  );
    fclose(databaseR);
}
void gravarDatabase(Produto * vetProd, int qtde) {
    printf(BLUE "\nSISTEMA: SALVANDO DADOS..." RESET);
    FILE *databaseW;
    databaseW = abrirArquivo("../data/database.bin", "wb");
    fwrite( &qtde, sizeof(int), 1, databaseW  );
    fwrite( vetProd, sizeof(Produto), qtde, databaseW  );
    fclose(databaseW);
    printf(GREEN "\nSISTEMA: Autosave concluido!" RESET);
}



int menu() {
    correct();
	int op;
	// system("@cls||clear");  // LIMPA A TELA
	printf(BLUE "\n\nSISTEMA DE ESTOQUE\n\n" RESET);
	printf(GREEN "1 - Inserir\n");
	printf("2 - Pesquisar por número\n");
	printf("3 - Pesquisar por nome\n");
	printf("4 - Atualizar\n");
	printf("5 - Maior\n" RESET);
	printf(RED "6 - Excluir\n" RESET);
	printf(GREEN "7 - Listar\n"  RESET);
	printf(RED "0 - Sair\n" RESET);
	do {
		printf(YELLOW "Escolha sua opção: " RESET);
		scanf(" %d", &op);
	} while(op < 0 || op > 7);
	return op;
}

int menuUpdate() {
    correct();
	int op;
	// system("@cls||clear");  // LIMPA A TELA
	printf(BLUE "\n\nSISTEMA DE ESTOQUE\n\n" RESET);
	printf(GREEN "1 - Aplicar desconto\n");
	printf("2 - Aplicar aumento\n");
	do {
		printf(YELLOW "Escolha sua opção: " RESET);
		scanf(" %d", &op);
	} while(op < 1 || op > 2);
	return op;
}

// funções


int pesqCod(Produto produtos[],int tam){
    if(tam >= 1){
        int cod = validCod();
        int i;
        for(i=0; i <= tam; i++){
            Produto produtoTemp = produtos[i];

            if(produtos[i].cod == cod){
                printf(GREEN"\nO Produto procurado foi encontrado!",RESET);
                printf(SEPARETOR);
                printf(BLUE"   \t Nome do produto: %s", produtoTemp.nome);
                printf(     "\n \t código do produto: %d", produtoTemp.cod);
                printf(     "\n \t Preço do produto: %0.2f", produtoTemp.prise);
                printf(     "\n \t Quantidade do produto: %d", produtoTemp.quantidade);
                printf(     "\n \t Data de validade do produto: %0.2d/%0.2d/%0.2d", produtoTemp.validade.dia,produtoTemp.validade.mes,produtoTemp.validade.ano,RESET);
                printf(SEPARETOR);
                return i;
            }else{
                printf(BLUE"\nSISTEMA: PROCURANDO...",RESET);
            }
        }
        printf(RED "\nO Produto não esta repetido e não foi encontado!" RESET);
        return -1;
    }else{
        printf(RED "\nSISTEMA: O banco de dados esta vazio, insira algo primeiro" RESET);
    }
}

int pesqName(Produto produtos[],int tam){
    if(tam >= 1){
        char pesq[101];
        int i;
        int comparador = 1;
        validNome(pesq);

        for(i=0; i <= tam; i++){
            Produto produtoTemp = produtos[i];
            comparador = strcmp(produtoTemp.nome, pesq);

            if(comparador == 0){
                printf(GREEN"%s\nO Produto procurado foi encontrado!",RESET);
                printf(SEPARETOR);
                printf(BLUE"   \t Nome do produto: %s", produtoTemp.nome);
                printf(     "\n \t código do produto: %d", produtoTemp.cod);
                printf(     "\n \t Preço do produto: %0.2f", produtoTemp.prise);
                printf(     "\n \t Quantidade do produto: %d", produtoTemp.quantidade);
                printf(     "\n \t Data de validade do produto: %0.2d/%0.2d/%.02d", produtoTemp.validade.dia,produtoTemp.validade.mes,produtoTemp.validade.ano,RESET);
                printf(SEPARETOR);
                return i;
            }else{
                printf(BLUE"%s\nSISTEMA: PROCURANDO...",RESET);
            }
        }
        printf(RED "\nO Produto não foi encontado!" RESET);
        return -1;
    }else{
        printf(RED "\nSISTEMA: O banco de dados esta vazio, insira algo primeiro" RESET);
    }
}


void inserir(Produto produtos[],int *tam){
    char name[101];
    validNome(name);
    float prise = validPreco();
    int qtde = validQuantidade();
    int day = validDia();
    int month = validMes();
    int year = validAno();
    int cod = validCod();
    printf(BLUE"\nSISTEMA: Confirme o código do produto!"RESET);
    int pesq = pesqCod(produtos,*tam);

    if(pesq == -1){
    strcpy(produtos[*tam].nome,name);
    produtos[*tam].cod = cod;
    produtos[*tam].prise = prise;
    produtos[*tam].quantidade = qtde;
    produtos[*tam].validade.dia = day;
    produtos[*tam].validade.mes = month;
    produtos[*tam].validade.ano = year;
    (*tam)++;
    }else{
        printf(SEPARETOR);
        printf(RED"\nERRO: O código do produto já existe!"RESET);
        printf(BLUE"\nSISTEMA: Saindo para o menu para preservar os arquivos!"RESET);
        printf(SEPARETOR);
    }
}


void update(Produto produtos[],int tam){
    int op;
    int pos = pesqCod(produtos, tam);
    float taxa;
    float taxaRend;
    float total;
    if(tam >= 1){
        if(pos > 0 ){
            float prodPrise = produtos[pos].prise;
            taxa = validTaxa();
            op = menuUpdate();
            taxaRend = taxa * prodPrise;

            switch ( op ) {
                case 1:
                    //desconto
                    total = prodPrise - taxaRend;
                break;
                case 2:
                    //aumento
                    total = prodPrise + taxaRend;
                break;
                default:
                printf ("\n\nOpção inválida!\n\n");
                }
            produtos[pos].prise = total;

            printf(BLUE "SISTEMA: O rendimento ou desconto de R$ %f foi aplicado no valor do produto!",taxaRend,RESET);
        }else{
            printf(RED "Não foi possivel aplicar o rendimento" RESET);
        }
    }else{
        printf("\n O banco de dados esta vazio, insira algo primeiro");
    }
}

void finderMaior(Produto produtos[],int tam){
    char nome[101];
    int cod;
    int qtde;
    int maior = 0;
    int i;
    int day,month,year;
    float prise;

    if(tam >= 1){
        for(i = 0; i <= tam; i++){
            Produto produtoTemp = produtos[i];

            if (produtoTemp.prise >= maior){
                maior = produtoTemp.prise;
                strcpy(nome,produtoTemp.nome);
                cod = produtoTemp.cod;
                prise = produtoTemp.prise;
                qtde = produtoTemp.quantidade;
                day = produtoTemp.validade.dia;
                month = produtoTemp.validade.mes;
                year = produtoTemp.validade.ano;
            }else{
                printf(BLUE"\n SISTEMA: PROCURANDO...",RESET);
            }
        }
        printf(SEPARETOR);
        printf(BLUE"   \t Nome do produto: %s", nome);
        printf(     "\n \t código do produto: %d", cod);
        printf(     "\n \t Preço do produto: %0.2f", prise);
        printf(     "\n \t Quantidade do produto: %d", qtde);
        printf(     "\n \t Data de validade do produto: %0.2d/%0.2d/%0.2d", day,month,year,RESET);
        printf(SEPARETOR);
    }else{
        printf(RED "\nSISTEMA: O banco de dados esta vazio, insira algo primeiro" RESET);
    }
}

void delete(Produto produtos[],int *tam){
    int i;
    if((*tam) >= 1){
        printf(YELLOW"\nALERTA: Tenha certeza que o código do produto esta certo!");
        printf("\nALERTA: ERROS no código do produto ocasionarão em exclusão permanente de um produto incorreto!"RESET);
        int pos = pesqCod(produtos,*tam);

        if(pos != -1){
            for (i = pos; i < (*tam- 1); i++) {
            produtos[i] = produtos[i+1];
        }
        (*tam)--;
        printf(SEPARETOR);
        printf(BLUE"\nSISTEMA: Produto deletado com sucesso!"RESET);
        printf(SEPARETOR);
        }else{
            printf(RED "\nSISTEMA: O código do produto e invalido ou não esta cadastrado!" RESET);
        }
    }else{
        printf(RED "\nSISTEMA: O banco de dados esta vazio, insira algo primeiro" RESET);
    }
}

void list(Produto produtos[],int tam){
    int i;
    if(tam >= 1){
        for (i = 0; i < tam; i++){
            Produto produtoTemp = produtos[i];
            printf(SEPARETOR);
            printf(BLUE"   \t Nome do produto: %s", produtoTemp.nome);
            printf(     "\n \t código do produto: %d", produtoTemp.cod);
            printf(     "\n \t Preço do produto: %0.2f", produtoTemp.prise);
            printf(     "\n \t Quantidade do produto: %d", produtoTemp.quantidade);
            printf(     "\n \t Data de validade do produto: %0.2d/%0.2d/%0.2d", produtoTemp.validade.dia,produtoTemp.validade.mes,produtoTemp.validade.ano,RESET);
            printf(SEPARETOR);
        }
    }else{
        printf(RED "\nSISTEMA: O banco de dados esta vazio, insira algo primeiro" RESET);
    }
}

long seqFibonacci(int termos){
    //  f1:1, f1:1, f2:2, 3, 5, 8, 13, 21, 34, 55:10
    long i;
    long f1 = 1;
    long f2 = 1;
    long f3;

    for (i = 2; i < termos; i++){
        f3 = f1+f2;
        f1 = f2;
        f2 = f3;
        printf("\n %d",f2);
    }
    return f2;
}

long reqSeqFibonacci(int termos){
    if ((termos == 1) || (termos == 2)){
        return 1;
    }else{
        return reqSeqFibonacci(termos-1) + reqSeqFibonacci(termos-2);
    }
}

void imprimirRecus(char data[],int tam){
    if (tam == 1){
        printf("%d  ",data[0]);
    }else{
        imprimirRecus(data,tam-1);
        printf("%d  ",data[tam-1]);
    }
}

// algoritmos
int buscaBinaria(int vetor[],int pesq, int tam){
    int meio;
    int fim = tam-1;
    int ini = 0;
    int count = 0;

    while(ini<=fim){
        meio = (ini+fim)/2;

        if(pesq == vetor[meio]){
            printf("Executado: %d",count);
            return meio;
        }else if(pesq > vetor[meio]){
            ini=meio+1;
        }else{
            fim = meio-1;
        }
        count++;
    }
    printf("Executado: %d", count);
    return -1;
}

void insertionSort(int vet[], int tam){
    int i,j;
    int valor;
    int trocas = 0;

    for (i = 1; i < tam; i++){
        valor = vet[i];
        j = i - 1;

        while ((j >= 0) && (valor < vet[j])){
            vet[j+1] = vet[j];
            j--;
            trocas++;
        }
        vet[j+1] = valor;
    }
    printf("\n Trocas: %d \n",trocas);
}
int insertionSortAdaptado(int vet[],int tam, int pos, int h){
    int i,j;
    int valor;
    int trocas = 0;

    for (i = pos + h; i < tam; i= i + h){
        valor = vet[i];
        j = i - h;

        while ((j >= 0) && (valor < vet[j])){
            vet[j+h] = vet[j];
            j= j - h;
            trocas++;
        }
        vet[j+h] = valor;
    }
    return trocas;
}

void shellSort(int vet[], int tam){
    int h,ini;
    int trocas = 0;
    FILE * logs;
    logs = abrirArquivo("../data/logs.txt","a+");

    for (h = 1; h <= tam; h=3*h+1){
        printf("\n H: %d",h);
    }

    for (h = (h-1)/3; h > 0;h = (h-1)/3){
        for (ini = 0; ini < h; ini++){
            trocas = trocas + insertionSortAdaptado(vet,tam,ini,h);
        }
    }
    printf("\n Trocas: %d",trocas);
    imprimirArray(vet,1000);
    fprintf(logs,"\n shellSort executou as trocas");
    fprintf(logs,"\n Trocas: %d\n",trocas);
    fclose(logs);
}

void bubbleSort(int vet[],int tam){
    int i,aux;
    int exe = 0;
    int trocas = 1;
    int fim = tam-1;
    FILE * logs;
    logs = abrirArquivo("../data/logs.txt","a+");

    do{
        trocas = 0;
        for (i = 0; i < fim; i++){
            if (vet[i] > vet[i+1]){
                aux = vet[i];
                vet[i] = vet[i+1];
                vet[i+1] = aux;
                trocas++;
                exe++;
            }
        }
        fim--;
    }while(trocas > 0);

    imprimirArray(vet,tam);
    printf("\n Trocas: %d\n",exe);
    fprintf(logs,"\n bubbleSort executou as trocas");
    fprintf(logs,"\n Trocas: %d\n",exe);
    fclose(logs);
}

void shakeSort(int vet[],int tam){
    int i,f,aux;
    int exe = 0;
    int trocas = 1;
    int fim = tam-1;
    int ini = 0;
    FILE * logs;
    logs = abrirArquivo("../data/logs.txt","a+");

    do{
        trocas = 0;
        for (i = ini, f = fim; i < fim; i++,f--){
            if (vet[i] > vet[i+1]){
                aux = vet[i];
                vet[i] = vet[i+1];
                vet[i+1] = aux;
                trocas++;
                exe++;
            }
            if (vet[f] < vet[f-1]){
                aux = vet[f];
                vet[f] = vet[f-1];
                vet[f-1] = aux;
                trocas++;
                exe++;
            }
        }
        fim--;
        ini++;
        imprimirArray(vet,tam);
        printf("\n");
    }while(trocas > 0);
    imprimirArray(vet,tam);
    printf("\n Trocas: %d\n",exe);
    fprintf(logs,"\n shakeSort executou as trocas");
    fprintf(logs,"\n Trocas: %d\n",exe);
    fclose(logs);
}

void combSort(int vet[],int tam){
    int i,aux;
    int h = tam;
    int exe = 0;
    int trocas = 1;

    do{
        trocas = 0;
        h = (h / 1.3);
        if (h == 9 || h == 10){
            h = 11;
        }else if (h <1){
            h = 1;
        }

        if (h < 1){
            tam--;
        }
        for (i = 0; i < tam-h; i++){
            if (vet[i] > vet[i+h]){
                aux = vet[i];
                vet[i] = vet[i+h];
                vet[i+h] = aux;
                trocas++;
                exe++;
            }
        }
        printf("\n H: %d",h);
    }while((trocas > 0) || (h > 1) );
    printf("\n");
    imprimirArray(vet,tam);
    printf("\n Trocas: %d\n",exe);
}

void quickSort(int vet[], int ini, int fim){
    int posPivo;

    if (ini < fim){
        posPivo = particao(vet,ini,fim);
        quickSort(vet, ini, posPivo - 1);
        quickSort(vet, posPivo + 1, fim);
    }
}

int particao(int vet[], int ini,int fim){
    int pivo = vet[ini];
    int i = ini + 1;
    int f = fim;

    while (i <= f){
        if (vet[i] <= pivo){
            i++;
        }else if (vet[f] > pivo){
            f--;
        }
        else{
            trocar(vet, i, f);
            i++;
            f--;
        }
    }
    trocar(vet, ini, f);
    return f;
}

void selectSort(int vet[], int tam){
    int posMaior;
    int i;
    int trocas = 0;

    for ( i = tam; i > 1; i--) {
        posMaior = pesqMaiorElemento(vet,i);
        if ( posMaior != i-1 ) {
            trocar(vet, posMaior, i-1);
            trocas++;
        }
    }
    printf("\nTROCAS: %ld\n", trocas);

}

void atualizarHeap(long int * vetor, long int raiz, long int n ) {
	int filhoEsq = 2 * raiz + 1;
	int filhoDir = 2 * raiz + 2;

	int maior;
	if ( filhoEsq >= n) {
		// SEM NENHUM FILHO
		return;
	} else if ( filhoDir >= n ){
		// SOMENTE o FILHO DA ESQUERDA
		maior = filhoEsq;
	} else if ( vetor[filhoEsq] > vetor[filhoDir]  ) {
		maior = filhoEsq;
	} else {
		maior = filhoDir;
	}

	if ( vetor[maior] > vetor[raiz]  ) {
		trocar(vetor, maior, raiz);	
		atualizarHeap(vetor, maior, n);
	} else {
		return;
	}
}

void construirHeap(int vet[],int tam){
    int i;

	for(i = (tam/2)-1; i>=0; i--) {
		atualizarHeap(vet, i, tam);
	}
}

void heapSort(int * vetor, int tam ) {
	long int n = tam;
	construirHeap(vetor,n);
	while (n > 1) {	
		trocar(vetor,0,n-1);
		n--;
		atualizarHeap(vetor,0,n);
	}
//	printf("\n\nTROCAS: %ld", trocas);
}
