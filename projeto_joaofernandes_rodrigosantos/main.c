/*
    @name: Banco Alves dos Reis
    @description: Porgrama de gest�o banc�ria
    @authors: Jo�o Fernandes & Rodrigo Santos
    @last_modified: 2022-01-19
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "conta.h"
#include "gestao.h"
#include "movimentacoes.h"

#define MAX_CONTAS 100

void mostrarMenu(int numAtualContas, float totalFundos);
void operacoesMenu(TipoConta contas[], int numAtualContas);

int main()
{
    setlocale(LC_ALL, "");

    //declara��o de vari�veis
    TipoConta contas[MAX_CONTAS];
    int numAtualContas;

    //inicializa��o das vari�veis inteiras a zero
    numAtualContas = 0;

    system("title BANCO ALVES DOS REIS");

    //chamada das fun��es mostrarMenu() e operacoesMenu()
    mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
    operacoesMenu(contas, numAtualContas);

    return 0;
}

//fun��o que apresenta o menu
void mostrarMenu(int numAtualContas, float totalFundos)
{
    system("cls");

    printf("BANCO ALVES DOS REIS\n\n");
    printf("Existem %d contas ativas e um total de %.2f EUR em fundos\n\n", numAtualContas, totalFundos);

    printf("1. Abrir uma conta\n");
    printf("2. Listar contas existentes\n");
    printf("3. Consultar detalhes de uma conta\n");
    printf("4. Depositar dinheiro numa conta\n");
    printf("5. Levantar dinheiro de uma conta\n");
    printf("6. Transferir dinheiro entre contas\n");
    printf("7. Editar a informa��o de uma conta\n");
    printf("8. Eliminar uma conta\n");
    printf("9. Gravar listagem de contas para um ficheiro de texto\n");
    printf("10. Sair do programa\n");
}

//fun��o que executa as opera��es do menu (dada a respetiva op��o)
void operacoesMenu(TipoConta contas[], int numAtualContas)
{
    char listagem, sair;
    int opcao, contaOrigem, contaDestino;

    opcao = contaOrigem = contaDestino = 0;

    //leitura da op��o do menu
    printf("Escolha uma opc�o do menu: ");
    scanf("%d", &opcao);
    fflush(stdin);

    //verifica��o da op��o e execu��o das respetivas opera��es
    switch(opcao)
    {

    case 1: /*abertura de conta*/
        if(numAtualContas < MAX_CONTAS)
        {
            abrirConta(&contas[numAtualContas], numAtualContas);
            numAtualContas++;
        }
        else
            printf("\nERRO: N�o � poss�vel abrir mais contas!\n");

        system("pause");

        mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
        operacoesMenu(contas, numAtualContas);
        break;
    case 2: /*listagem de todas as contas*/
        printf("Listar todas as contas registadas (T) ou contas de um determinado cliente (C)? ");
        scanf("%c", &listagem);
        fflush(stdin);

        if(listagem == 'T' || listagem == 't')
            listarTodasContas(contas, numAtualContas);
        else if(listagem == 'C' || listagem == 'c')
            listarContasCliente(contas, numAtualContas);
        else
            printf("ERRO: Op��o inv�lida!");

        system("pause");

        mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
        operacoesMenu(contas, numAtualContas);
        break;
    case 3: /*consulta dos detalhes de uma conta*/
        contaOrigem = lerNumConta(contas, numAtualContas);

        if(contaOrigem != -1)
            imprimirConta(contas[contaOrigem]);

        system("pause");

        mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
        operacoesMenu(contas, numAtualContas);
        break;
    case 4: /*dep�sito de dinheiro*/
        contaOrigem = lerNumConta(contas, numAtualContas);

        if(contaOrigem != -1)
            depositarDinheiro(&contas[contaOrigem]);

        system("pause");

        mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
        operacoesMenu(contas, numAtualContas);
        break;
    case 5: /*levantamento de dinheiro*/
        contaOrigem = lerNumConta(contas, numAtualContas);

        if(contaOrigem != -1)
            levantarDinheiro(&contas[contaOrigem]);

        system("pause");

        mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
        operacoesMenu(contas, numAtualContas);
        break;
    case 6: /*transfer�ncia de dinheiro*/
        printf("CONTA DE ORIGEM\n");
        contaOrigem = lerNumConta(contas, numAtualContas);

        if(contaOrigem != -1)
        {
            printf("CONTA DE DESTINO\n");
            contaDestino = lerNumConta(contas, numAtualContas);

            transferirDinheiro(&contas[contaOrigem], &contas[contaDestino]);
        }

        system("pause");

        mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
        operacoesMenu(contas, numAtualContas);
        break;
    case 7: /*edi��o de informa��es de conta*/
        contaOrigem = lerNumConta(contas, numAtualContas);

        if(contaOrigem != -1)
            editarDetalhesConta(&contas[contaOrigem]);

        system("pause");

        mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
        operacoesMenu(contas, numAtualContas);
        break;
    case 8: /*elimina��o de conta*/
        contaOrigem = lerNumConta(contas, numAtualContas);

        if(contaOrigem != -1)
        {
            if(contas[contaOrigem].saldo == 0.0)
            {
                eliminarConta(contas, numAtualContas, contaOrigem);
                numAtualContas--;
            }
            else
                printf("\nERRO: O saldo da conta deve estar a 0!\n");
        }

        system("pause");

        mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
        operacoesMenu(contas, numAtualContas);
        break;
    case 9: /*guardar contas em ficheiro*/
        guardarContas(contas, numAtualContas);

        system("pause");

        mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
        operacoesMenu(contas, numAtualContas);
        break;
    case 10: /*sa�da do programa*/
        printf("Deseja sair do programa (S/N)? ");
        scanf("%c", &sair);
        fflush(stdin);

        if(sair == 's' || sair == 'S')
            exit(0);
        else if(sair == 'n' || sair == 'N')
        {
            mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
            operacoesMenu(contas, numAtualContas);
        }
        else
        {
            printf("\nERRO: Resposta inv�lida!\n");

            system("pause");

            mostrarMenu(numAtualContas, totalFundos(contas, numAtualContas));
            operacoesMenu(contas, numAtualContas);
        }
        break;
    default: /*op��o do menu n�o existente*/
        printf("\nERRO: A op��o escolhida n�o existe!\n");
        operacoesMenu(contas, numAtualContas);
    }
}
