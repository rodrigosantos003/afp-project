#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "conta.h"

//fun��o para leitura do n�mero de conta e verifica��o da sua exist�ncia
int lerNumConta(TipoConta contas[], int numAtualContas){
    int numConta = 0;

    printf("Introduza o n�mero de conta: ");
    scanf("%d", &numConta);
    fflush(stdin);

    for(int i = 0; i < numAtualContas; i++){
        if(contas[i].numero == numConta)
            return i;
        else{
            printf("A conta n�o existe!\n");
            return -1;
        }
    }
}

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
            printf("O saldo inicial deve ser igual ou superior a 150 EUR!\n");
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

    printf("Hist�rico (�ltimos 3 movimentos)\n");
    for(int i = 0; i < 3; i++){
        printf("Descri��o: %s | ", conta.historico[i].descricao);
        printf("Valor: %.2f\n", conta.historico[i].valor);
    }

    printf("Data de abertura: %02d/%02d/%4d\n", conta.data.dia, conta.data.mes, conta.data.ano);

    printf("----------------\n");
}

//fun��o para verifica��o de saldo suficiente
int verificarSaldoConta(TipoConta *conta, float montante){
    if(conta->saldo > montante) return 1;
    return 0;
}

//fun��o para dep�sito de dinheiro numa conta
void depositarDinheiro(TipoConta *conta){
    float montante = 0.0;

    printf("Introduza a montante a depositar na conta > ");
    scanf("%f", &montante);

    conta->saldo += montante;

    atualizarHistorico(conta, montante, "Dep�sito");
}

//fun��o para levantamento de dinheiro de uma conta
void levantarDinheiro(TipoConta *conta){
    float montante = 0.0;
    int saldoSuficiente;

    printf("Introduza a montante que pretente levantar da conta > ");
    scanf("%f", &montante);

    if(conta->modalidade == normal){
        saldoSuficiente = verificarSaldoConta(conta, montante + 5);

        if(saldoSuficiente == 1){
            conta->saldo -= montante + 5;
            printf("\nMontante levantada com sucesso (%.2f)\n", montante);
        } else printf("\nERRO: SALDO INSUFICIENTE");
    }
    else{
        saldoSuficiente = verificarSaldoConta(conta, montante);
        if(saldoSuficiente == 1){
            conta->saldo -= montante;
            printf("\nMontante levantada com sucesso (%.2f)\n", montante);
        } else printf("\nERRO: SALDO INSUFICIENTE");

    }

    atualizarHistorico(conta, montante, "Levantamento");
}

//fun��o para transfer�ncia de dinheiro numa conta
void transferirDinheiro(TipoConta *contaOrigem, TipoConta *contaDestino){
    float montante = 0.0;
    int saldoSuficiente;

    printf("Introduza a montante que pretente transferir da conta origem > ");
    scanf("%f", &montante);

    if(contaOrigem->modalidade == normal){
        saldoSuficiente = verificarSaldoConta(&contaOrigem, montante + 5);

        if(saldoSuficiente == 1){
            if(montante > 0){
                contaOrigem->saldo -= montante + 5;
                contaDestino->saldo += montante;
                printf("\nMontante transferido com sucesso (%.2f)\n", montante);
            } else printf("O montante tem de ser superior a 0!");
        } else printf("\nERRO: SALDO INSUFICIENTE");
    }
    else{
        saldoSuficiente = verificarSaldoConta(&contaOrigem, montante);

        if(saldoSuficiente == 1){
            contaOrigem->saldo -= montante;
            contaDestino->saldo += montante;
            printf("\nMontante levantada com sucesso (%.2f)\n", montante);
        } else printf("\nERRO: SALDO INSUFICIENTE");

    }

    atualizarHistorico(contaOrigem, montante, "Envio de dinheiro por transfer�ncia");
    atualizarHistorico(contaDestino, montante, "Rece��o de dinheiro por transfer�ncia");
}

//fun��o para atualiza��o do hist�rico
void atualizarHistorico(TipoConta *conta, float valor, char descricao[101]){
    strcpy(conta->historico[2].descricao, conta->historico[1].descricao);
    conta->historico[2].valor = conta->historico[1].valor;

    strcpy(conta->historico[1].descricao, conta->historico[0].descricao);
    conta->historico[1].valor = conta->historico[0].valor;

    strcpy(conta->historico[0].descricao, descricao);
    conta->historico[0].valor = valor;
}
