#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

int vetorPrincipal[TAM];

typedef struct EstruturaAuxiliar{
    int *elementos;
    int quantidade;
    int tamanho;
} EstruturaAuxiliar;

EstruturaAuxiliar estruturaAuxiliar[TAM];

void inicializar(){
    for(int i=0; i<TAM; i++) {
        estruturaAuxiliar[i].elementos = NULL;
        estruturaAuxiliar[i].quantidade = 0;
        estruturaAuxiliar[i].tamanho = 0;
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{   
    posicao = posicao - 1;
    if(tamanho < 1){
        return TAMANHO_INVALIDO;
    }
    if((posicao < 0) || (posicao >= TAM)){
        return POSICAO_INVALIDA;
    }
    if(estruturaAuxiliar[posicao].elementos != NULL){
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    estruturaAuxiliar[posicao].elementos = (int *)malloc(TAM * sizeof(int));
    //estruturaAuxiliar[posicao].elementos = (EstruturaAuxiliar *)malloc(TAM * sizeof(EstruturaAuxiliar));
    if(estruturaAuxiliar[posicao].elementos){
        estruturaAuxiliar[posicao].tamanho = tamanho;
        return SUCESSO;
    } else{
        return SEM_ESPACO_DE_MEMORIA;
    }

    /*
    // a posicao pode já existir estrutura auxiliar
    retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    // se posição é um valor válido {entre 1 e 10}
    retorno = POSICAO_INVALIDA;
    // o tamanho ser muito grande
    retorno = SEM_ESPACO_DE_MEMORIA;
    // o tamanho nao pode ser menor que 1
    retorno = TAMANHO_INVALIDO;
    // deu tudo certo, crie
    retorno = SUCESSO; */
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    /* int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0; */

    carregarArquivo("dados.txt");
    int i = 0;
    posicao = posicao - 1;
    int quantidade = estruturaAuxiliar[posicao].quantidade;

    if((posicao < 0) || (posicao >= TAM)){
        return POSICAO_INVALIDA;
    }
    if(estruturaAuxiliar[posicao].elementos == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if(estruturaAuxiliar[posicao].quantidade >= estruturaAuxiliar[posicao].tamanho){
        return SEM_ESPACO;
    }

    estruturaAuxiliar[posicao].elementos[quantidade] = valor; // insere o valor na Estrutura
    estruturaAuxiliar[posicao].quantidade++; // incrementa a quantidade de elementos da Estrutura
    salvarArquivo("dados.txt");
    return SUCESSO;
}

/*

    if((posicao < 0) || (posicao >= TAM)){
        return POSICAO_INVALIDA;
    } else{
        if(estruturaAuxiliar[posicao].elementos == NULL){
            return SEM_ESTRUTURA_AUXILIAR;
        } else{
            if(estruturaAuxiliar[posicao].quantidade >= tamanhoAux){
                return SEM_ESPACO;
            } else{
                estruturaAuxiliar[posicao].elementos[quantidade] = valor; // insere o valor na Estrutura
                estruturaAuxiliar[posicao].quantidade = estruturaAuxiliar[posicao].quantidade + 1; // incrementa a quantidade de elementos da Estrutura
                return SUCESSO;
            }
        }
    }
} */

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{   
    posicao = posicao - 1;
    int tamanho = estruturaAuxiliar[posicao].quantidade;
    if((posicao < 0) || (posicao >= TAM)){
        return POSICAO_INVALIDA;
    } else{
        if(estruturaAuxiliar[posicao].elementos != NULL){
            if(estruturaAuxiliar[posicao].quantidade == 0){
                return ESTRUTURA_AUXILIAR_VAZIA;
            } else{
                estruturaAuxiliar[posicao].elementos[tamanho--];
                estruturaAuxiliar[posicao].quantidade--;
                return SUCESSO;
            }
        } else{
            return SEM_ESTRUTURA_AUXILIAR;
        }
    }
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{   
    posicao = posicao - 1;
    int i = 0;
    int encontrado = -1;
    int tamanho = estruturaAuxiliar[posicao].quantidade;
    // Verifica se a posição é válida
    if (posicao < 0 || posicao >= TAM){
        return POSICAO_INVALIDA;
    } else{
        if(estruturaAuxiliar[posicao].elementos != NULL){
            if(tamanho == 0){
                return ESTRUTURA_AUXILIAR_VAZIA;
            } else{
                for(i=0; i< tamanho; i++){
                    if(estruturaAuxiliar[posicao].elementos[i] == valor){
                        encontrado = i; // Índice do valor encontrado
                        break;
                    }
                }
                if (encontrado == -1){ 
                    return NUMERO_INEXISTENTE;
                }
                for(i = encontrado; i < tamanho - 1; i++) {
                    estruturaAuxiliar[posicao].elementos[i] = estruturaAuxiliar[posicao].elementos[i + 1];
                }
                
                estruturaAuxiliar[posicao].quantidade = estruturaAuxiliar[posicao].quantidade - 1;
                return SUCESSO;

            }
        } else{
            return SEM_ESTRUTURA_AUXILIAR;
        }
    }    
}


// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{   
    posicao = posicao - 1;
    if (posicao < 0 || posicao > TAM)
    {
        return POSICAO_INVALIDA;
    }
    else{
        return SUCESSO;
    }    
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int i = 0;
    posicao = posicao - 1;
    if((posicao < 0) || (posicao >= TAM)){
        return POSICAO_INVALIDA;
    }
    if(estruturaAuxiliar[posicao].elementos == NULL){
        return SEM_ESTRUTURA_AUXILIAR; 
    }
    if(estruturaAuxiliar[posicao].quantidade == 0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    for(i=0; i < estruturaAuxiliar[posicao].quantidade; i++){
        vetorAux[i] = estruturaAuxiliar[posicao].elementos[i];
    }
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{   
    posicao = posicao - 1;
    int i = 0;
    int j = 0;
    int auxiliar = 0;
    int tamanho = estruturaAuxiliar[posicao].quantidade;

    if((posicao < 0) || (posicao >= TAM)){
        return POSICAO_INVALIDA;
    }
    if(estruturaAuxiliar[posicao].elementos == NULL){
        return SEM_ESTRUTURA_AUXILIAR; 
    }
    if(estruturaAuxiliar[posicao].quantidade == 0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    for(i=0; i < estruturaAuxiliar[posicao].quantidade; i++){
        vetorAux[i] = estruturaAuxiliar[posicao].elementos[i];
    }

    // Ordernar //
    for(i=0; i < tamanho; i++){
        for(j=0; j < tamanho - i - 1; j++){
            if(vetorAux[j] > vetorAux[j+1]){
                auxiliar = vetorAux[j];
                vetorAux[j] = vetorAux[j+1];
                vetorAux[j+1] = auxiliar;
            }
        }
    }

    return SUCESSO;   
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int i = 0;
    int j = 0;
    int k = 0;
    int vazio = 0;

    for (int i = 0; i < TAM; i++) {
        if (estruturaAuxiliar[i].quantidade == 0 || estruturaAuxiliar[i].elementos == NULL) {
            vazio++;
            continue;
        }

        for (int j = 0; j < estruturaAuxiliar[i].quantidade; j++) {
            vetorAux[k] = estruturaAuxiliar[i].elementos[j];
            k++;
        }
    }
    
    for(i=0; i < TAM; i++){
        for(j=0; j < estruturaAuxiliar[i].quantidade; j++){
            if(estruturaAuxiliar[i].quantidade == 0){
                vazio++;
            } else{
                vetorAux[k] = estruturaAuxiliar[i].elementos[j];
                k++; 
            }
        }
    }

    if(vazio == 10){
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int i = 0;
    int j = 0;
    int k = 0;
    int vazio = 0;
    int auxiliar = 0;

    for (int i = 0; i < TAM; i++) {
        if (estruturaAuxiliar[i].quantidade == 0 || estruturaAuxiliar[i].elementos == NULL) {
            vazio++;
            continue; // Pula para o próximo índice se a estrutura estiver vazia
        }
        for (int j = 0; j < estruturaAuxiliar[i].quantidade; j++) {
            vetorAux[k] = estruturaAuxiliar[i].elementos[j];
            k++;
        }
    }


    if(vazio == 10){
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    for(i=0; i < k; i++){
        for(j=0; j < k - i - 1; j++){
            if(vetorAux[j] > vetorAux[j+1]){
                auxiliar = vetorAux[j];
                vetorAux[j] = vetorAux[j+1];
                vetorAux[j+1] = auxiliar;
            }
        }
    }

    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    int i = 0;

    posicao = posicao - 1;

    if((posicao < 0) || (posicao >= TAM)){
        return POSICAO_INVALIDA;
    }

    if(estruturaAuxiliar[posicao].elementos == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    int tamanhoInicial = estruturaAuxiliar[posicao].tamanho;
    int tamanhoFinal = tamanhoInicial + novoTamanho;

    if(tamanhoFinal < 1){
        return NOVO_TAMANHO_INVALIDO;
    }

    int *newArray = (int *)realloc(estruturaAuxiliar[posicao].elementos, tamanhoFinal * sizeof(int));
    if (newArray == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }
    estruturaAuxiliar[posicao].elementos = newArray;
    estruturaAuxiliar[posicao].tamanho = tamanhoFinal;

    if (novoTamanho > 0) {
        for (int i = tamanhoInicial; i < tamanhoFinal; i++) {
            estruturaAuxiliar[posicao].elementos[i] = 0; // Inicializa com 0
        }
    }

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/


int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    posicao = posicao - 1;

    if (posicao < 0 || posicao >= TAM) {
        return POSICAO_INVALIDA;
    }
    if (estruturaAuxiliar[posicao].elementos == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (estruturaAuxiliar[posicao].quantidade == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    return estruturaAuxiliar[posicao].quantidade;
}


/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{   
    // Aloca memória para o cabeçote
    No *cabecote = (No *)malloc(sizeof(No));
    if (cabecote == NULL) {
        return NULL;
    }

    cabecote->prox = NULL; // Inicializa a lista como vazia
    No *ultimo = cabecote; // Ponteiro para o último elemento na lista

    // Percorre todas as estruturas auxiliares
    for (int i = 0; i < TAM; i++) {
        if (estruturaAuxiliar[i].elementos != NULL) { // Verifica se a estrutura existe
            for (int j = 0; j < estruturaAuxiliar[i].quantidade; j++) { // Itera pelos elementos preenchidos
                No *novo = (No *)malloc(sizeof(No)); // Aloca um novo nó
                if (novo == NULL) {
                    destruirListaEncadeadaComCabecote(&cabecote); // Libera memória em caso de erro
                    return NULL;
                }
                novo->conteudo = estruturaAuxiliar[i].elementos[j]; // Insere o conteúdo
                novo->prox = NULL; // Aponta para NULL (novo fim da lista)
                ultimo->prox = novo; // Atualiza o próximo do último nó
                ultimo = novo; // Move o ponteiro 'ultimo' para o novo nó
            }
        }
    }

    // Verifica se a lista está vazia (sem elementos)
    if (cabecote->prox == NULL) {
        free(cabecote); // Libera o cabeçote vazio
        return NULL;
    }

    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    int i = 0;
    No *valor = inicio->prox;

    while(valor != NULL){
        vetorAux[i++] = valor->conteudo;
        valor = valor->prox;
    }    
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{   
    int i = 0;
    No *value = *inicio;

    while(value != NULL){
        No *prox = value->prox;
        free(value);
        value = prox;
    }
}


/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

//

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{   
    for(int i=0; i<TAM; i++){
        free(estruturaAuxiliar[i].elementos);
        estruturaAuxiliar[i].elementos = NULL; 
    }
}

int carregarArquivo(const char *dados){
    FILE *arquivo = fopen(dados, "r");
    if(arquivo == NULL){
        return;
    }

    int posicao;
    int tamanho;
    int numero;
    int retorno;

    char line[5000];

    while(fgets(line, sizeof(line), arquivo) != NULL){
        line[strcspn(line, "\n")] = '\0';

        char *slice = strtok(line, ";");
        if(slice == NULL){
            continue;
        }
        // Lê a posicao
        posicao = atoi(slice) - 1;
        slice = strtok(NULL, ";");
        tamanho = atoi(slice);

        retorno = criarEstruturaAuxiliar(posicao, tamanho);

        if(retorno != SUCESSO){
            fclose(arquivo);
            return;
        }

        while((slice = strtok(NULL, ";")) != NULL){
            retorno = inserirNumeroEmEstrutura(posicao, atoi(slice));
            if(retorno != SUCESSO){
                fclose(arquivo);
                return;
            }
        }
    }
    fclose(arquivo);
    return SUCESSO;
}

void salvarArquivo(const char *dados){
    FILE *arquivo = fopen("dados.txt", "r");
    if(arquivo == NULL){
        return;
    }
    for(int i = 0; i<TAM; i++){
        EstruturaAuxiliar *temp = &estruturaAuxiliar[i];

        if(temp->elementos != NULL && temp->quantidade > 0){
            fprintf(arquivo, "%d;%d", i+1, temp->tamanho);

            for(int j = 0; j < temp->quantidade; j++){
                fprintf(arquivo, ";%d", temp->elementos[j]);
            }
            fprintf(arquivo, "\n");
        }
    }
    fclose(arquivo);
}