#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "conta.h"

//fun��o para leitura do n�mero de conta e verifica��o da sua exist�ncia
int lerNumConta(TipoConta contas[], int numAtualContas){
    int numConta = 0;

    //leitura do n�mero de conta
    printf("Introduza o n�mero de conta: ");
    scanf("%d", &numConta);
    fflush(stdin);

    //itera��o para verifica��o da exist�ncia da conta
    for(int i = 0; i < numAtualContas; i++){
        //se a conta existir � retornada a sua posi��o no array
        if(contas[i].numero == numConta)
            return i;
        //sen�o � escrito no ecr� que a conta n�o existe e � um erro
        else{
            printf("\nERRO: A conta n�o existe!\n");
        }
    }

    return -1;
}

//fun��o para abertura de conta
void abrirConta(TipoConta *conta, int numAtualContas){
    int num, quantidadeDigitos;
    num = quantidadeDigitos = 0;

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t); /*retorna os valores da data local*/

    printf("INTRODUZA OS DADOS DA CONTA:\n");

    //atribui��o do n�mero de conta
    conta->numero = numAtualContas + 1;

    //leitura do n�mero de titulares
    do{
        printf("N� de titulares > ");
        scanf("%d", &conta->totalTitulares);

        if(conta->totalTitulares > 5)
            printf("\nERRO: A conta deve ter at� 5 titulares!");
        else if(conta->totalTitulares < 0)
            printf("\nERRO: O n�mero de titulares deve ser um n�mero positivo");
    }while(conta->totalTitulares > 5 || conta->titulares < 0);
    fflush(stdin);

    //leitura dos dados dos titulares
    for(int i = 0; i < conta->totalTitulares; i++){
        printf("TITULAR %d\n", i+1);

        do{
            printf("NIF > ");
            scanf("%d", &conta->titulares[i].nif);

            num = conta->titulares[i].nif;
            quantidadeDigitos = 0;
            do {
                num /= 10;
                quantidadeDigitos++;
            }while (num != 0);

            if(quantidadeDigitos != 9)
                printf("\nERRO: O NIF deve ter 9 d�gitos!\n");
        }while(quantidadeDigitos != 9);


        getchar();

        printf("Nome > ");
        gets(conta->titulares[i].nome);
    }
    fflush(stdin);

    //leitura da modalidade
    do{
        printf("Modalidade da Conta (Normal:0 / Isenta:1) > ");
        scanf("%u", &conta->modalidade);

        if(conta->modalidade != 0 || conta->modalidade != 1)
            printf("\nERRO: A modalidade deve ser 0 ou 1, Normal ou Isenta resptivamnete!\n");
    }while(conta->modalidade != 0 || conta->modalidade != 1);
    fflush(stdin);

    //leitura do saldo inicial
    do{
        printf("Saldo > ");
        scanf("%f", &conta->saldo);

        if(conta->saldo < 150)
            printf("\nERRO: O saldo inicial deve ser igual ou superior a 150 EUR!\n");
    } while(conta->saldo < 150);
    fflush(stdin);

    //atribui��o da data de abertura (atrav�s da data local)
    conta->data.dia = tm.tm_mday;
    conta->data.mes = tm.tm_mon+1;
    conta->data.ano = tm.tm_year+1900;
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

//fun��o para listar todas as contas registadads
void listarTodasContas(TipoConta contas[], int numAtualContas){
    //itera��o para escrita de todas as contas existentes
    for(int i = 0; i < numAtualContas; i++){
        imprimirConta(contas[i]);
        printf("\n");
    }
}

//fun��o para listar todas as contas de um determinado cliente
void listarContasCliente(TipoConta contas[], int numAtualContas){
    int nif;

    //leitura do NIF do cliente
    printf("NIF a consultar > ");
    scanf("%d", &nif);
    fflush(stdin);

    //itera��o para percorrer todas as contas
    for(int i = 0; i < numAtualContas; i++){
        //itera��o para percorrer os titulares da cintas
        for(int x = 0; x < contas[i].totalTitulares; x++){
            //se o NIF do titular for igual ao NIF introduzido, s�o escritos os detalhes da conta
            if(contas[i].titulares[x].nif == nif){
                imprimirConta(contas[i]);
                printf("\n");
            }
        }
    }
}

//fun��o para verifica��o de saldo suficiente
int verificarSaldoConta(TipoConta *conta, float montante){
    //se o saldo for superior ao montante recebido � retornado 1 (i.e verdadeiro)
    if(conta->saldo > montante)
        return 1;
    //sen�o � retornado 0 (i.e falso)
    return 0;
}

//fun��o para dep�sito de dinheiro numa conta
void depositarDinheiro(TipoConta *conta){
    float montante = 0.0F;

    //leitura do montante a depositar
    do{
        printf("Montante a depositar > ");
        scanf("%f", &montante);

        if(montante <= 0)
            printf("ERRO: O montante deve ser superior a 0!");
    }while(montante <= 0);
    fflush(stdin);

    //introdu��o do montante no saldo da conta
    conta->saldo += montante;
    printf("\nMontante depositado com sucesso (%.2f EUR)!\n", montante);

    //chamada da fun��o atualizarHistorico() para atualiza��o do hist�rico de movimentos
    atualizarHistorico(conta, montante, "Dep�sito");
}

//fun��o para levantamento de dinheiro de uma conta
void levantarDinheiro(TipoConta *conta){
    float montante = 0.0F;
    int saldoSuficiente = 0;

    //leitura do montante a levantar
    do{
        printf("Montante a levantar > ");
        scanf("%f", &montante);

        if(montante <= 0)
            printf("\nERRO: O montante deve ser superior a 0!");
    }while(montante <= 0);
    fflush(stdin);

    //verifica��o da modalidade da conta, verifica��o de saldo suficiente e realiza��o da opera��o
    if(conta->modalidade == normal){
        saldoSuficiente = verificarSaldoConta(conta, montante + 5);

        if(saldoSuficiente == 1){
            conta->saldo -= montante + 5;
            printf("\nMontante levantada com sucesso (%.2f EUR)!\n", montante);
        } else printf("\nERRO: Saldo insuficiente!");
    }
    else{
        saldoSuficiente = verificarSaldoConta(conta, montante);

        if(saldoSuficiente == 1){
            conta->saldo -= montante;
            printf("\nMontante levantada com sucesso (%.2f EUR)!\n", montante);
        } else printf("\nERRO: Saldo insuficiente!");

    }

    //chamada da fun��o atualizarHistorico() para atualiza��o do hist�rico de movimentos
    atualizarHistorico(conta, montante, "Levantamento");
}

//fun��o para transfer�ncia de dinheiro numa conta
void transferirDinheiro(TipoConta *contaOrigem, TipoConta *contaDestino){
    float montante = 0.0F;
    int saldoSuficiente = 0;

    //leitura do montante a transferir
    do{
        printf("Montante a transferir > ");
        scanf("%f", &montante);

        if(montante <= 0)
            printf("\nERRO: O montante deve ser superior a 0!");
    }while(montante <= 0);
    fflush(stdin);

    //verifica��o da modalidade da conta, verifica��o de saldo suficiente e realiza��o da opera��o
    if(contaOrigem->modalidade == normal){
        saldoSuficiente = verificarSaldoConta(contaOrigem, montante + 5);

        if(saldoSuficiente == 1){
            contaOrigem->saldo -= montante + 5;
            contaDestino->saldo += montante;
            printf("\nMontante transferido com sucesso (%.2f EUR)!\n", montante);
        }
        else
            printf("\nERRO: Saldo insuficiente!");
    }
    else{
        saldoSuficiente = verificarSaldoConta(contaOrigem, montante);

        if(saldoSuficiente == 1){
            contaOrigem->saldo -= montante;
            contaDestino->saldo += montante;
            printf("\nMontante levantada com sucesso (%.2f EUR)\n", montante);
        } else printf("\nERRO: Saldo insuficiente!");

    }

    //chamada da fun��o atualizarHistorico() para atualiza��o do hist�rico de movimentos
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
