#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "conta.h"

//fun��o para abertura de conta
void abrirConta(TipoConta *conta){
    printf("INTRODUZA OS DADOS DA CONTA:\n");

    //leitura do n�mero de conta
    printf("N�mero > ");
    scanf("%d", &conta->numero);
    fflush(stdin);

    //leitura do n�mero de titulares
    printf("N� de titulares > ");
    scanf("%d", &conta->totalTitulares);
    fflush(stdin);

    //leitura dos dados dos titulares
    for(int i = 0; i < conta->totalTitulares; i++){
        printf("TITULAR %d\n", i+1);

        printf("NIF > ");
        scanf("%d", &conta->titulares[i].nif);

        getchar();

        printf("Nome > ");
        gets(conta->titulares[i].nome);
    }
    fflush(stdin);

    //leitura da modalidade
    printf("Modalidade da Conta (Normal:0 / Isenta:1) > ");
    scanf("%d", &conta->modalidade);
    fflush(stdin);

    //leitura do montante inicial
    do{
        printf("Saldo > ");
        scanf("%f", &conta->saldo);

        if(conta->saldo < 150)
            printf("O saldo inicial deve ser igual ou superior a 150�!\n");
    } while(conta->saldo < 150);
    fflush(stdin);

    //leitura da data de abertura
    printf("Data de Abertura (dia/mes/ano) > ");
    scanf("%d/%d/%d", &conta->data.dia, &conta->data.mes, &conta->data.ano);
    fflush(stdin);
}

//fun��o que escreve os detalhes de uma conta
void imprimirConta(TipoConta conta){
    printf("----------------\n");

    printf("N�mero: %d\n", conta.numero);

    printf("TITULARES\n");
    for(int i = 0; i < conta.totalTitulares; i++){
        printf("Titular %d: ", i+1);
        printf("| Nome: %-25s ", conta.titulares[i].nome);
        printf("| NIF: %d\n", conta.titulares[i].nif);
    }

    if(conta.modalidade == 0)
        printf("Modalidade: Normal\n");
    else
        printf("Modalidade: Isenta\n");

    printf("Saldo: %.2f EUR \n", conta.saldo);

    printf("Hist�rico (�tlimos 3 movimentos)\n");
    for(int i = 0; i < 3; i++){
        printf("Descri��o: %s | ", conta.historico[i].descricao);
        printf("Valor: %.2f\n", conta.historico[i].valor);
    }

    printf("Data de abertura: %d/%d/%d\n", conta.data.dia, conta.data.mes, conta.data.ano);

    printf("----------------\n");
}

//fun��o para conuslta dos detalhes de uma conta (dado o respetivo n�mero)
void consultarDetalhesConta(TipoConta contas[], int numAtualContas){
    int numContaConsultar = 0;

    printf("Introduza o n�mero de conta para consultar os detalhes: ");
    scanf("%d", &numContaConsultar);

    fflush(stdin);

    for(int i = 0; i < numAtualContas; i++){
        if(contas[i].numero == numContaConsultar){
            imprimirConta(contas[i]);
        }
        else
            printf("A conta n�o existe!\n");
    }
}

//fun��o para dep�sito de dinheiro numa conta
void depositarDinheiro(TipoConta *conta){
    float montante = 0.0;

    printf("Introduza a montante a depositar na conta > ");
    scanf("%f", &montante);

    conta->saldo += montante;
}

//fun��o para levantamento de dinheiro de uma conta
void levantarDinheiro(TipoConta *conta){
    float montante = 0.0;

    printf("Introduza a montante que pretente levantar da conta > ");
    scanf("%f", &montante);

    if(montante > conta->saldo){
        printf("\nERRO: SALDO INSUFICIENTE");
    }
    else if(montante > 0){
        conta->saldo -= montante;
        printf("\nMontante levantada com sucesso (%f)", montante);
    }
}

//fun��o para transfer�ncia de dinheiro numa conta
void transferirDinheiro(TipoConta *contaOrigem, TipoConta *contaDestino){
    float montante = 0.0;

    printf("Introduza a montante que pretente transferir da conta origem > ");
    scanf("%f", &montante);

    if(montante > contaOrigem->saldo){
        printf("\nERRO: SALDO INSUFICIENTE");
    }
    else if(montante > 0){
        contaOrigem->saldo -= montante;
        contaDestino->saldo += montante;
        printf("\nMontante transferida com sucesso (%f)", montante);
    }
}
