#ifndef GESTAO_H_INCLUDED
#define GESTAO_H_INCLUDED

//prot�tipos de fun��es
float totalFundos(TipoConta contas[], int numAtualContas);
void guardarContas(TipoConta contas[], int numAtualContas);
void listarTodasContas(TipoConta contas[], int numAtualContas);
void listarContasCliente(TipoConta contas[], int numAtualContas);
int aprovarTransacao(TipoConta *conta);

#endif // GESTAO_H_INCLUDED
