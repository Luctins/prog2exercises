#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

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
#define DEBUG

#include "exerc_pto.h"

client_t  client_head = { .next=NULL};
tool_t   tool_head   = { .next=NULL };
sale_c_t  sale_c_head = { .next=NULL };

client_t  *tmp_client;
tool_t    *tmp_tool;
sale_c_t  *tmp_sale_c;

unsigned int _opt[4] = {0,0,0,0};


int main(void)
{
  puts("Hello, initializing\n last_compiled:"__DATE__);
  while (1)
  {
    printf("which functionalities do you want to access?\n");
    for(uint8_t i=0;menu_opt[i][0][0];i++)
    {
      for(uint8_t j=0;menu_opt[i][j][0];j++)
      {
        printf("* %s [%u]\n",menu_opt[i][j],j);
      }
      //fflush(stdout);
      scanf("%u",&_opt[i]);
      if(_opt[i]==SYNC){break;}
    }
    #ifdef DEBUG
    printf("%u %u\n",_opt[0],_opt[1]);
    #endif

    switch (_opt[0])
    {
      case TOOL:

      break;
      case CLIENT:
        switch(_opt[1])
        {
          case ADD:
            tmp_client=malloc(sizeof(generic_t));
            if(tmp_client==NULL)
            {
              ERR("mem");
              break;
            }
            insert((generic_t *)&client_head,(generic_t *)tmp_client);
            puts("insert the client data\n");
            puts("name:%s");
            scanf("%s\n",tmp_client->name);
            puts("surname:%s");
            scanf("%s\n",tmp_client->surname);
            puts("id_code:%u");
            scanf("%u", &tmp_client->id_code);
            puts("cpf:"CPF_FMT);
            scanf(CPF_FMT,CPF_ARGS(&tmp_client->cpf));
            puts("rg"RG_FMT);
            scanf(RG_FMT,RG_ARGS(&tmp_client->rg));
          break;
          case LIST:
            LIST_ITER(client_head,tmp_client, CLIENT_FMT,CLIENT_ARGS(tmp_client));
          break;
          case DELETE:
            puts("insert client id to delete");
            uint32_t tofindcode;
            scanf("%u",&tofindcode);
            tmp_client=(client_t *)find((generic_t *)&client_head,tofindcode);
            if(tmp_client)
            {
              printf("deleting\n\t "CLIENT_FMT,CLIENT_ARGS(tmp_client));
              delete((generic_t *)&client_head,(generic_t *)tmp_client);
              puts("done.\n");
            }
            else
            {
              ERR("no such client");
            }
          break;
          default:
              ERR("invalid opt");
          break;
        }
      break;
      #if 0
      case SALES:
        switch(_opt[1])
        {
          case ADD:
            tmp_sale_c=malloc(sizeof(generic_t));
            if(tmp_sale_c==NULL)
            {
              ERR("mem");
              break;
            }
            insert((generic_t *)&sales_c_head,(generic_t *)tmp_sales_c);
            puts("insert the sale info\n");
            puts("id_code:%s");
            scanf("%s\n",tmp_sales_c->name);
            puts("surname:%s");
            scanf("%s\n",tmp_sales_c->surname);
            puts("id_code:%u");
            scanf("%u", &tmp_sales_c->id_code);
            puts("cpf:"CPF_FMT);
            scanf(CPF_FMT,CPF_ARGS(tmp_sales_c->cpf));
            puts("rg"RG_FMT);
            scanf(RG_FMT,RG_ARGS(tmp_sales_c->rg));
          break;
          case LIST:
            LIST_ITER(client_head,tmp_client,\
              "id_code:%u",\
          break;
          case DELETE:
            /*TODO use find to find item to delete by id code*/
            puts("insert client id to delete");
            uint32_t tofindcode;
            scanf("%u",&tofindcode);
            tmp_client=(client_t *)find((generic_t *)&client_head,tofindcode);
            if(tmp_client)
            {
              printf("deleting\n\tname:%s surname:%s id_code:%u cpf:"CPF_FMT"rg"RG_FMT,\
              tmp_client->name,tmp_client->surname,tmp_client->id_code,\
              tmp_client->cpf[0],tmp_client->cpf[1],tmp_client->cpf[3],tmp_client->cpf[4],\
              tmp_client->rg[0],tmp_client->rg[1],tmp_client->rg[2]);

              delete((generic_t *)&client_head,(generic_t *)tmp_client);
              puts("done.\n");
            }
            else
            {
              ERR("no such client");
            }
      break;
      #endif
      case SYNC:

      break;
      default:
          ERR("invalid opt");
      break;
      }
    }
  return 0;
}

generic_t * find(generic_t * head, uint32_t tofind_id)
{
  base_t *elem= (base_t *)head;
}

void insert(generic_t * head, generic_t * _toinsert)
{
  base_t * elem= (base_t *)head;
  base_t * toinsert= (base_t *)_toinsert;
  for (;elem->next;elem=elem->next); /* go to list tail */
  elem->next=toinsert;
  toinsert->next=NULL;
};

int delete(generic_t * head, generic_t * todelete)
{
  base_t * elem= (base_t *)head;
  base_t * bef;/*the element before the node to be deleted*/

  for(;elem->next&&elem->next!=todelete/*stop when next equal todelete*/;elem=elem->next);
  if(!elem->next) return -1; /* did not found the element  in the list, simple sanity check*/
  bef=elem;
  elem=elem->next;/* now elem == todelete*/
  if(elem->next==NULL)
  {
    elem->next=NULL;
    free(todelete);
  }
  else
  {
    bef->next=elem->next;/*set next pointer of before todelete*/
    free(todelete);
  }
  return 0;
}
