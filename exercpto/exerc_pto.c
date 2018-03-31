#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#define DEBUG

#include "exerc_pto.h"

client_t  client_head = { .next=NULL};
tool_t   tool_head   = { .next=NULL };
sales_c_t  sales_c_head = { .next=NULL };

client_t  *tmp_client;
tool_t    *tmp_tool;
sales_c_t  *tmp_sales_c;

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

    switch (_opt[0])
    {
      case TOOL:
        switch(_opt[1])
        {
          case ADD:
            tmp_tool=malloc(sizeof(generic_t));
            if(tmp_tool==NULL)
            {
              ERR("mem");
              break;
            }
            insert((generic_t *)&tool_head,(generic_t *)tmp_tool);
            puts("id_code:%u");
            scanf("%u",&tmp_tool->id_code);
            puts("desc:%s");
            fflush(stdin);
            fgets(tmp_tool->desc,BUFF_LEN,stdin);
            puts("price:%lf");
            scanf("%lf",&tmp_tool->price);
          break;

          case LIST:
            LIST_ITER(&tool_head,tmp_tool,TOOL_FMT,TOOL_ARGS(tmp_tool));
          break;
          case DELETE:
            /*TODO use find to find item to delete by id code*/
            puts("insert tool code to delete");
            uint32_t tofindcode;
            scanf("%u",&tofindcode);
            tmp_tool=(tool_t *)find((generic_t *)&tool_head,tofindcode);
            if(tmp_tool)
            {
              printf("deleting\t"TOOL_FMT"\n",TOOL_ARGS(tmp_tool));
              delete((generic_t *)&tool_head,(generic_t *)tmp_tool);
              puts("done.\n");
            }
            else
            {
              ERR("no such sale");
            }
          break;
          default:
                ERR("invalid opt");
                break;
              }
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
            puts("insert the client data\nname:%s");
            fflush(stdin);
            fgets(tmp_client->name,BUFF_LEN,stdin);
            if(tmp_client->name[0]=='\0') fgets(tmp_client->name,BUFF_LEN,stdin);
            puts("surname:%s");
            fflush(stdin);
            fgets(tmp_client->surname,BUFF_LEN,stdin);
            puts("id_code:%u");
            scanf("%u", &tmp_client->id_code);
            puts("cpf:"CPF_FMT);
            scanf(CPF_FMT,CPF_ARGS(&tmp_client->cpf));
            puts("rg:"RG_FMT);
            scanf(RG_FMT,RG_ARGS(&tmp_client->rg));
          break;
          case LIST:
            LIST_ITER(&client_head,tmp_client, CLIENT_FMT,CLIENT_ARGS(tmp_client));
          break;
          case DELETE:
            puts("insert client id to delete");
            uint32_t tofindcode;
            scanf("%u",&tofindcode);
            tmp_client=(client_t *)find((generic_t *)&client_head,tofindcode);
            if(tmp_client)
            {
              printf("deleting\t "CLIENT_FMT"\n",CLIENT_ARGS(tmp_client));
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
      case SALES:
        switch(_opt[1])
        {
          case ADD:
            tmp_sales_c=malloc(sizeof(generic_t));
            if(tmp_sales_c==NULL)
            {
              ERR("mem");
              break;
            }
            insert((generic_t *)&sales_c_head,(generic_t *)tmp_sales_c);
            puts("insert the sale info\n");
            puts("id_code:%u");
            scanf("%u\n",&tmp_sales_c->id_code);
            puts("sales_c_code:%u");
            scanf("%u\n",&tmp_sales_c->tool_code);
            puts("client_code:%u");
            scanf("%u\n",&tmp_sales_c->client_code);
            puts("value:%u");
            scanf("%lf\n",&tmp_sales_c->value);
          break;
          case LIST:
            LIST_ITER(&sales_c_head,tmp_sales_c,SALES_C_FMT,SALES_C_ARGS(tmp_sales_c));
          break;
          case DELETE:
            /*TODO use find to find item to delete by id code*/
            puts("insert sale id to delete");
            uint32_t tofindcode;
            scanf("%u",&tofindcode);
            tmp_sales_c=(sales_c_t *)find((generic_t *)&sales_c_head,tofindcode);
            if(tmp_sales_c)
            {
              printf("deleting\t"SALES_C_FMT"\n",SALES_C_ARGS(tmp_sales_c));
              delete((generic_t *)&sales_c_head,(generic_t *)tmp_sales_c);
              puts("done.\n");
            }
            else
            {
              ERR("no such sale");
            }
            break;
            default:
                ERR("invalid opt");
            break;
          }
      break;
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
  for (;elem->next&&elem->id_code!=tofind_id;elem=elem->next);
  return (generic_t *)elem;
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
