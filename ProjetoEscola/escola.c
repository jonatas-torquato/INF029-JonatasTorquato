#define TAM_ALUNO 3
#define TAM_PROFESSOR 3
#define TAM_DISCIPLINA 3
#define MAX_QTDE_ALUNOS_MATRICULADOS 3
#define CADASTRADO_REALIZADO_COM_SUCESSO -1
#define MATRICULA_INVALIDA -2
#define MATRICULA_REPETIDA -3
#define LISTA_CHEIA -4
#define MATRICULA_ATUALIZADA -5
#define NAO_ENCONTRADO -6
#define DADOS_INVALIDOS -7
#define MATRICULA_EXCLUIDA -8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct{
  int matricula;
  char nome[50];
  int ativo;
} AlunosMatriculados;

typedef struct{
  int dia;
  int mes;
  int ano;
} Data;

typedef struct a{
  int matricula;
  char nome[50];
  char sexo;
  Data dataNascimento;
  char cpf[12];
  int ativo; //verificar se o aluno está ativo//
} Aluno;

typedef struct p{
  int matricula;
  char nome[50];
  char sexo;
  Data dataNascimento;
  char cpf[12];
  int ativo; //verificar se o professor está ativo//
} Professor;

typedef struct d{
  int codigoDisciplina;
  char nome[50];
  int semestre;
  int matriculaProfessor;
  char professorDisciplina[50];
  AlunosMatriculados listaAlunosMatriculados[MAX_QTDE_ALUNOS_MATRICULADOS];
  int qtdeAlunosMatriculados;
  int ativo;
} Disciplina;

// prototipos das funções

int menuGeral();

int menuAluno();
int cadastrarAluno(); // matricula, nome, sexo, data de nascimento, cpf
void listarAluno();
int atualizarAluno();
int excluirAluno();

int menuProfessor();
int cadastrarProfessor(); // matricula, nome, sexo, data de nascimento, cpf
void listarProfessor();
int atualizarProfessor();
int excluirProfessor();

int menuDisciplina();
int cadastrarDisciplina();
void listarDisciplina();
int atualizarDisciplina();
int excluirDisciplina();
int inserirAlunoDisciplina();
int excluirAlunoDisciplina();

int menuRelatorio();
void listarUmaDisciplina();
void listarAlunosPorSexo();
void listarAlunosPorNome();
void listarAlunosPorDataNascimento();
void listarProfessoresPorSexo();
void listarProfessoresPorNome();
void listarProfessoresPorDataNascimento();
void listarAniversariantesDoMes();
int listarPessoasPorStringBusca();
void listarAlunosMatriculadosEmTresDisciplinas();
void listarDisciplinasAcima40Vagas();



// modularização
// utilizar um gerador automÃ¡tico de matrícula
// novos atributos na struct aluno e fzr leitura desses novos atributos
// validações

int main(void){
  Aluno listaAluno[TAM_ALUNO];
  int opcao;
  int sair = 0;
  int qtdeAluno = 0;

  Professor listaProfessor[TAM_PROFESSOR];
  int qtdeProfessor = 0;

  Disciplina listaDisciplina[TAM_DISCIPLINA];
  int qtdeDisciplina = 0;

  AlunosMatriculados listaAlunosMatriculados[TAM_ALUNO];
  int qtdeAlunosMatriculados = 0;

  Aluno listaAlunoAuxiliar[TAM_ALUNO];
  int qtdeAlunoAuxiliar = qtdeAluno;

  Professor listaProfessorAuxiliar[TAM_PROFESSOR];
  int qtdeProfessorAuxiliar = qtdeProfessor;

  int alunoQtdeMaterias[qtdeAluno];

  char stringBusca[50];

  while(sair != 1){

    opcao = menuGeral();

    switch (opcao){
      case 0:{
        sair = 1;
        break;
      }
      case 1:{
        printf("\n\n----Módulo Aluno----\n");
        int sairAluno = 0;
        int opcaoAluno;
        while(sairAluno != 1){

          opcaoAluno = menuAluno();

          switch(opcaoAluno){
            case 0:{
              sairAluno = 1;
              break;
            }
            case 1:{
              // função cadastrar
              int retorno = cadastrarAluno(listaAluno, qtdeAluno);
              if(retorno == LISTA_CHEIA){
                printf("Lista de Alunos cheia.\n");
              } else if(retorno == MATRICULA_INVALIDA){
                printf("Matrícula Inválida.\n");
              } else if(retorno == MATRICULA_REPETIDA){
                printf("Aluno já está cadastrado.\n");
              } else if(retorno == DADOS_INVALIDOS){
                printf("Dados Inválidos.\n");
              } else if(retorno == CADASTRADO_REALIZADO_COM_SUCESSO){
                printf("Aluno cadastrado com sucesso.\n");
                qtdeAluno++;
              }
              break;
            }
            case 2:{
              // função listar
              listarAluno(listaAluno, qtdeAluno);
              break;
            }
            case 3:{
              // função atualizar
              int retorno = atualizarAluno(listaAluno, qtdeAluno, listarDisciplina, qtdeDisciplina, qtdeAlunosMatriculados);
              if(retorno == MATRICULA_INVALIDA){
                printf("Matrícula InvÃ¡lida.\n");
              } else if(retorno == NAO_ENCONTRADO){
                printf("Aluno não encontrado.\n");
              } else if(retorno == MATRICULA_ATUALIZADA){
                printf("Aluno atualizado com sucesso.\n");
              } else if(retorno == DADOS_INVALIDOS){
                printf("Dados Inválidos.\n");
              } else if(retorno == MATRICULA_REPETIDA){
                printf("Matrícula digitada já existe no cadastrado.\n");
              }
              break;
            }
            case 4:{
              // função excluir
              int retorno = excluirAluno(listaAluno, qtdeAluno, listarDisciplina, qtdeDisciplina, qtdeAlunosMatriculados);
              if(retorno == MATRICULA_INVALIDA){
                printf("Matrícula Inválida.\n");
              } else if(retorno == NAO_ENCONTRADO){
                printf("Aluno não encontrado.\n");
              } else if(retorno == MATRICULA_EXCLUIDA){
                printf("Aluno excluído com sucesso.\n");
                qtdeAluno--;
              }
              break;
            }

            default:{
              printf("Opção Inválida.");
            }
          }
        }
        break;
      }
      case 2:{
        printf("----Módulo Professor----\n");

        int sairProfessor = 0;
        int opcaoProfessor;
        while(sairProfessor != 1){

          opcaoProfessor = menuProfessor();

          switch(opcaoProfessor){
            case 0:{
              sairProfessor = 1;
              break;
            }
            case 1:{
              // função cadastrar
              int retorno = cadastrarProfessor(listaProfessor, qtdeProfessor);
              if(retorno == LISTA_CHEIA){
                printf("Lista de Professor cheia.\n");
              } else if(retorno == MATRICULA_INVALIDA){
                printf("Matrícula Inválida.\n");
              } else if(retorno == MATRICULA_REPETIDA){
                printf("Aluno já está cadastrado.\n");
              } else if(retorno == DADOS_INVALIDOS){
                printf("Dados Inválidos.\n");
              } else if(retorno == CADASTRADO_REALIZADO_COM_SUCESSO){
                printf("Professor cadastrado com sucesso.\n");
                qtdeProfessor++;
              }
              break;
            }
            case 2:{
              // função listar
              listarProfessor(listaProfessor, qtdeProfessor);
              break;
            }
            case 3:{
              // função atualizar
              int retorno = atualizarProfessor(listaProfessor, qtdeProfessor, listaDisciplina, qtdeDisciplina);
              if(retorno == MATRICULA_INVALIDA){
                printf("Matrícula Inválida.\n");
              } else if(retorno == NAO_ENCONTRADO){
                printf("Professor não encontrado.\n");
              } else if(retorno == MATRICULA_ATUALIZADA){
                printf("Professor atualizado com sucesso.\n");
              } else if(retorno == DADOS_INVALIDOS){
                printf("Dados Inválidos.\n");
              } else if(retorno == MATRICULA_REPETIDA){
                printf("Matrícula digitada já existe no cadastrado.\n");
              }
              break;
            }
            case 4:{
              // função excluir
              int retorno = excluirProfessor(listaProfessor, qtdeProfessor);
              if(retorno == MATRICULA_INVALIDA){
                printf("Matrícula Inválida.\n");
              } else if(retorno == NAO_ENCONTRADO){
                printf("Professor não encontrado.\n");
              } else if(retorno == MATRICULA_EXCLUIDA){
                printf("Professor excluído com sucesso.\n");
                qtdeProfessor--;
              }
              break;
            }

            default:{
              printf("Opção Inválida.");
            }
          }
        }

        break;
      }
      case 3:{
        printf("----Módulo Disciplina----\n");
        int sairDisciplina = 0;
        int opcaoDisciplina;
        while(sairDisciplina != 1){

          opcaoDisciplina = menuDisciplina();

          switch(opcaoDisciplina){
            case 0:{
              sairDisciplina = 1;
              break;
            }
            case 1:{
              // função cadastrar
              int retorno = cadastrarDisciplina(listaDisciplina, qtdeDisciplina, listaProfessor);
              if(retorno == LISTA_CHEIA){
                printf("Lista de Disciplinas cheia.\n");
              } else if(retorno == MATRICULA_INVALIDA){
                printf("Codigo da Disciplina Inválido.\n");
              } else if(retorno == MATRICULA_REPETIDA){
                printf("Disciplina já está cadastrada.\n");
              } else if(retorno == DADOS_INVALIDOS){
                printf("Dados Inválidos.\n");
              } else if(retorno == NAO_ENCONTRADO){
                printf("Dados Inválidos.\n");
              } else if(retorno == CADASTRADO_REALIZADO_COM_SUCESSO){
                printf("Disciplina cadastrada com sucesso.\n");
                qtdeDisciplina++;
              }
              break;
            }
            case 2:{
              // função listar
              listarDisciplina(listaDisciplina, qtdeDisciplina, listaProfessor);
              break;
            }
            case 3:{
              // função atualizar
              int retorno = atualizarDisciplina(listaDisciplina, qtdeDisciplina, listaProfessor);
              if(retorno == MATRICULA_INVALIDA){
                printf("Codigo da Disciplina Inválido.\n");
              } else if(retorno == NAO_ENCONTRADO){
                printf("Disciplina não encontrada.\n");
              } else if(retorno == MATRICULA_ATUALIZADA){
                printf("Disciplina atualizada com sucesso.\n");
              } else if(retorno == DADOS_INVALIDOS){
                printf("Dados Inválidos.\n");
              } else if(retorno == MATRICULA_REPETIDA){
                printf("Código da Disciplina digitada já existe no cadastrado.\n");
              }
              break;
            }
            case 4:{
              // função excluir
              int retorno = excluirDisciplina(listaDisciplina, qtdeDisciplina);
              if(retorno == MATRICULA_INVALIDA){
                printf("Código  da Disciplina Inválida.\n");
              } else if(retorno == NAO_ENCONTRADO){
                printf("Disciplina não encontrada.\n");
              } else if(retorno == MATRICULA_EXCLUIDA){
                printf("Disciplina excluída com sucesso.\n");
                qtdeDisciplina--;
              }
              break;
            }
            case 5:{
                int retorno = inserirAlunoDisciplina(listaDisciplina, qtdeDisciplina, listaAluno, qtdeAluno, listaAlunosMatriculados, qtdeAlunosMatriculados);
                if(retorno == MATRICULA_INVALIDA){
                    printf("Código/Matrícula Inválida.\n");
                } else if(retorno == NAO_ENCONTRADO){
                    printf("Não encontrado.\n");
                } else if(retorno == CADASTRADO_REALIZADO_COM_SUCESSO){
                    qtdeAlunosMatriculados++;
                    printf("Aluno inserido na Disciplina com Sucesso.\n");
                }
              break;
            }
            case 6:{
               int retorno = excluirAlunoDisciplina(listaDisciplina, qtdeDisciplina, listaAluno, qtdeAluno, listaAlunosMatriculados, qtdeAlunosMatriculados);
                if(retorno == MATRICULA_INVALIDA){
                    printf("Código/Matrícula Inválida.\n");
                } else if(retorno == NAO_ENCONTRADO){
                    printf("Não encontrado.\n");
                } else if(retorno == MATRICULA_EXCLUIDA){
                    qtdeAlunosMatriculados--;
                    printf("Aluno excluído da Disciplina com Sucesso.\n");
                }
              break;
            }
            default:{
              printf("Opção Inválida.");
            }
          }
        }
        break;
      }
      case 4:{
        printf("\n\n----Módulo Relatórios----\n");
        int sairRelatorio = 0;
        int opcaoRelatorio;
        while(sairRelatorio != 1){

          opcaoRelatorio = menuRelatorio();

          switch(opcaoRelatorio){
            case 0:{
              sairRelatorio = 1;
              break;
            }
            case 1:{
              // Listar Alunos
              listarAluno(listaAluno, qtdeAluno);
              break;
            }
            case 2:{
              // listar Professor
              listarProfessor(listaProfessor, qtdeProfessor);
              break;
            }
            case 3:{
              // Listar Disciplina
              listarDisciplina(listaDisciplina, qtdeDisciplina);
              break;
            }
            case 4:{
              // Listar Uma Disciplina
              listarUmaDisciplina(listaDisciplina, qtdeDisciplina, listaAlunosMatriculados, qtdeAlunosMatriculados);
              break;
            }
            case 5:{
              // Listar Aluno por sexo
              listarAlunosPorSexo(listaAluno, qtdeAluno);
              break;
            }
            case 6:{
              // Listar Aluno por nome
              listarAlunosPorNome(listaAluno, qtdeAluno, listaAlunoAuxiliar, qtdeAlunoAuxiliar);
              break;
            }
            case 7:{
              // Listar Aluno por data de nascimento
              listarAlunosPorDataNascimento(listaAluno, qtdeAluno, listaAlunoAuxiliar, qtdeAlunoAuxiliar);
              break;
            }
            case 8:{
              // Listar Professor por sexo
              listarProfessoresPorSexo(listaProfessor, qtdeProfessor);
              break;
            }
            case 9:{
              // Listar Professor por nome
              listarProfessoresPorNome(listaProfessor, qtdeProfessor, listaProfessorAuxiliar, qtdeProfessorAuxiliar);
              break;
            }
            case 10:{
              // Listar Professor por data de nascimento
              listarProfessoresPorDataNascimento(listaProfessor, qtdeProfessor, listaProfessorAuxiliar, qtdeProfessorAuxiliar);
              break;
            }
            case 11:{
              // listar Aniversariantes do Mes
              listarAniversariantesDoMes(listaAluno, qtdeAluno, listaProfessor, qtdeProfessor);
              break;
            }
            case 12:{
              // Listar por String de busca
              listarPessoasPorStringBusca(listaAluno, qtdeAluno, listaProfessor, qtdeProfessor);
              break;
            }
            case 13:{
              listarAlunosMatriculadosEmTresDisciplinas(listaAluno, qtdeAluno, listaDisciplina, qtdeDisciplina, qtdeAlunosMatriculados, alunoQtdeMaterias);
              break;
            }
            case 14:{
              listarDisciplinasAcima40Vagas(listaDisciplina, qtdeDisciplina);
              break;
            }
            default:{
              printf("Opção Inválida.");
            }
          }
        }
        break;

      }
      default:{
        printf("Opção Inválida\n");
      }
    }
  }
  return 0;
}

// funções

// ALUNO --------------------------------------------------------------------------------


int menuGeral(){
  int opcao;

  printf("\n\n----Projeto Escola----\n");
  printf("0 - Sair\n");
  printf("1 - Aluno\n");
  printf("2 - Professor\n");
  printf("3 - Disciplina\n");
  printf("4 - Relatórios\n");

  scanf("%d", &opcao);

  return opcao;
}

int menuAluno(){
  int opcaoAluno;

  printf("\n\n----Menu Aluno----\n");
  printf("1 - Cadastrar Aluno\n");
  printf("2 - Listar Aluno\n");
  printf("3 - Atualizar Aluno\n");
  printf("4 - Excluir Aluno\n");

  scanf("%d", &opcaoAluno);

  return opcaoAluno;
}

int cadastrarAluno(Aluno listaAluno[], int qtdeAluno, Data dataNascimento){
  int matricula;

  printf("\n\n--- Cadastrar Aluno ---\n");
  if(qtdeAluno == TAM_ALUNO){
    return LISTA_CHEIA;
  }else{
    printf("Digite a matrícula: \n");
    scanf("%d", &matricula);

    if(matricula < 0){
      return MATRICULA_INVALIDA;
    } else{
      int encontrado=0;
      for(int i=0; i<qtdeAluno; i++){
        if(matricula == listaAluno[i].matricula){
          encontrado=1;
        }
      }
      if(encontrado==1){
        return MATRICULA_REPETIDA;
      } else{

        int tam;
        getchar();

        printf("Digite o nome: \n");
        fgets(listaAluno[qtdeAluno].nome, 50, stdin);
        tam = strlen(listaAluno[qtdeAluno].nome) - 1;

        if((listaAluno[qtdeAluno].nome[0] >= 'a') && (listaAluno[qtdeAluno].nome[0] >= 'z')){
            listaAluno[qtdeAluno].nome[0] = listaAluno[qtdeAluno].nome[0] - 32; 
        }

        if(listaAluno[qtdeAluno].nome[tam] == '\n'){
            listaAluno[qtdeAluno].nome[tam] = '\0';
        }

        printf("Digite o sexo: \nM - Masculino\nF - Feminino\n");
        scanf("%c", &listaAluno[qtdeAluno].sexo);

        if(((listaAluno[qtdeAluno].sexo != 'M') && (listaAluno[qtdeAluno].sexo != 'F')) && ((listaAluno[qtdeAluno].sexo != 'm') && (listaAluno[qtdeAluno].sexo != 'f'))){
            return DADOS_INVALIDOS; 
        }
        printf("Digite a data de nascimento: \n");
        printf("Dia: \n");
        scanf("%d", &listaAluno[qtdeAluno].dataNascimento.dia);
        if((listaAluno[qtdeAluno].dataNascimento.dia < 0) || (listaAluno[qtdeAluno].dataNascimento.dia > 31)){
            return DADOS_INVALIDOS;
        }
        printf("Mês: \n");
        scanf("%d", &listaAluno[qtdeAluno].dataNascimento.mes);
        if((listaAluno[qtdeAluno].dataNascimento.mes < 0) || (listaAluno[qtdeAluno].dataNascimento.mes > 12)){
            return DADOS_INVALIDOS;                
        }
        printf("Ano: \n");
        scanf("%d", &listaAluno[qtdeAluno].dataNascimento.ano);
        if((listaAluno[qtdeAluno].dataNascimento.ano < 1900) || (listaAluno[qtdeAluno].dataNascimento.ano > 2024)){
            return DADOS_INVALIDOS;
        } 
        getchar();
        printf("Digite o CPF: \n");
        fgets(listaAluno[qtdeAluno].cpf, 12, stdin);

        tam = strlen(listaAluno[qtdeAluno].cpf) - 1;
        if(listaAluno[qtdeAluno].cpf[tam] == '\n'){
            listaAluno[qtdeAluno].cpf[tam] == '\0';
        }

        // Validar CPF

        if(strlen(listaAluno[qtdeAluno].cpf) != 11){
            return DADOS_INVALIDOS;
        }

        for(int p=0; listaAluno[qtdeAluno].cpf[p] != '\0'; p++){
            if((listaAluno[qtdeAluno].cpf[p] <= '0') && (listaAluno[qtdeAluno].cpf[p] >= '9')){
                return DADOS_INVALIDOS;
            }
        }

        // CADASTRO

        listaAluno[qtdeAluno].matricula = matricula; // MATRICULA
        listaAluno[qtdeAluno].ativo = 1; //aluno ativo// */
        return CADASTRADO_REALIZADO_COM_SUCESSO;
      }
    }
  }
}

void listarAluno(Aluno listaAluno[], int qtdeAluno){
  printf("\n--- Listar Aluno ---\n");
  if(qtdeAluno == 0){
    printf("\nLista de alunos vazia.\n\n");
  }else{
    for(int i=0; i<qtdeAluno; i++){
      if(listaAluno[i].ativo == 1){
        printf("Matrícula: %d\n", listaAluno[i].matricula);
        printf("Nome: %s\n", listaAluno[i].nome);
        printf("Data de nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
        printf("Sexo: %c\n", listaAluno[i].sexo);
        printf("CPF: %s\n", listaAluno[i].cpf);
        printf("\n\n");
      }
    }
  }
}

int atualizarAluno(Aluno listaAluno[], int qtdeAluno, Disciplina listaDisciplina[], int qtdeDisciplina, int listaAlunosMatriculados[], int qtdeAlunosMatriculados){
    int matricula;
    char nome[50];
    char sexo;
    Data dataNascimento;
    char cpf[12];


    int novamatricula;
    int atualizada = 0;
    int repetida = 0;
    int tam;

    printf("--- Atualizar Aluno ---\n");
    printf("Digite a matrícula: \n");
    scanf("%d", &matricula);

    if(matricula < 0){
      printf("Matrícula Inválida.\n");
      return MATRICULA_INVALIDA;
    }else{
      for(int i=0; i<qtdeAluno; i++){
        if((matricula == listaAluno[i].matricula)&&(listaAluno[i].ativo)){
          printf("Digite a nova matrícula: \n");
          scanf("%d", &novamatricula);
          if(novamatricula < 0){
            return MATRICULA_INVALIDA;
          }else{
            for(int j=0; j<qtdeAluno; j++){
              if(novamatricula == listaAluno[j].matricula){
                repetida = 1;
                break;
              }
            }
            if(repetida != 1){
                getchar();

                printf("Digite o nome: \n");
                fgets(nome, 50, stdin);
                tam = strlen(nome) - 1;

                if((nome[0] >= 'a') && (nome[0] >= 'z')){
                    nome[0] = nome[0] - 32; 
                }

                if(nome[tam] == '\n'){
                    nome[tam] = '\0';
                }

                printf("Digite o sexo: \nM - Masculino\nF - Feminino\n");
                scanf("%c", &sexo);

                if(((sexo != 'M') && (sexo != 'F')) && ((sexo != 'm') && (sexo != 'f'))){
                    return DADOS_INVALIDOS; 
                }
                printf("Digite a data de nascimento: \n");
                printf("Dia: \n");
                scanf("%d", &dataNascimento.dia);
                if((dataNascimento.dia < 0) || (dataNascimento.dia > 31)){
                    return DADOS_INVALIDOS;
                }
                printf("Mês: \n");
                scanf("%d", &dataNascimento.mes);
                if((dataNascimento.mes < 0) || (dataNascimento.mes > 12)){
                    return DADOS_INVALIDOS;                
                }
                printf("Ano: \n");
                scanf("%d", &dataNascimento.ano);
                if((dataNascimento.ano < 1900) || (dataNascimento.ano > 2024)){
                    return DADOS_INVALIDOS;
                } 
                getchar();
                printf("Digite o CPF: \n");
                fgets(cpf, 12, stdin);

                tam = strlen(cpf) - 1;
                if(cpf[tam] == '\n'){
                    cpf[tam] == '\0';
                }

                // Validar CPF

                if(strlen(cpf) != 11){
                    return DADOS_INVALIDOS;
                }

                for(int p=0; cpf[p] != '\0'; p++){
                    if((cpf[p] <= '0') && (cpf[p] >= '9')){
                        return DADOS_INVALIDOS;
                    }
                }

                // Atualizar o aluno cadastrado na Disciplina

                if(qtdeDisciplina > 0){ // Se existir uma disciplina
                    for(int k=0; k < qtdeDisciplina; k++){
                        for(int m=0; m < qtdeAlunosMatriculados - 1; m++){
                            if(listaAluno[i].matricula == listaDisciplina[k].listaAlunosMatriculados[m].matricula){
                                listaDisciplina[k].listaAlunosMatriculados[m].matricula = novamatricula;
                            }
                        }
                    }
                }

                listaAluno[i].matricula = novamatricula;
                strcpy(listaAluno[i].nome, nome);
                listaAluno[i].sexo = sexo;
                listaAluno[i].dataNascimento.dia = dataNascimento.dia;
                listaAluno[i].dataNascimento.mes = dataNascimento.mes;
                listaAluno[i].dataNascimento.ano = dataNascimento.ano;
                strcpy(listaAluno[i].cpf, cpf);


                atualizada = 1;
                break;
            }
          }
        }
      }
      if(atualizada == 1){
        return MATRICULA_ATUALIZADA;
      }else if(repetida == 1){
        return MATRICULA_REPETIDA;
      }else{
        return NAO_ENCONTRADO;
      }
    }
}

int excluirAluno(Aluno listaAluno[], int qtdeAluno, Disciplina listaDisciplina[], int qtdeDisciplina, int listaAlunosMatriculados[], int qtdeAlunosMatriculados){
  printf("--- Excluir Aluno ---\n");
  printf("Digite a matrícula: \n");
  int matricula;
  scanf("%d", &matricula);
  int achou = 0;
  int alunoEncontrado = 0;
  int m, k; // contadores
  if(matricula < 0){
    return MATRICULA_INVALIDA;
  }else{
        for(int i=0; i<qtdeAluno; i++){
            if(matricula == listaAluno[i].matricula){
                // Excluir o aluno cadastrado na Disciplina
                if(qtdeDisciplina > 0){ // Se existir uma disciplina
                    for(k=0; k < qtdeDisciplina; k++){
                        for(m=0; m < qtdeAlunosMatriculados; m++){
                            if(matricula == listaDisciplina[k].listaAlunosMatriculados[m].matricula){
                                alunoEncontrado = 1;
                                break;
                            }
                        }
                    }
                    if(alunoEncontrado = 1){
                        for(m=0; m <qtdeAlunosMatriculados; m++){
                            listaDisciplina[k].listaAlunosMatriculados[m] = listaDisciplina[k].listaAlunosMatriculados[m+1];
                        }
                    }
                }
                //exclusao lógica//
                listaAluno[i].ativo = -1;
                for(int j=i; j < qtdeAluno - 1; j++){
                  listaAluno[j].matricula = listaAluno[j+1].matricula;
                  listaAluno[j].ativo = listaAluno[j+1].ativo;
                }
                achou = 1;
                break;
            }
        }
        if(achou == 1){
            return MATRICULA_EXCLUIDA;
        } else{
            return NAO_ENCONTRADO;
        }
    }
}

// PROFESSOR -------------------------------------------------------------------------------- 

int menuProfessor(){
  int opcaoProfessor;

  printf("\n\n----Menu Professor----\n");
  printf("1 - Cadastrar Professor\n");
  printf("2 - Listar Professor\n");
  printf("3 - Atualizar Professor\n");
  printf("4 - Excluir Professor\n");

  scanf("%d", &opcaoProfessor);

  return opcaoProfessor;
}

int cadastrarProfessor(Professor listaProfessor[], int qtdeProfessor, Data dataNascimento){
  int matricula;

  printf("\n\n--- Cadastrar Professor ---\n");
  if(qtdeProfessor == TAM_PROFESSOR){
    return LISTA_CHEIA;
  }else{
    printf("Digite a matrícula: \n");
    scanf("%d", &matricula);

    if(matricula < 0){
      return MATRICULA_INVALIDA;
    } else{
      int encontrado=0;
      for(int i=0; i<qtdeProfessor; i++){
        if(matricula == listaProfessor[i].matricula){
          encontrado=1;
        }
      }
      if(encontrado==1){
        return MATRICULA_REPETIDA;
      } else{

        int tam;
        getchar();

        printf("Digite o nome: \n");
        fgets(listaProfessor[qtdeProfessor].nome, 50, stdin);
        tam = strlen(listaProfessor[qtdeProfessor].nome) - 1;

        if((listaProfessor[qtdeProfessor].nome[0] >= 'a') && (listaProfessor[qtdeProfessor].nome[0] >= 'z')){
            listaProfessor[qtdeProfessor].nome[0] = listaProfessor[qtdeProfessor].nome[0] - 32; 
        }

        if(listaProfessor[qtdeProfessor].nome[tam] == '\n'){
            listaProfessor[qtdeProfessor].nome[tam] = '\0';
        }

        printf("Digite o sexo: \nM - Masculino\nF - Feminino\n");
        scanf("%c", &listaProfessor[qtdeProfessor].sexo);

        if(((listaProfessor[qtdeProfessor].sexo != 'M') && (listaProfessor[qtdeProfessor].sexo != 'F')) && ((listaProfessor[qtdeProfessor].sexo != 'm') && (listaProfessor[qtdeProfessor].sexo != 'f'))){
            return DADOS_INVALIDOS; 
        }
        printf("Digite a data de nascimento: \n");
        printf("Dia: \n");
        scanf("%d", &listaProfessor[qtdeProfessor].dataNascimento.dia);
        if((listaProfessor[qtdeProfessor].dataNascimento.dia < 0) || (listaProfessor[qtdeProfessor].dataNascimento.dia > 31)){
            return DADOS_INVALIDOS;
        }
        printf("Mês: \n");
        scanf("%d", &listaProfessor[qtdeProfessor].dataNascimento.mes);
        if((listaProfessor[qtdeProfessor].dataNascimento.mes < 0) || (listaProfessor[qtdeProfessor].dataNascimento.mes > 12)){
            return DADOS_INVALIDOS;                
        }
        printf("Ano: \n");
        scanf("%d", &listaProfessor[qtdeProfessor].dataNascimento.ano);
        if((listaProfessor[qtdeProfessor].dataNascimento.ano < 1900) || (listaProfessor[qtdeProfessor].dataNascimento.ano > 2024)){
            return DADOS_INVALIDOS;
        } 
        getchar();
        printf("Digite o CPF: \n");
        fgets(listaProfessor[qtdeProfessor].cpf, 12, stdin);

        tam = strlen(listaProfessor[qtdeProfessor].cpf) - 1;
        if(listaProfessor[qtdeProfessor].cpf[tam] == '\n'){
            listaProfessor[qtdeProfessor].cpf[tam] == '\0';
        }

        // Validar CPF

        if(strlen(listaProfessor[qtdeProfessor].cpf) != 11){
            return DADOS_INVALIDOS;
        }

        for(int p=0; listaProfessor[qtdeProfessor].cpf[p] != '\0'; p++){
            if((listaProfessor[qtdeProfessor].cpf[p] <= '0') && (listaProfessor[qtdeProfessor].cpf[p] >= '9')){
                return DADOS_INVALIDOS;
            }
        }

        // CADASTRO

        listaProfessor[qtdeProfessor].matricula = matricula; // MATRICULA
        listaProfessor[qtdeProfessor].ativo = 1; //professor ativo// */
        return CADASTRADO_REALIZADO_COM_SUCESSO;
      }
    }
  }
}

void listarProfessor(Professor listaProfessor[], int qtdeProfessor){
  printf("\n--- Listar Professor ---\n");
  if(qtdeProfessor == 0){
    printf("\nLista de Professor vazia.\n\n");
  }else{
    for(int i=0; i<qtdeProfessor; i++){
      if(listaProfessor[i].ativo == 1){
        printf("Matrícula: %d\n", listaProfessor[i].matricula);
        printf("Nome: %s\n", listaProfessor[i].nome);
        printf("Data de nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
        printf("Sexo: %c\n", listaProfessor[i].sexo);
        printf("CPF: %s\n", listaProfessor[i].cpf);
        printf("\n\n");
      }
    }
  }
}

int atualizarProfessor(Professor listaProfessor[], int qtdeProfessor, Disciplina listaDisciplina[], int qtdeDisciplina){
    int matricula;
    char nome[50];
    char sexo;
    Data dataNascimento;
    char cpf[12];

    int novamatricula;
    int atualizada = 0;
    int repetida = 0;

    printf("--- Atualizar Professor ---\n");
    printf("Digite a matrícula: \n");
    scanf("%d", &matricula);

    if(matricula < 0){
      printf("Matrícula Inválida.\n");
      return MATRICULA_INVALIDA;
    }else{
      for(int i=0; i<qtdeProfessor; i++){
        if((matricula == listaProfessor[i].matricula)&&(listaProfessor[i].ativo)){
          printf("Digite a nova matrícula: \n");
          scanf("%d", &novamatricula);
          if(novamatricula < 0){
            return MATRICULA_INVALIDA;
          }else{
            for(int j=0; j < qtdeProfessor; j++){
              if(novamatricula == listaProfessor[j].matricula){
                repetida = 1;
                break;
              }
            }
            if(repetida != 1){
                int tam;
                getchar();

                printf("Digite o nome: \n");
                fgets(nome, 50, stdin);
                tam = strlen(nome) - 1;

                if((nome[0] >= 'a') && (nome[0] >= 'z')){
                    nome[0] = nome[0] - 32; 
                }

                if(nome[tam] == '\n'){
                    nome[tam] = '\0';
                }

                printf("Digite o sexo: \nM - Masculino\nF - Feminino\n");
                scanf("%c", &sexo);

                if(((sexo != 'M') && (sexo != 'F')) && ((sexo != 'm') && (sexo != 'f'))){
                    return DADOS_INVALIDOS; 
                }
                printf("Digite a data de nascimento: \n");
                printf("Dia: \n");
                scanf("%d", &dataNascimento.dia);
                if((dataNascimento.dia < 0) || (dataNascimento.dia > 31)){
                    return DADOS_INVALIDOS;
                }
                printf("Mês: \n");
                scanf("%d", &dataNascimento.mes);
                if((dataNascimento.mes < 0) || (dataNascimento.mes > 12)){
                    return DADOS_INVALIDOS;                
                }
                printf("Ano: \n");
                scanf("%d", &dataNascimento.ano);
                if((dataNascimento.ano < 1900) || (dataNascimento.ano > 2024)){
                    return DADOS_INVALIDOS;
                } 

                getchar();
                printf("Digite o CPF: \n");
                fgets(cpf, 12, stdin);

                tam = strlen(cpf) - 1;
                if(cpf[tam] == '\n'){
                    cpf[tam] == '\0';
                }

                // Validar CPF

                if(strlen(cpf) != 11){
                    return DADOS_INVALIDOS;
                }

                for(int p=0; cpf[p] != '\0'; p++){
                    if((cpf[p] <= '0') && (cpf[p] >= '9')){
                        return DADOS_INVALIDOS;
                    }
                }

                listaProfessor[i].matricula = novamatricula;
                strcpy(listaProfessor[i].nome, nome);
                listaProfessor[i].sexo = sexo;
                listaProfessor[i].dataNascimento.dia = dataNascimento.dia;
                listaProfessor[i].dataNascimento.mes = dataNascimento.mes;
                listaProfessor[i].dataNascimento.ano = dataNascimento.ano;
                strcpy(listaProfessor[i].cpf, cpf);

                // ATUALIZAÇÃO DO PROFESSOR CADASTRADO NA DISCIPLINA //
                for(int k=0; k<qtdeDisciplina; k++){
                    if(matricula == listaDisciplina[i].matriculaProfessor){
                        listaDisciplina[i].matriculaProfessor = listaProfessor[i].matricula;
                        strcpy(listaDisciplina[k].professorDisciplina, listaProfessor[i].nome);
                    }
                }
                atualizada = 1;
                break;
            }
          }
        }
      }
      if(atualizada == 1){
        return MATRICULA_ATUALIZADA;
      }else if(repetida == 1){
        return MATRICULA_REPETIDA;
      }else{
        return NAO_ENCONTRADO;
      }
    }
}

int excluirProfessor(Professor listaProfessor[], int qtdeProfessor){
  printf("--- Excluir Professor ---\n");
  printf("Digite a matrícula: \n");
  int matricula;
  scanf("%d", &matricula);
  int achou = 0;
  if(matricula < 0){
    return MATRICULA_INVALIDA;
  }else{
    for(int i=0; i<qtdeProfessor; i++){
      if(matricula == listaProfessor[i].matricula){
        //exclusao lógica//
        listaProfessor[i].ativo = -1;
        for(int j=i; j < qtdeProfessor - 1; j++){
          listaProfessor[j].matricula = listaProfessor[j+1].matricula;
          listaProfessor[j].ativo = listaProfessor[j+1].ativo;
        }
        achou = 1;
        break;
      }
    }
    if(achou == 1){
      return MATRICULA_EXCLUIDA;
    } else{
      return NAO_ENCONTRADO;
    }
  } 
}

// DISCIPLINA

// Disciplina NOME, CÓDIGO,  SEMESTRE, PROFESSOR;

int menuDisciplina(){
  int opcaoDisciplina;

  printf("\n\n----Menu Disciplina----\n");
  printf("1 - Cadastrar Disciplina\n");
  printf("2 - Listar Disciplina\n");
  printf("3 - Atualizar Disciplina\n");
  printf("4 - Excluir Disciplina\n");
  printf("5 - Inserir Aluno na Disciplina\n");
  printf("6 - Excluir Aluno da Disciplina\n");


  scanf("%d", &opcaoDisciplina);

  return opcaoDisciplina;
}

int cadastrarDisciplina(Disciplina listaDisciplina[], int qtdeDisciplina, Professor listaProfessor[]){
  int codigoDisciplina;
  int semestre;
  int matriculaProfessor;


  printf("\n\n--- Cadastrar Disciplina ---\n");

  if(qtdeDisciplina == TAM_DISCIPLINA){
    return LISTA_CHEIA;
  }

  printf("Digite o codigo da Disciplina: \n");
  scanf("%d", &codigoDisciplina);

  if(codigoDisciplina < 0){
      return MATRICULA_INVALIDA;
  }

  for(int i=0; i<qtdeDisciplina; i++){
    if(codigoDisciplina == listaDisciplina[i].codigoDisciplina){
      return MATRICULA_REPETIDA;
    }
  }

  int tam;
  getchar();

  printf("Digite o nome: \n");
  fgets(listaDisciplina[qtdeDisciplina].nome, 50, stdin);
  tam = strlen(listaDisciplina[qtdeDisciplina].nome) - 1;

  if(listaDisciplina[qtdeDisciplina].nome[tam] == '\n'){
    listaDisciplina[qtdeDisciplina].nome[tam] = '\0';
  }

  printf("Digite o semestre da Disciplina: \n");
  scanf("%d", &semestre);

    if((semestre < 1) || (semestre > 12)){
        return DADOS_INVALIDOS;
    }

    listaDisciplina[qtdeDisciplina].semestre = semestre;

    printf("Digite a matricula do professor para cadastrar na Disciplina: \n");
    scanf("%d", &matriculaProfessor);

    if(matriculaProfessor < 0){
        return MATRICULA_INVALIDA;
    } else{
        int encontrado=0;
        for(int i=0; i<TAM_PROFESSOR; i++){
            if(matriculaProfessor == listaProfessor[i].matricula){
                listaDisciplina[qtdeDisciplina].matriculaProfessor = matriculaProfessor;
                strcpy(listaDisciplina[qtdeDisciplina].professorDisciplina, listaProfessor[i].nome);
                encontrado = 1;
            }
        }
        if(encontrado != 1){
            return NAO_ENCONTRADO;
        }

        listaDisciplina[qtdeDisciplina].codigoDisciplina = codigoDisciplina; // MATRICULA
        listaDisciplina[qtdeDisciplina].ativo = 1; //Disciplina ativo// */
        return CADASTRADO_REALIZADO_COM_SUCESSO;
    }
}


void listarDisciplina(Disciplina listaDisciplina[], int qtdeDisciplina){
  printf("\n--- Listar Disciplina ---\n");
  if(qtdeDisciplina == 0){
    printf("\nLista de Disciplinas vazia.\n\n");
  }else{
    for(int i=0; i<qtdeDisciplina; i++){
      if(listaDisciplina[i].ativo == 1){
        printf("Código da Disciplina: %d\n", listaDisciplina[i].codigoDisciplina);
        printf("Nome da Disciplina: %s\n", listaDisciplina[i].nome);
        printf("Semestre: %d\n", listaDisciplina[i].semestre);
        printf("Nome do Professor: %s\n", listaDisciplina[i].professorDisciplina);
        printf("\n\n");
      }
    }
  }
}

int atualizarDisciplina(Disciplina listaDisciplina[], int qtdeDisciplina, Professor listaProfessor[], int qtdeProfessor){
    int codigoDisciplina;
    char nome[50];
    int semestre;
    int matriculaProfessor;
    char professorDisciplina[50];

    int novoCodigoDisciplina;
    int atualizada = 0;
    int encontrado=0;
    int repetida = 0;
    int tam = 0;

    printf("--- Atualizar Disciplina ---\n");
    printf("Digite o Codigo da Disciplina: \n");
    scanf("%d", &codigoDisciplina);

    if(codigoDisciplina < 0){
        return MATRICULA_INVALIDA;
    }

    if(codigoDisciplina < 0){
      printf("Codigo da Disciplina Inválido.\n");
      return MATRICULA_INVALIDA;
    }else{
      for(int i=0; i<qtdeDisciplina; i++){
        if((codigoDisciplina == listaDisciplina[i].codigoDisciplina)&&(listaDisciplina[i].ativo)){
          printf("Digite o novo Codigo da Disciplina: \n");
          scanf("%d", &novoCodigoDisciplina);
          if(novoCodigoDisciplina < 0){
            return MATRICULA_INVALIDA;
          }else{
            for(int j=0; j<qtdeDisciplina; j++){
              if(novoCodigoDisciplina == listaDisciplina[j].codigoDisciplina){
                repetida = 1;
                break;
              }
            }
            if(repetida != 1){
                getchar();
                printf("Digite o nome: \n");
                fgets(nome, 50, stdin);
                tam = strlen(nome) - 1;

                if(nome[tam] == '\n'){
                    nome[tam] = '\0';
                }
                printf("Digite o semestre da Disciplina: \n");
                scanf("%d", &semestre);

                if((semestre < 1) || (semestre > 12)){
                    return DADOS_INVALIDOS;
                }

                int matriculaProfessor;

                printf("Digite a matricula do professor para cadastrar na Disciplina: \n");
                scanf("%d", &matriculaProfessor);

                if(matriculaProfessor < 0){
                    return MATRICULA_INVALIDA;
                } else{
                    for(int k=0; k<TAM_PROFESSOR; k++){
                        if(matriculaProfessor == listaProfessor[k].matricula){
                            listaDisciplina[i].matriculaProfessor = matriculaProfessor;
                            strcpy(listaDisciplina[i].professorDisciplina, listaProfessor[k].nome);
                            // O restante das atualizações (nome da Disciplina, semestre, novoCodigoDisciplina)
                            strcpy(listaDisciplina[i].nome, nome);
                            listaDisciplina[i].semestre = semestre;
                            listaDisciplina[i].codigoDisciplina = novoCodigoDisciplina; // MATRICULA
                            encontrado = 1;
                        }
                    }
                }
            }
          }
          if(encontrado == 1){
              return MATRICULA_ATUALIZADA;
          }else if(repetida == 1){
              return MATRICULA_REPETIDA;
          }else{
              return NAO_ENCONTRADO;
          }
        }
      }
    }
}

int excluirDisciplina(Disciplina listaDisciplina[], int qtdeDisciplina){
  printf("--- Excluir Disciplina ---\n");
  printf("Digite o código da Disciplina: \n");
  int codigoDisciplina;
  scanf("%d", &codigoDisciplina);
  int achou = 0;
  if(codigoDisciplina < 0){
    return MATRICULA_INVALIDA;
  }else{
    for(int i=0; i<qtdeDisciplina; i++){
      if(codigoDisciplina == listaDisciplina[i].codigoDisciplina){
        //exclusao lógica//
        listaDisciplina[i].ativo = -1;
        for(int j=i; j < qtdeDisciplina - 1; j++){
          listaDisciplina[j].codigoDisciplina = listaDisciplina[j+1].codigoDisciplina;
          listaDisciplina[j].ativo = listaDisciplina[j+1].ativo;
        }
        achou = 1;
        break;
      }
    }
    if(achou == 1){
      return MATRICULA_EXCLUIDA;
    } else{
      return NAO_ENCONTRADO;
    }
  } 
}

int inserirAlunoDisciplina(Disciplina listaDisciplina[], int qtdeDisciplina, Aluno listaAluno[], int qtdeAluno, AlunosMatriculados listaAlunosMatriculados[], int qtdeAlunosMatriculados){
    int matricula;
    int codigoDisciplina;
    char nome[50];
    int achou = 0;
    int k = 0;

    printf("--- Inserir Aluno na Disciplina ---\n");
    printf("Digite o código da Disciplina: \n");
    scanf("%d", &codigoDisciplina);
    if(codigoDisciplina < 0){
        return MATRICULA_INVALIDA;
    }else{
        for(int i=0; i<qtdeDisciplina; i++){
            if(codigoDisciplina == listaDisciplina[i].codigoDisciplina){
                achou = 1;
                k = i;
                break;
            }
        }
        if(achou == 1){
            printf("Digite a matricula do Aluno para inserir na Disciplina: \n");
            scanf("%d", &matricula);

            if(matricula < 0){
                return MATRICULA_INVALIDA;
            } else{
                int encontrado=0;
                for(int j=0;j<qtdeAluno; j++){
                    if(matricula == listaAluno[j].matricula){
                        strcpy(nome, listaAluno[j].nome);
                        encontrado = 1;
                        break;
                    }
                }
                if(encontrado != 1){
                    return NAO_ENCONTRADO;
                } else{
                    listaDisciplina[k].listaAlunosMatriculados[qtdeAlunosMatriculados].matricula = matricula;
                    strcpy(listaDisciplina[k].listaAlunosMatriculados[qtdeAlunosMatriculados].nome, nome);
                    listaDisciplina[k].listaAlunosMatriculados[qtdeAlunosMatriculados].ativo = 1;
                    return CADASTRADO_REALIZADO_COM_SUCESSO;
                }
            }
        } else{
            return MATRICULA_INVALIDA;
        }
    }
}

int excluirAlunoDisciplina(Disciplina listaDisciplina[], int qtdeDisciplina, Aluno listaAluno[], int qtdeAluno, AlunosMatriculados listaAlunosMatriculados[], int qtdeAlunosMatriculados){
    int matricula;
    int codigoDisciplina;        
    int achou = 0;
    int p;
    int k = 0; // posição da disciplina

    printf("--- Excluir Aluno na Disciplina ---\n");
    printf("Digite o código da Disciplina: \n");
    scanf("%d", &codigoDisciplina);
    if(codigoDisciplina < 0){
        return MATRICULA_INVALIDA;
    }else{
        for(int i=0; i<qtdeDisciplina; i++){
            if(codigoDisciplina == listaDisciplina[i].codigoDisciplina){
                achou = 1;
                k = i; // posição da disciplina
                break;
            }
        }
        if(achou == 1){
            printf("Digite a matricula do Aluno para excluir na Disciplina: \n");
            scanf("%d", &matricula);

            int encontrado=0;
            for(int j=0; j<qtdeAlunosMatriculados; j++){
                if((matricula == listaDisciplina[k].listaAlunosMatriculados[j].matricula) && (listaDisciplina[k].listaAlunosMatriculados[j].ativo == 1)){
                    listaDisciplina[k].listaAlunosMatriculados[j].ativo = -1;
                    encontrado = 1;
                    for(p = j; p < qtdeAlunosMatriculados - 1; p++){
                        listaDisciplina[k].listaAlunosMatriculados[p] = listaDisciplina[k].listaAlunosMatriculados[p+1];
                    }
                    break;
                }
            }
            if(encontrado == 1){
                return MATRICULA_EXCLUIDA;
            } else{
                return NAO_ENCONTRADO;
            }
        } else{
            return NAO_ENCONTRADO;
        }
    }
}

// RELATÓRIOS

int menuRelatorio(){
  int opcaoRelatorio;

  printf("\n\n----Menu Relatorio----\n");
  printf("1 - Listar Alunos\n");
  printf("2 - Listar Professores\n");
  printf("3 - Listar Disciplinas\n");
  printf("4 - Listar uma Disciplina\n");
  printf("5 - Listar Alunos por sexo (Masculino/Feminino)\n");
  printf("6 - Listar Alunos ordenados por Nome\n");
  printf("7 - Listar Alunos ordenados por data de nascimento\n");
  printf("8 - Listar Professores por sexo (Masculino/Feminino)\n");
  printf("9 - Listar Professores ordenados por Nome\n");
  printf("10 - Listar Professores ordenados por data de nascimento\n");
  printf("11 - Listar Aniversariantes do Mês\n");
  printf("12 - Listar Pessoas por String de Busca\n");
  printf("13 - Listar Alunos Matriculados em menos de 3 Disciplinas\n");
  printf("14 - Listar Disciplinas que extrapolam 40 vagas\n");

  scanf("%d", &opcaoRelatorio);

  return opcaoRelatorio;
}

// Listar Alunos, Professores, Disciplinas

void listarUmaDisciplina(Disciplina listaDisciplina[], int qtdeDisciplina, Disciplina listaAlunosMatriculados[], int qtdeAlunosMatriculados){
    int codigoDisciplina;
    int i, p;
    printf("\n--- Listar Uma Disciplina ---\n");
    printf("Digite o código da Disciplina: \n");
    scanf("%d", &codigoDisciplina);
    int encontrado=0;
    for(i=0; i<qtdeDisciplina; i++){
        if(codigoDisciplina == listaDisciplina[i].codigoDisciplina){
            encontrado=1;
            p=i;
            break;
        }
    }
    if(encontrado == 1){
            printf("Código da Disciplina: %d\n", listaDisciplina[p].codigoDisciplina);
            printf("Nome da Disciplina: %s\n", listaDisciplina[p].nome);
            printf("Semestre: %d\n", listaDisciplina[p].semestre);
            printf("Nome do Professor: %s\n", listaDisciplina[p].professorDisciplina);

            if(qtdeAlunosMatriculados == 0){
                printf("\nNão há alunos Matriculados nesta Disciplina.\n");
            } else{
                printf("\n- Alunos Matriculados na Disciplina -\n");
                for(int j = 0; j < qtdeAlunosMatriculados; j++){
                    if((listaDisciplina[p].listaAlunosMatriculados[j].matricula > 0) &&(listaDisciplina[p].listaAlunosMatriculados[j].ativo)){
                        printf("Matrícula: %d \n", listaDisciplina[p].listaAlunosMatriculados[j].matricula);
                        printf("Nome: %s \n", listaDisciplina[p].listaAlunosMatriculados[j].nome);
                    }
                }
            }
    } else{
        printf("Disciplina não encontrada");
    }
}

void listarAlunosPorSexo(Aluno listaAluno[], int qtdeAluno){
    printf("\n--- Listar Alunos Por Sexo ---\n");
    if(qtdeAluno == 0){
        printf("\nLista de alunos vazia.\n\n");
    } else{
        printf("\n- Sexo Masculino -\n");
        for(int i=0; i<qtdeAluno; i++){
            if((listaAluno[i].sexo == 'M') || (listaAluno[i].sexo == 'm')){
                if(listaAluno[i].ativo){
                    printf("Nome: %s\n", listaAluno[i].nome);                }
            }
        }
        printf("\n- Sexo Feminino -\n");
        for(int i=0; i<qtdeAluno; i++){
            if((listaAluno[i].sexo == 'F') || (listaAluno[i].sexo == 'f')){
                if(listaAluno[i].ativo){
                    printf("Nome: %s\n", listaAluno[i].nome);                }
            }
        }
    }
}

void listarAlunosPorNome(Aluno listaAluno[], int qtdeAluno, Aluno listaAlunoAuxiliar[], int qtdeAlunoAuxiliar){
    char auxiliar[50];
    printf("\n--- Listar Alunos Ordenado por Nome (Ordem Alfabética)---\n");
    if(qtdeAluno == 0){
        printf("\nLista de alunos vazia.\n\n");
    } else{
        for(int i=0; i<qtdeAluno; i++){
            strcpy(listaAlunoAuxiliar[i].nome, listaAluno[i].nome);
        }
        for(int i=0; i < qtdeAluno - 1; i++){
            for(int j=0; j < qtdeAluno - i - 1; j++){
                if(strcmp(listaAlunoAuxiliar[j].nome, listaAlunoAuxiliar[j+1].nome) > 0){
                    strcpy(auxiliar, listaAlunoAuxiliar[j].nome);
                    strcpy(listaAlunoAuxiliar[j].nome, listaAlunoAuxiliar[j+1].nome);
                    strcpy(listaAlunoAuxiliar[j+1].nome, auxiliar);
                }
            }
        }
        for(int i=0; i < qtdeAluno; i++){
            printf("Nome: %s\n", listaAlunoAuxiliar[i].nome);
        }
    }
}

void listarAlunosPorDataNascimento(Aluno listaAluno[], int qtdeAluno, Aluno listaAlunoAuxiliar[], int qtdeAlunoAuxiliar){
    Aluno auxiliar;
    qtdeAlunoAuxiliar = qtdeAluno;
    for(int i=0; i< qtdeAluno; i++){
        listaAlunoAuxiliar[i] = listaAluno[i];
    }
    printf("\n--- Listar Alunos Ordenado por Data de Nascimento (Ordem Crescente)---\n");
    if(qtdeAluno == 0){
        printf("\nLista de alunos vazia.\n\n");
    } else{
        for(int i=0; i < qtdeAlunoAuxiliar - 1; i++){
            for(int j=0; j < qtdeAlunoAuxiliar - i - 1; j++){
                if(listaAlunoAuxiliar[j].dataNascimento.ano > listaAlunoAuxiliar[j+1].dataNascimento.ano || (listaAlunoAuxiliar[j].dataNascimento.ano == listaAlunoAuxiliar[j+1].dataNascimento.ano && listaAlunoAuxiliar[j].dataNascimento.mes > listaAlunoAuxiliar[j+1].dataNascimento.mes) || (listaAlunoAuxiliar[j].dataNascimento.ano == listaAlunoAuxiliar[j+1].dataNascimento.ano && listaAlunoAuxiliar[j].dataNascimento.mes == listaAlunoAuxiliar[j+1].dataNascimento.mes && listaAlunoAuxiliar[j].dataNascimento.dia == listaAlunoAuxiliar[j+1].dataNascimento.dia)){
                    auxiliar = listaAlunoAuxiliar[j];
                    listaAlunoAuxiliar[j] = listaAlunoAuxiliar[j+1];
                    listaAlunoAuxiliar[j+1] = auxiliar;
                }
            }
        }
        for(int i=0; i < qtdeAlunoAuxiliar; i++){
            printf("Nome: %s\n", listaAlunoAuxiliar[i].nome);
            printf("Data Nascimento: %d/%d/%d\n\n", listaAlunoAuxiliar[i].dataNascimento.dia, listaAlunoAuxiliar[i].dataNascimento.mes, listaAlunoAuxiliar[i].dataNascimento.ano);
        }
    }
}

void listarProfessoresPorSexo(Professor listaProfessor[], int qtdeProfessor){
    printf("\n--- Listar Professores Por Sexo ---\n");
    if(qtdeProfessor == 0){
        printf("\nLista de Professores vazia.\n\n");
    } else{
        printf("\n- Sexo Masculino -\n");
        for(int i=0; i<qtdeProfessor; i++){
            if((listaProfessor[i].sexo == 'M') || (listaProfessor[i].sexo == 'm')){
                if(listaProfessor[i].ativo){
                    printf("Nome: %s\n", listaProfessor[i].nome);                }
            }
        }
        printf("\n- Sexo Feminino -\n");
        for(int i=0; i<qtdeProfessor; i++){
            if((listaProfessor[i].sexo == 'F') || (listaProfessor[i].sexo == 'f')){
                if(listaProfessor[i].ativo){
                    printf("Nome: %s\n", listaProfessor[i].nome);                }
            }
        }
    }
}

void listarProfessoresPorNome(Professor listaProfessor[], int qtdeProfessor, Professor listaProfessorAuxiliar[], int qtdeProfessorAuxiliar){
    char auxiliar[50];
    printf("\n--- Listar Professores Ordenado por Nome (Ordem Alfabética)---\n");
    if(qtdeProfessor == 0){
        printf("\nLista de Professores vazia.\n\n");
    } else{
        for(int i=0; i<qtdeProfessor; i++){
            strcpy(listaProfessorAuxiliar[i].nome, listaProfessor[i].nome);
        }
        for(int i=0; i < qtdeProfessor - 1; i++){
            for(int j=0; j < qtdeProfessor - i - 1; j++){
                if(strcmp(listaProfessorAuxiliar[j].nome, listaProfessorAuxiliar[j+1].nome) > 0){
                    strcpy(auxiliar, listaProfessorAuxiliar[j].nome);
                    strcpy(listaProfessorAuxiliar[j].nome, listaProfessorAuxiliar[j+1].nome);
                    strcpy(listaProfessorAuxiliar[j+1].nome, auxiliar);
                }
            }
        }
        for(int i=0; i < qtdeProfessor; i++){
            printf("Nome: %s\n", listaProfessorAuxiliar[i].nome);
        }
    }
}

void listarProfessoresPorDataNascimento(Professor listaProfessor[], int qtdeProfessor, Professor listaProfessorAuxiliar[], int qtdeProfessorAuxiliar){
    Professor auxiliar;
    qtdeProfessorAuxiliar = qtdeProfessor;
    for(int i=0; i< qtdeProfessor; i++){
        listaProfessorAuxiliar[i] = listaProfessor[i];
    }
    printf("\n--- Listar Professores Ordenado por Data de Nascimento (Ordem Crescente)---\n");
    if(qtdeProfessor == 0){
        printf("\nLista de Professores vazia.\n\n");
    } else{
        for(int i=0; i < qtdeProfessorAuxiliar - 1; i++){
            for(int j=0; j < qtdeProfessorAuxiliar - i - 1; j++){
                if(listaProfessorAuxiliar[j].dataNascimento.ano > listaProfessorAuxiliar[j+1].dataNascimento.ano || (listaProfessorAuxiliar[j].dataNascimento.ano == listaProfessorAuxiliar[j+1].dataNascimento.ano && listaProfessorAuxiliar[j].dataNascimento.mes > listaProfessorAuxiliar[j+1].dataNascimento.mes) || (listaProfessorAuxiliar[j].dataNascimento.ano == listaProfessorAuxiliar[j+1].dataNascimento.ano && listaProfessorAuxiliar[j].dataNascimento.mes == listaProfessorAuxiliar[j+1].dataNascimento.mes && listaProfessorAuxiliar[j].dataNascimento.dia == listaProfessorAuxiliar[j+1].dataNascimento.dia)){
                    auxiliar = listaProfessorAuxiliar[j];
                    listaProfessorAuxiliar[j] = listaProfessorAuxiliar[j+1];
                    listaProfessorAuxiliar[j+1] = auxiliar;
                }
            }
        }
        for(int i=0; i < qtdeProfessorAuxiliar; i++){
            printf("Nome: %s\n", listaProfessorAuxiliar[i].nome);
            printf("Data Nascimento: %d/%d/%d\n\n", listaProfessorAuxiliar[i].dataNascimento.dia, listaProfessorAuxiliar[i].dataNascimento.mes, listaProfessorAuxiliar[i].dataNascimento.ano);
        }
    }
}

void listarAniversariantesDoMes(Aluno listaAluno[], int qtdeAluno, Professor listaProfessor[], int qtdeProfessor){
    int op;
    printf("\n--- Listar os Aniversariantes do Mês ---\n");
    if((qtdeProfessor == 0) && (qtdeAluno == 0)){
        printf("\nLista de Professores vazia.\n");
    } else{
        printf("Digite o número do Mês (de 1 a 12): \n");
        scanf("%d", &op);
        switch (op){
            case 1:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 1){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 1){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            case 2:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 2){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 2){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            case 3:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 3){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 3){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            case 4:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 4){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 4){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            case 5:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 5){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 5){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            case 6:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 6){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 6){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            case 7:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 7){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 7){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            case 8:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 8){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 8){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            case 9:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 9){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 9){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            case 10:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 10){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 10){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            case 11:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 11){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 11){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            case 12:{
                for(int i = 0; i < qtdeAluno; i++){
                    if(listaAluno[i].dataNascimento.mes == 12){
                        printf("Nome: %s\n", listaAluno[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaAluno[i].dataNascimento.dia, listaAluno[i].dataNascimento.mes, listaAluno[i].dataNascimento.ano);
                    }
                }
                for(int i = 0; i < qtdeProfessor; i++){
                    if(listaProfessor[i].dataNascimento.mes == 12){
                        printf("Nome: %s\n", listaProfessor[i].nome);
                        printf("Data de Nascimento: %d/%d/%d\n", listaProfessor[i].dataNascimento.dia, listaProfessor[i].dataNascimento.mes, listaProfessor[i].dataNascimento.ano);
                    }
                }
                break;
            }
            default:{
                printf("Opção Inválida.\n");
            }
        }
    }
}

//  Lista de Pessoas (busca string)
void converterMaiuMinusculo(char palavra[]){
    for(int i=0; palavra[i]; i++){
        palavra[i] = tolower(palavra[i]);
    }
}

int listarPessoasPorStringBusca(Aluno listaAluno[], int qtdeAluno, Professor listaProfessor[], int qtdeProfessor){
    printf("\n--- Listar Pesssoas (Alunos e Professores) por uma string de busca ---\n");
    int tam; // tamanho da busca
    char nomeAuxiliar[50];
    char stringBusca[50];

    getchar();
    printf("\nDigite de 1 a 3 caracteres para buscar o nome: \n");
    fgets(stringBusca, 50, stdin);

    tam = strlen(stringBusca);
    if(stringBusca[tam-1] =='\n'){
        stringBusca[tam-1] = '\0';
    }

    if(tam < 3){
        printf("A palavra digitada tem menos de 3 letras.\n");
    } else{
        // Procurando na lista Aluno
        for(int i=0; i<tam; i++){
            strcpy(nomeAuxiliar, listaAluno[i].nome);
            converterMaiuMinusculo(nomeAuxiliar);
            if(strstr(nomeAuxiliar, stringBusca)){
                printf("Nome: %s\n", listaAluno[i].nome);
            }
        }
        // Procurando na lista Professor
        for(int i=0; i<tam; i++){
            strcpy(nomeAuxiliar, listaProfessor[i].nome);
            converterMaiuMinusculo(nomeAuxiliar);
            if(strstr(nomeAuxiliar, stringBusca)){
                printf("Nome: %s\n", listaProfessor[i].nome);
            }
        }
    }
}

void listarAlunosMatriculadosEmTresDisciplinas(Aluno listaAluno[], int qtdeAluno, Disciplina listaDisciplina[], int qtdeDisciplina, int qtdeAlunosMatriculados, int alunoQtdeMaterias[]){
    int cont;
    printf("\n--- Listar Alunos Matriculados em menos de 3 disciplinas ---\n");
    for(int i=0; i < qtdeAluno; i++){
        for(int j=0; j<qtdeDisciplina; j++){
            cont = 0;
            for(int k=0; k<qtdeAlunosMatriculados; k++){
                if(listaAluno[i].matricula == listaDisciplina[j].listaAlunosMatriculados[k].matricula){
                    cont++;
                }
            }
            alunoQtdeMaterias[i] = cont;
        }
    }

    for(int i=0; i < qtdeAluno; i++){
        if(alunoQtdeMaterias[i] < 3){
            printf("Nome: %s\n", listaAluno[i].nome);
            printf("Quantidade de disciplinas que está Matriculado: %d\n", alunoQtdeMaterias[i]);
        }
    }
}

void listarDisciplinasAcima40Vagas(Disciplina listaDisciplina[], int qtdeDisciplina){
    printf("\n--- Listar Disciplinas com mais de 40 vagas ---\n");
    int encontrado= 0;
    for(int i=0; i<qtdeDisciplina; i++){
        if(listaDisciplina[i].qtdeAlunosMatriculados > 40){
            encontrado = 1;
            printf("Disciplina: %s\n", listaDisciplina[i].nome);
        }
    }
    if(encontrado!=1){
        printf("Disciplina não encontrada.\n");
    }
}
