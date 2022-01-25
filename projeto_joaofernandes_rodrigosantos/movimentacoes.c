#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "conta.h"
#include "gestao.h"
#include "movimentacoes.h"

//fun��o para verifica��o de saldo suficiente
int verificarSaldoConta(TipoConta *conta, float montante)
{
    //se o saldo for superior ao montante recebido � retornado 1 (i.e verdadeiro)
    if(conta->saldo >= montante)
        return 1;
    //sen�o � retornado 0 (i.e falso)
    return 0;
}

//fun��o para dep�sito de dinheiro numa conta
void depositarDinheiro(TipoConta *conta)
{
    float montante = 0.0F;

    //leitura do montante a depositar
    do
    {
        printf("Montante a depositar > ");
        scanf("%f", &montante);
        fflush(stdin);

        if(montante <= 0)
            printf("\nERRO: O montante deve ser superior a 0!\n");
    }
    while(montante <= 0);

    //introdu��o do montante no saldo da conta
    conta->saldo += montante;
    printf("\nMontante depositado com sucesso (%.2f EUR)!\n", montante);

    //chamada da fun��o atualizarHistorico() para atualiza��o do hist�rico de movimentos
    atualizarHistorico(conta, montante, "Dep�sito");
}

//fun��o para levantamento de dinheiro de uma conta
void levantarDinheiro(TipoConta *conta)
{
    float montante = 0.0F;
    int saldoSuficiente = 0;
    int aprovacao;

    //leitura do montante a levantar
    do
    {
        printf("Montante a levantar > ");
        scanf("%f", &montante);
        fflush(stdin);

        if(montante <= 0)
            printf("\nERRO: O montante deve ser superior a 0!\n");
    }
    while(montante <= 0);

    if(montante >= 400)
    {
        printf("\nAVISO: O montante indicado � considerado um movimento suspeito!\n");
        printf("Iremos proceder a perguntas de seguran�a!\n");

        aprovacao = aprovarTransacao(conta);
    }
    else
        aprovacao = 1;


    if(aprovacao == 1)
    {
        //verifica��o da modalidade da conta, verifica��o de saldo suficiente e realiza��o da opera��o
        if(conta->modalidade == normal)
        {
            saldoSuficiente = verificarSaldoConta(conta, montante + 5);

            if(saldoSuficiente == 1)
            {
                conta->saldo -= montante + 5;
                printf("\nMontante levantada com sucesso (%.2f EUR)!\n", montante);

                //chamada da fun��o atualizarHistorico() para atualiza��o do hist�rico de movimentos
                atualizarHistorico(conta, montante, "Levantamento");
            }
            else printf("\nERRO: Saldo insuficiente!\n");
        }
        else
        {
            saldoSuficiente = verificarSaldoConta(conta, montante);

            if(saldoSuficiente == 1)
            {
                conta->saldo -= montante;
                printf("\nMontante levantada com sucesso (%.2f EUR)!\n", montante);

                //chamada da fun��o atualizarHistorico() para atualiza��o do hist�rico de movimentos
                atualizarHistorico(conta, montante, "Levantamento");
            }
            else printf("\nERRO: Saldo insuficiente!\n");

        }
    }
    else
        printf("\nERRO: A aprova��o da transa��o falhou!\n");

}

//fun��o para transfer�ncia de dinheiro entre contas
void transferirDinheiro(TipoConta *contaOrigem, TipoConta *contaDestino)
{
    float montante = 0.0F;
    int saldoSuficiente = 0;
    int aprovacao;

    //leitura do montante a transferir
    do
    {
        printf("Montante a transferir > ");
        scanf("%f", &montante);
        fflush(stdin);

        if(montante <= 0)
            printf("\nERRO: O montante deve ser superior a 0!\n");
    }
    while(montante <= 0);

    if(montante >= 400)
    {
        printf("\nAVISO: O montante indicado � consideraddo um movimento suspeito.\n");
        printf("Iremos proceder a perguntas de seguran�a!\n");

        aprovacao = aprovarTransacao(contaOrigem);
    }
    else
        aprovacao = 1;

    if(aprovacao == 1)
    {
        //verifica��o da modalidade da conta, verifica��o de saldo suficiente e realiza��o da opera��o
        if(contaOrigem->modalidade == normal)
        {
            saldoSuficiente = verificarSaldoConta(contaOrigem, montante + 5);

            if(saldoSuficiente == 1)
            {
                contaOrigem->saldo -= montante + 5;
                contaDestino->saldo += montante;
                printf("\nMontante transferido com sucesso (%.2f EUR)!\n", montante);

                //chamada da fun��o atualizarHistorico() para atualiza��o do hist�rico de movimentos
                atualizarHistorico(contaOrigem, montante, "Envio de dinheiro por transfer�ncia");
                atualizarHistorico(contaDestino, montante, "Rece��o de dinheiro por transfer�ncia");
            }
            else
                printf("\nERRO: Saldo insuficiente!\n");
        }
        else
        {
            saldoSuficiente = verificarSaldoConta(contaOrigem, montante);

            if(saldoSuficiente == 1)
            {
                contaOrigem->saldo -= montante;
                contaDestino->saldo += montante;
                printf("\nMontante transferido com sucesso (%.2f EUR)!\n", montante);

                //chamada da fun��o atualizarHistorico() para atualiza��o do hist�rico de movimentos
                atualizarHistorico(contaOrigem, montante, "Envio de dinheiro por transfer�ncia");
                atualizarHistorico(contaDestino, montante, "Rece��o de dinheiro por transfer�ncia");
            }
            else
                printf("\nERRO: Saldo insuficiente!\n");
        }
    }
    else
        printf("\nERRO: A aprova��o falhou!\n");
}

//fun��o para atualiza��o do hist�rico
void atualizarHistorico(TipoConta *conta, float valor, char descricao[101])
{
    strcpy(conta->historico[2].descricao, conta->historico[1].descricao);
    conta->historico[2].valor = conta->historico[1].valor;

    strcpy(conta->historico[1].descricao, conta->historico[0].descricao);
    conta->historico[1].valor = conta->historico[0].valor;

    strcpy(conta->historico[0].descricao, descricao);
    conta->historico[0].valor = valor;
}
