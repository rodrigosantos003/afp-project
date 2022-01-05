/*
    @name: Banco Alves dos Reis
    @description: Porgrama de gest�o banc�ria
    @authors: Jo�o Fernandes & Rodrigo Santos
    @last_modified: 2021-01-05
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "conta.h"

#define MAX_CONTAS 100

void mostrarMenu(void);
void operacoesMenu(int opcao, TipoConta contas[], int numAtualContas);

int main()
{
    setlocale(LC_ALL, "");

    //declara��o de vari�veis
    TipoConta contas[MAX_CONTAS];
    int numAtualContas, opcaoMenu;

    //inicializa��o das vari�veis inteiras a zero
    opcaoMenu = numAtualContas = 0;

    //chamada das fun��es mostrarMenu() e operacoesMenu()
    mostrarMenu();
    operacoesMenu(opcaoMenu, contas, numAtualContas);

    return 0;
}

//fun��o que apresenta o menu
void mostrarMenu()
{
    printf("BANCO ALVES DOS REIS\n");

    printf("1. Abrir uma conta\n");
    printf("2. Listar contas existentes\n");
    printf("3. Consultar detalhes de uma conta\n");
    printf("4. Depositar dinheiro numa conta\n");
    printf("5. Levantar dinheiro de uma conta\n");
    printf("6. Transferir dinheiro entre contas\n");
    printf("7. Editar a informa��o de uma conta\n");
    printf("8. Eliminar uma conta\n");
    printf("9. Gravar listagem de contas para um ficheiro de texto\n\n");
    printf("10. Sair do programa\n");
}

//fun��o que executa as opera��es do menu (dada a respetiva op��o)
void operacoesMenu(int opcao, TipoConta contas[], int numAtualContas){
    char listagem, sair;
    int contaOrigem, contaDestino;

    contaOrigem = contaDestino = 0;

    //leitura da op��o do menu
    printf("Escolha uma opc�o do menu: ");
    scanf("%d", &opcao);
    fflush(stdin);

    //verifica��o da op��o e execu��o das respetivas opera��es
    switch(opcao){
        case 1: /*abertura de conta*/
            if(numAtualContas < MAX_CONTAS){
                abrirConta(&contas[numAtualContas], numAtualContas);
                numAtualContas++;
            }
            else
                printf("\nERRO: N�o � poss�vel abrir mais contas!\n");

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 2: /*listagem de todas as contas*/
            printf("Listar todas as contas registadas (T) ou contas de um determinado cliente (C)? ");
            scanf("%c", &listagem);

            if(listagem == 'T' || listagem == 't')
                listarTodasContas(contas, numAtualContas);
            else if(listagem == 'C' || listagem == 'c')
                listarContasCliente(contas, numAtualContas);
            else
                printf("ERRO: Op��o inv�lida!");

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 3: /*consulta dos detalhes de uma conta*/
            do{
                contaOrigem = lerNumConta(contas, numAtualContas);
            }while(contaOrigem == -1);

            imprimirConta(contas[2-1]);

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 4: /*dep�sito de dinheiro*/
            do{
                contaOrigem = lerNumConta(contas, numAtualContas);
            }while(contaOrigem == -1);

            depositarDinheiro(&contas[contaOrigem]);

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 5: /*levantamento de dinheiro*/
            do{
                contaOrigem = lerNumConta(contas, numAtualContas);
            }while(contaOrigem == -1);

            levantarDinheiro(&contas[contaOrigem]);

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 6: /*transfer�ncia de dinheiro*/
            do{
                contaOrigem = lerNumConta(contas, numAtualContas);
                contaDestino = lerNumConta(contas, numAtualContas);
            }while(contaOrigem == -1 || contaDestino == -1);

            transferirDinheiro(&contas[contaOrigem], &contas[contaDestino]);

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 7: /*edi��o de informa��es de conta*/
            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 8: /*elimina��o de conta*/
            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 9: /*elimina��o de conta*/
            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 10: /*sa�da do programa*/
            printf("Deseja sair do programa (S/N)? ");
            scanf("%c", &sair);

            if(sair == 's' || sair == 'S')
                exit(0);
            else if(sair == 'n' || sair == 'N'){
                mostrarMenu();
                operacoesMenu(opcao, contas, numAtualContas);
            }
            else{
                printf("\nERRO: Resposta inv�lida!\n");
                mostrarMenu();
                operacoesMenu(opcao, contas, numAtualContas);
            }
            break;
        default: /*op��o do menu n�o existente*/
            printf("\nERRO: A op��o escolhida n�o existe!\n");
            operacoesMenu(opcao, contas, numAtualContas);
    }
}
