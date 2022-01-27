#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "conta.h"
#include "gestao.h"
#include "movimentacoes.h"

//fun��o para c�lculo do total de fundos
float totalFundos(TipoConta contas[], int numAtualContas)
{
    float total = 0.0F;

    //soma dos saldos de todas as contas
    for(int i = 0; i < numAtualContas; i++)
    {
        total += contas[i].saldo;
    }

    //retorna a soma dos saldos
    return total;
}

//fun��o para listar todas as contas registadas
void listarTodasContas(TipoConta contas[], int numAtualContas)
{
    //itera��o para escrita de todas as contas existentes
    for(int i = 0; i < numAtualContas; i++)
    {
        imprimirConta(contas[i]);
        printf("\n");
    }
}

//fun��o para listar todas as contas de um determinado cliente
void listarContasCliente(TipoConta contas[], int numAtualContas)
{
    int nif;

    //leitura do NIF do cliente
    printf("NIF a consultar > ");
    scanf("%d", &nif);
    fflush(stdin);

    //itera��o para percorrer todas as contas
    for(int i = 0; i < numAtualContas; i++)
    {
        //itera��o para percorrer os titulares da cintas
        for(int x = 0; x < contas[i].totalTitulares; x++)
        {
            //se o NIF do titular for igual ao NIF introduzido, s�o escritos os detalhes da conta
            if(contas[i].titulares[x].nif == nif)
            {
                imprimirConta(contas[i]);
                printf("\n");
            }
        }
    }
}

//fun��o para aprova��o de transa��es
int aprovarTransacao(TipoConta *conta)
{
    char nome[101];
    int nif, numTitulares;

    //leitura das respostas �s perguntas de seguran�a
    printf("Qual o nome do 1� titular da conta? ");
    gets(nome);
    fflush(stdin);

    printf("Qual � o seu NIF? ");
    scanf("%d", &nif);
    fflush(stdin);

    printf("Quantos titulares tem a conta? ");
    scanf("%d", &numTitulares);
    fflush(stdin);

    //valida��o das respostas
    if(strcmp(nome, conta->titulares[0].nome) == 0)
    {
        if(numTitulares == conta->totalTitulares)
        {
            for(int i = 0; i < conta->totalTitulares; i++)
            {
                if(nif == conta->titulares[i].nif)
                {
                    //se as respostas estiverem todas corretas, � retornado "sucesso" (i.e 1)
                    return 1;
                }
            }
        }
    }

    return -1;
}

//fun��o para guardar contas num ficheiro de texto
void guardarContas(TipoConta contas[], int numAtualContas)
{
    FILE *ficheiroContas;

    ficheiroContas = fopen("contas.txt", "w");

    if(ficheiroContas == NULL)
    {
        printf("\nERRO: Ocorreu um erro ao abrir o ficheiro!\n");
        exit(1);
    }

    //escrita dos dados no ficheiro
    for(int i = 0; i < numAtualContas; i++)
    {
        fprintf(ficheiroContas, "----------------\n");

        fprintf(ficheiroContas, "N�mero: %d\n", contas[i].numero);

        fprintf(ficheiroContas, "TITULARES:\n");
        for(int j = 0; j < contas[i].totalTitulares; j++)
        {
            fprintf(ficheiroContas, "\t%d ", j+1);
            fprintf(ficheiroContas, "| Nome: %-25s ", contas[i].titulares[j].nome);
            fprintf(ficheiroContas, "| NIF: %d\n", contas[i].titulares[j].nif);
        }

        if(contas[i].modalidade == normal)
            fprintf(ficheiroContas, "Modalidade: Normal\n");
        else
            fprintf(ficheiroContas, "Modalidade: Isenta\n");

        fprintf(ficheiroContas, "Saldo: %.2f EUR\n", contas[i].saldo);

        fprintf(ficheiroContas, "HIST�RICO:\n");
        for(int x = 0; x < 3; x++)
        {
            fprintf(ficheiroContas, "\tDescri��o: %-25s ", contas[i].historico[x].descricao);
            fprintf(ficheiroContas, "| Valor: %.2f\n", contas[i].historico[x].valor);
        }
        fprintf(ficheiroContas, "Data de abertura: %02d/%02d/%4d\n", contas[i].data.dia, contas[i].data.mes, contas[i].data.ano);

        fprintf(ficheiroContas, "----------------\n");
    }

    fclose(ficheiroContas);

    printf("Contas guardadas com sucesso!\n\n");
}

//fun��o para eliminar todos os dados
void eliminarDados(TipoConta *contas[], int *numAtualContas)
{
    FILE *ficheiroContas;

    for(int i = 0; i < *numAtualContas; i++)
    {
        if(contas[i]->saldo > 0)
        {
            //se existirem ontas com saldo superior a zero a fun��o � terminada
            printf("\nERRO: Existem contas com saldo maior que 0!\n\n");
            return;
        }
    }

    ficheiroContas = fopen("contas.txt", "w");

    if(ficheiroContas == NULL)
    {
        printf("\nERRO: Ocorreu um erro ao abrir o ficheiro!\n");
        exit(1);
    }

    //apagar dados do ficheiro
    fprintf(ficheiroContas, "%s", "");

    //eliminar contas do array
    memset(contas, 0, 100*sizeof(TipoConta));
    numAtualContas = 0;

    fclose(ficheiroContas);

    printf("\nDados eliminados com sucesso!\n");
}
