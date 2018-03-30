#include <stdio.h>
#include <stdint.h>

/*
4) Crie um sistema de vendas de ferramentas que tenha as seguintes
funcionalidades:
- Controle de ferramentas (codigo, descricao, valor) – incluir, excluir listar;
- Controle de clientes (codigo, nome, sobrenome, cpf, rg) – incluir, excluir,
listar
- Controle de vendas (codigo, codigoferramenta, codigocliente, valor) –
realizar vendas, consultar relatório de vendas por cliente, consultar
relatório de vendas em ordem crescente por valor
- O sistema deve armazenar os dados em disco
*/

#include "exerc_pto.h"



/**
 * Insert element into linked list.
 * @param  toinsert [description]
 * @param  head     [description]
 * @return          NULL if unable to insert element
 */
base_t * insert(base_t * head, uint8_t size)
{
  base_t * elem;
  while(elem->)
};


union foobaz fb= { .f.x=1 };
struct foo *ptr = (struct foo*)&fb;

int main(void)
{
  printf("%d\n",sizeof(union foobaz));
  printf("%d\n",ptr->x);
  /*
  while(1)
  {

  }*/
  return 0;
}
