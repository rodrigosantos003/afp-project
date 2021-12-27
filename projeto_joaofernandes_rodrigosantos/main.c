/*
    @name: Banco Alves dos Reis
    @description: Porgrama de gest�o banc�ria
    @authors: Jo�o Fernandes & Rodrigo Santos
    @last_modified: 2021-12-27
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "conta.h"

#define MAX_CONTAS 100

void menu(int opcao, TipoConta contas[], int numAtualContas);
void gravarListagemContas();

int main()
{
    setlocale(LC_ALL, "");

    //declara��o e vari�veis
    TipoConta contas[MAX_CONTAS];
    int numAtualContas, opcaoMenu;

    opcaoMenu = 0;
    numAtualContas = 0;

    printf("BANCO ALVES DOS REIS\n");
    menu(opcaoMenu, contas, numAtualContas);

    return 0;
}

//fun��o que apresenta o menu
void menu(int opcao, TipoConta contas[], int numAtualContas){
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

    printf("Escolha uma opc�o do menu: ");
    scanf("%d", &opcao);

    fflush(stdin);

    switch(opcao){
        case 1:
            abrirConta(&contas[numAtualContas]);
            numAtualContas++;
            menu(opcao, contas, numAtualContas);
            break;
        case 2:
            for(int i = 0; i < numAtualContas; i++){
                imprimirConta(contas[i]);
                printf("\n");
            }

            menu(opcao, contas, numAtualContas);
            break;
        case 3:
            menu(opcao, contas, numAtualContas);
            break;
        case 4:
            break;
        case 5:
            menu(opcao, contas, numAtualContas);
            break;
        case 6:
            menu(opcao, contas, numAtualContas);
            break;
        case 7:
            menu(opcao, contas, numAtualContas);
            break;
        case 8:
            menu(opcao, contas, numAtualContas);
            break;
        case 9:
            menu(opcao, contas, numAtualContas);
            break;
        case 10:
            exit(0);
            break;
    }
}

