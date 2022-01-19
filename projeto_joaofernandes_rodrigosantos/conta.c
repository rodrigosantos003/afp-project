#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#include "conta.h"
#include "gestao.h"
#include "movimentacoes.h"

//fun��o para leitura do n�mero de conta e verifica��o da sua exist�ncia
int lerNumConta(TipoConta contas[], int numAtualContas)
{
    int numConta = 0;

    //leitura do n�mero de conta
    printf("Introduza o n�mero de conta: ");
    scanf("%d", &numConta);
    fflush(stdin);

    //itera��o para verifica��o da exist�ncia da conta
    for(int i = 0; i < numAtualContas; i++)
    {
        //se a conta existir � retornada a sua posi��o no array
        if(contas[i].numero == numConta)
        {
            return i;
        }
    }
    //sen�o � escrito no ecr� que a conta n�o existe e � retornado o valor de "erro" (i.e -1)
    printf("\nERRO:A conta n�o existe!\n");
    return -1;
}

//fun��o para abertura de conta
void abrirConta(TipoConta *conta, int numAtualContas)
{
    int num, quantidadeDigitos;
    num = quantidadeDigitos = 0;

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t); /*retorna os valores da data local*/

    printf("INTRODUZA OS DADOS DA CONTA:\n");

    //atribui��o do n�mero de conta
    conta->numero = numAtualContas + 1;

    //leitura do n�mero de titulares
    do
    {
        printf("N� de titulares > ");
        scanf("%d", &conta->totalTitulares);
        fflush(stdin);

        if(conta->totalTitulares > 5)
            printf("\nERRO: A conta deve ter at� 5 titulares!\n");
        else if(conta->totalTitulares <= 0)
            printf("\nERRO: O n�mero de titulares deve ser maior que 0!\n");
    }
    while(conta->totalTitulares > 5 || conta->totalTitulares <= 0);

    //leitura dos dados dos titulares
    for(int i = 0; i < conta->totalTitulares; i++)
    {
        printf("TITULAR %d\n", i+1);

        do
        {
            printf("NIF > ");
            scanf("%d", &conta->titulares[i].nif);
            fflush(stdin);

            num = conta->titulares[i].nif;
            quantidadeDigitos = 0;
            do
            {
                num /= 10;
                quantidadeDigitos++;
            }
            while (num != 0);

            if(quantidadeDigitos != 9)
                printf("\nERRO: O NIF deve ter 9 d�gitos!\n");
        }
        while(quantidadeDigitos != 9);


        do
        {
            printf("Nome > ");
            gets(conta->titulares[i].nome);
            fflush(stdin);

            if(strcmp(conta->titulares[i].nome, "") == 0)
                printf("\nERRO: O nome deve estar preenchido!\n");
        }
        while(strcmp(conta->titulares[i].nome, "") == 0);

    }

    //leitura da modalidade
    do
    {
        printf("Modalidade da Conta (Normal:0 / Isenta:1) > ");
        scanf("%u", &conta->modalidade);
        fflush(stdin);

        if(conta->modalidade < 0 || conta->modalidade > 1)
            printf("\nERRO: A modalidade deve ser 0 ou 1, Normal ou Isenta respetivamente!\n");
    }
    while(conta->modalidade < 0 || conta->modalidade > 1);


    //leitura do saldo inicial
    do
    {
        printf("Saldo > ");
        scanf("%f", &conta->saldo);
        fflush(stdin);

        if(conta->saldo < 150)
            printf("\nERRO: O saldo inicial deve ser igual ou superior a 150 EUR!\n");
    }
    while(conta->saldo < 150);


    //atribui��o da data de abertura (atrav�s da data local)
    conta->data.dia = tm.tm_mday;
    conta->data.mes = tm.tm_mon+1;
    conta->data.ano = tm.tm_year+1900;
}

//fun��o para escrever os detalhes de uma conta
void imprimirConta(TipoConta conta)
{
    printf("----------------\n");

    printf("N�mero: %d\n", conta.numero);

    printf("TITULARES:\n");
    for(int i = 0; i < conta.totalTitulares; i++)
    {
        printf("\t%d ", i+1);
        printf("| Nome: %-25s ", conta.titulares[i].nome);
        printf("| NIF: %d\n", conta.titulares[i].nif);
    }

    if(conta.modalidade == normal)
        printf("Modalidade: Normal\n");
    else
        printf("Modalidade: Isenta\n");

    printf("Saldo: %.2f EUR \n", conta.saldo);

    printf("HIST�RICO (�ltimos 3 movimentos):\n");
    for(int i = 0; i < 3; i++)
    {
        printf("\tDescri��o: %-25s | ", conta.historico[i].descricao);
        printf("Valor: %.2f\n", conta.historico[i].valor);
    }

    printf("Data de abertura: %02d/%02d/%4d\n", conta.data.dia, conta.data.mes, conta.data.ano);

    printf("----------------\n");
}


//fun��o para edi��o dos detalhes da conta
void editarDetalhesConta(TipoConta *conta)
{
    char resposta;
    int numTitulares, num, quantidadeDigitos;

    numTitulares = num = quantidadeDigitos = 0;

    printf("Pretende alterar o tipo de conta? (S/N) ");
    scanf("%c", &resposta);
    fflush(stdin);

    if(resposta == 'S' || resposta == 's')
    {
        do
        {
            printf("Novo tipo de conta (Normal:0 / Isenta:1) > ");
            scanf("%u", &conta->modalidade);
            fflush(stdin);

            if(conta->modalidade < 0 || conta->modalidade > 1)
                printf("\nERRO: A modalidade deve ser 0 ou 1, Normal ou Isenta respetivamente!\n");
        }
        while(conta->modalidade < 0 || conta->modalidade > 1);
    }

    printf("Pretende adicionar titulares? (S/N) ");
    scanf("%c", &resposta);
    fflush(stdin);

    if(resposta == 'S' || resposta == 's')
    {
        printf("N� de titulares a adicionar > ");
        scanf("%d", &numTitulares);
        fflush(stdin);

        if(conta->totalTitulares + numTitulares <= 5)
        {
            for(int i = conta->totalTitulares; i < conta->totalTitulares + numTitulares; i++)
            {
                printf("TITULAR %d\n", i+1);

                do
                {
                    printf("NIF > ");
                    scanf("%d", &conta->titulares[i].nif);
                    fflush(stdin);

                    num = conta->titulares[i].nif;
                    quantidadeDigitos = 0;
                    do
                    {
                        num /= 10;
                        quantidadeDigitos++;
                    }
                    while (num != 0);

                    if(quantidadeDigitos != 9)
                        printf("\nERRO: O NIF deve ter 9 d�gitos!\n");
                }
                while(quantidadeDigitos != 9);

                printf("Nome > ");
                gets(conta->titulares[i].nome);
                fflush(stdin);
            }

            conta->totalTitulares += numTitulares;
        }
        else
            printf("\nERRO: O n�mero de titulares ultrapassa o limite!\n");
    }
}

void eliminarConta(TipoConta contas[], int numAtualContas, int indiceApagar)
{
    for(int i = indiceApagar; i < numAtualContas; i++)
    {
        contas[i] = contas[i+1];
    }

    printf("\nConta eliminada com sucesso!\n");
}
