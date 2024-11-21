// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Jônatas Souza
//  email: jonatas.alfatorquato@gmail.com
//  Matrícula: 20221160002
//  Semestre: 2024.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "JonatasSouza20221160002.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);
int converterString(char *string, char *newString);
//int TotalDeDias(int dia, int mes, int ano);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */

int q1(char data[]){
  int datavalida = 1;
  int i;
  int anoBissexto = 0;
  int dia = 0, mes = 0, ano = 0;
  //quebrar a string data em strings sDia, sMes, sAno

  DataQuebrada dq = quebraData(data);
  if (dq.valido != 1) {
      datavalida = 0;
  }

  dia = dq.iDia;
  mes = dq.iMes;
  ano = dq.iAno;

  // validando ano
  if((ano >= 1000) && (ano <= 2025)){
    datavalida = 1;
  } else{
    datavalida = 0;
  }

  // Verificando se é ano bissexto

  if(((ano % 4) == 0 && (ano % 100) != 0) || (ano % 400) == 0){
    anoBissexto= 1;
  } else{
    anoBissexto= 0;
  }

  // validando mes
  
  if((mes >= 1) && (mes <= 12)){
    datavalida = 1;
  } else{
    datavalida = 0;
  }

  // validando dia

  if(mes == 2){
    if(anoBissexto == 0){
      if((dia >= 1) && (dia <= 28)){
        datavalida = 1;
      } else{
        datavalida = 0;
      }
    } else if(anoBissexto == 1){
      if((dia >= 1) && (dia <= 29)){
        datavalida = 1;
      } else{
        datavalida = 0;
      }
    }
  } else if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
    if((dia >= 1) && (dia <= 31)){
      datavalida = 1;
    } else{
      datavalida = 0;
    }
  } else if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
    if((dia >= 1) && (dia <= 30)){
      datavalida = 1;
    } else{
      datavalida = 0;
    }
  }

  //printf("%s\n", data);

  if (datavalida)
      return 1;
  else
      return 0;
}


/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    int diaDi, mesDi, anoDi, diaDf, mesDf, anoDf; // dia, mes, ano inicial e final
    int difDia=0, difMes=0, difAno=0;
    DataQuebrada dqInicial, dqFinal;

    int totalDiasInicial, totalDiasFinal, totalDias;
    int i;
    //calcule os dados e armazene nas três variáveis a seguir
    
    DiasMesesAnos dma;

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else if (q1(datainicial) > q1(datafinal)){
      //verifique se a data final não é menor que a data inicial
      dma.retorno = 4;
      return dma;
    } else{
      //calcule a distancia entre as datas
      DataQuebrada dqInicial = quebraData(datainicial);
      diaDi = dqInicial.iDia; mesDi = dqInicial.iMes; anoDi = dqInicial.iAno;

      DataQuebrada dqFinal = quebraData(datafinal);
      diaDf = dqFinal.iDia; mesDf = dqFinal.iMes; anoDf = dqFinal.iAno;

      if(anoDf < anoDi || (anoDf == anoDi && mesDf < mesDi) || (anoDf == anoDi && mesDf == mesDi && diaDf < diaDi)){
        dma.retorno = 4;
        return dma;
      }
      
      difAno = anoDf - anoDi;
      difMes = mesDf - mesDi;
      difDia = diaDf - diaDi;

      if(difDia < 0){
        difMes--;
        if(((mesDf - 1) == 2) && (((anoDf % 4) == 0 && (anoDf % 100) != 0) || (anoDf % 400) == 0)){
          difDia += 29;
        } else if((mesDf - 1) == 2){
          difDia += 28;
        } else if(mesDf == 1 || mesDf == 3 || mesDf == 5 || mesDf == 7 || mesDf == 8 || mesDf == 10 || mesDf == 12){
          difDia += 31;
        } else if(mesDf == 4 || mesDf == 6 || mesDf == 9 || mesDf == 11){
          difDia += 30;
        }
      }

      if(difMes < 0){
        difAno--;
        difMes += 12;
      }

      dma.qtdAnos = difAno;
      dma.qtdMeses = difMes;
      dma.qtdDias = difDia;

      //se tudo der certo
      dma.retorno = 1;
      return dma; 
    }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */

int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
    int tam = 0;
    int i;
    char aux[250];

    for(i=0; texto[i] != '\0'; i++){
      tam++;
    }

    // Copiando o texto para uma string auxiliar

    for(i=0; i<tam; i++){
      aux[i] = texto[i];
    }

    if(isCaseSensitive == 1){
      // Localizar o caractere
      for(i=0; i<tam; i++){
        if(c == texto[i]){
          qtdOcorrencias++;
        }
      }
    } else if(isCaseSensitive != 1){
      // Converter o caracter em minusculo
      if((c >= 'A') && (c <= 'Z')){
        c += 32;
      }
      // Converter a string auxiliar em minusculo
      for(i=0; i<tam; i++){
        if((aux[i] >= 'A') && (aux[i] <= 'Z')){
          aux[i] = aux[i] + 32;
        }
      }
      // Localizar o caractere
      for(i=0; i<tam; i++){
        if(c == aux[i]){
          qtdOcorrencias++;
        }
      }
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
  int qtdOcorrencias = 0;
  int i, j, k = 0;
  int tamTexto = 0, tamBusca = 0;

  char newStrTexto[250];
  char newStrBusca[50];
  
  // Converte as strings com caracteres especiais
  converterString(strTexto, newStrTexto);
  converterString(strBusca, newStrBusca);

  // Calcula o tamanho das strings convertidas
  for (i = 0; newStrTexto[i] != '\0'; i++){
    tamTexto++;
  }

  for (i = 0; newStrBusca[i] != '\0'; i++){
    tamBusca++;
  }

  // Busca pela ocorrência de strBusca na strTexto
  for (i = 0; i <= tamTexto - tamBusca; i++){
    int encontrado = 1;
    for (j = 0; j < tamBusca; j++){
      if (newStrBusca[j] != newStrTexto[j+i]){
        encontrado = 0;
        break;
      }
    }

    if (encontrado){
      qtdOcorrencias++;
      posicoes[k] = i + 1;
      posicoes[k+1] = i + tamBusca;
      k += 2;
    }
  }

  return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int auxiliar = num;
    int digito = 0;
    int numInvertido = 0;

    while (auxiliar != 0){
        digito = auxiliar % 10; // Pega o ultimo digito do numero inteiro
        numInvertido *= 10;
        numInvertido += digito;
        auxiliar = auxiliar / 10; // Faz a nova divisão
    }
    num = numInvertido;

    return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;

    int aux1 = numerobase, aux2 = numerobusca;
    int digito1 = 0, digito2 = 0;
    int numInvertido1 = 0, numInvertido2 = 0;
    int tam1 = 0, tam2 = 0;

    // -------- NumeroBase ---------
    // Invertendo o numerobase
    while (aux1 != 0) {
        digito1 = aux1 % 10;
        numInvertido1 = numInvertido1 * 10 + digito1;
        tam1++;
        aux1 /= 10;
    }

    int vetor1[tam1];
    int i = 0;

    // Preenchendo vetor1 do numerobase
    while (numInvertido1 != 0) {
        digito1 = numInvertido1 % 10;
        vetor1[i++] = digito1;
        numInvertido1 /= 10;
    }

    // -------- NumeroBusca ---------
    // Invertendo o numerobusca
    while (aux2 != 0) {
        digito2 = aux2 % 10;
        numInvertido2 = numInvertido2 * 10 + digito2;
        tam2++;
        aux2 /= 10;
    }

    int vetor2[tam2];
    i = 0;

    // Preenchendo vetor2 do numerobusca
    while (numInvertido2 != 0) {
        digito2 = numInvertido2 % 10;
        vetor2[i++] = digito2;
        numInvertido2 /= 10;
    }

    if (tam2 > tam1) {
        return 0;
    }

    // Busca Sequencial para encontrar o vetor2 numerobusca no vetor1 numerobase
    int j, encontrado;

    for (i = 0; i <= tam1 - tam2; i++) {
        encontrado = 1;
        for (j = 0; j < tam2; j++) {
            if (vetor1[i + j] != vetor2[j]) {
                encontrado = 0;
                break;
            }
        }
        if (encontrado == 1) {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}


DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}

int converterString(char *string, char *newString) {
  char comAcento[][4] = {"Ä", "Á", "Â", "À", "Ã", "ä", "á", "â", "à", "ã",
                          "É", "Ê", "Ë", "È", "é", "ê", "ë", "è",
                          "Í", "Î", "Ï", "Ì", "í", "î", "ï", "ì",
                          "Ö", "Ó", "Ô", "Ò", "Õ", "ö", "ó", "ô", "ò", "õ",
                          "Ü", "Ú", "Û", "Ù", "ü", "ú", "û", "ù",
                          "Ç", "ç"};
  char semAcento[] = "AAAAAaaaaaEEEEeeeeIIIIiiiiOOOOOoooooUUUUuuuuCc";
  
  int i = 0, j=0, k = 0, encontrado;
  while (string[i] != '\0'){
    encontrado = 0;

    // Verifica se é um caractere multibyte (UTF-8)
    if((unsigned char)string[i] >= 192){ // Se for multibyte (maior que 192)
      char temp[4] = {string[i], string[i + 1], '\0'}; // Captura 2 bytes (ex: 'a' e '~')
      for (j=0; j < 46; j++){
        if(strcmp(temp, comAcento[j]) == 0){
          newString[k++] = semAcento[j];
          encontrado = 1;
          break;
        }
      }
      i++;
    }

    // Caso seja caractere simples (ASCII) ou não mapeado
    if (encontrado != 1){
      newString[k++] = string[i];
    }
    i++;
  }

  newString[k] = '\0'; // Finaliza a nova string
  return k;            // Retorna o tamanho da nova string
}

/*

int TotalDeDias(int dia, int mes, int ano){
  int totalDias = dia;
  int i;

  // Adiciona os dias dos meses anteriores no mesmo ano
  for (i=1; i<mes; i++) {
    if(i == 2){
      if(((ano % 4) == 0 && (ano % 100) != 0) || (ano % 400) == 0){
        totalDias += 29;
      } else{
        totalDias += 28;
      }
    } else if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
      totalDias += 31;
    } else if (i == 4 || i == 6 || i == 9 || i == 11){
      totalDias += 30;
    }
  }
  
  // Colocando os dias dos anos anteriores
  if(((ano % 4) == 0 && (ano % 100) != 0) || (ano % 400) == 0){
    totalDias += (ano - 1) * 366; 
  } else{
    totalDias += (ano - 1) * 365;
  }

  return totalDias;
} */