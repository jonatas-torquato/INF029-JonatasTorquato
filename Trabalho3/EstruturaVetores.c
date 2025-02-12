#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 10

#include "EstruturaVetores.h"

int vetorPrincipal[TAM];

typedef struct EstruturaAuxiliar{
    int *elementos;
    int quantidade;
    int tamanho;
} EstruturaAuxiliar;

EstruturaAuxiliar *estruturaAuxiliar;

void inicializar(){
    estruturaAuxiliar = malloc(sizeof(EstruturaAuxiliar) * TAM);

    for(int i=0; i<TAM; i++) {
        estruturaAuxiliar[i].elementos = NULL;
        estruturaAuxiliar[i].quantidade = 0;
        estruturaAuxiliar[i].tamanho = 0;
    }
    carregarArquivo("dados.txt");
}
/* 
    Objetivo: Escrever no arquivo 'dados.txt' a posição do VetorPrincipal, seguido do tamanho da 
    Estrutura Auxiliar, e se houver, escrever também os elementos da estrutura auxiliar.
    Cada número é separado pelo sinal de ponto e vírgula.
*/
int carregarArquivo(const char *dados){ 
    FILE *arquivo = fopen(dados, "r");
    // Se não existir arquivo, tenta criar um arquivo.
    if(arquivo == NULL){
        arquivo = fopen(dados, "w");
        if(arquivo == NULL){
        // Erro ao criar arquivo
            printf("Arquivo inexistente.\nErro ao criar arquivo.\n");
            return ERROR;
        } else{
        // Sucesso ao criar arquivo
            printf("Arquivo inexistente. Arquivo criado com sucesso.\n");
        }
    } else{
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
            // Slice vai armazernar o conteúdo que vier depois do ; se for diferente de NULL;
            slice = strtok(NULL, ";");
            // Lê o tamanho;
            tamanho = atoi(slice);

            retorno = criarEstruturaAuxiliar(posicao, tamanho);

            if(retorno != SUCESSO){
                fclose(arquivo);
                return ERROR;
            }

            while((slice = strtok(NULL, ";")) != NULL){
                retorno = inserirNumeroEmEstrutura(posicao, atoi(slice));
                if(retorno != SUCESSO){
                    fclose(arquivo);
                    return ERROR;
                }
            }
        }
        fclose(arquivo);
        return SUCESSO;
    }
}

/*
    Objetivo: salvar todos os dados das Estruturas Auxiliares no arquivo 'dados.txt'.
    Posição, tamanho e os elementos das Estruturas Auxiliares.
*/

int salvarArquivo(const char *dados){
    FILE *arquivo = fopen("dados.txt", "w");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo.\n");
        return ERROR;
    } else{
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
    }
    fclose(arquivo);
    return SUCESSO;
}

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
}

int inserirNumeroEmEstrutura(int posicao, int valor)
{   
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
                salvarArquivo("dados.txt");
                return SUCESSO;
            }
        } else{
            return SEM_ESTRUTURA_AUXILIAR;
        }
    }
}

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
                salvarArquivo("dados.txt");
                return SUCESSO;
            }
        } else{
            return SEM_ESTRUTURA_AUXILIAR;
        }
    }    
}

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

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){   
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

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    int i = 0;
    No *valor = inicio->prox;

    while(valor != NULL){
        vetorAux[i++] = valor->conteudo;
        valor = valor->prox;
    }    
}

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

void finalizar()
{   
    for(int i=0; i<TAM; i++){
        free(estruturaAuxiliar[i].elementos);
        estruturaAuxiliar[i].elementos = NULL; 
    }
}