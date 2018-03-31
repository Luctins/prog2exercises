/**
 * @file exerc_pto.h
 * @author Lucas Martins Mendes
 */

#ifndef EXERC_PTO
#define EXERC_PTO

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>


/*--------Macros-------*/

#define _STR(s) #s
#define STRINGIFY(s) _STR(s)

#define _TOKENPASTE(x,y) x # y
#define TOKENPASTE(x,y) _TOKENPASTE(x,y)

#define ERR(str) printf(str" ERR at "STRINGIFY(LINE)" in %s",__func__)

/**
* print struct contents.
* @param head  head of list
* @param param list of variable addresses for printing
* @param fmt   [description]
* @param iteration element
*/
#ifndef LIST_ITER
#define LIST_ITER(head,iterel,fmt,...)                \
for(iterel=head;iterel;iterel=iterel->next)     \
{                                                     \
  printf(fmt"\n",__VA_ARGS__);                        \
}                                                     \
puts("\n");
#endif /* LIST_ITER */

/*----------Constants---------*/

#define BUFF_LEN 100 /*!<default buffer lenght*/

#define CPF_FMT "%hu.%hu.%hu-%hu"
#define CPF_ARGS(varname) varname[0],varname[1],varname[3],varname[4]

#define RG_FMT "%hu.%hu.%hu"
#define RG_ARGS(varname) varname[0],varname[1],varname[3]

#define CLIENT_FMT "id_code:%u name:%s surname:%s cpf:"CPF_FMT" rg:"RG_FMT
#define CLIENT_ARGS(var) var->id_code,var->name,var->surname,\
                          CPF_ARGS(var->cpf),RG_ARGS(var->rg)

#define SALES_C_FMT "id_code:%u tool_code:%u client_code:%u value:%lf"
#define SALES_C_ARGS(var) var->id_code, var->tool_code, var->client_code, var->value

#define TOOL_FMT "id_code:%u desc:%s price:%lf"
#define TOOL_ARGS(var) var->id_code, var->desc, var->price

const char menu_opt[3][5][20] =
  {
    {"Tool stock control","client database","sales database","sync to disk",'\0'},
    {"add","list","delete",'\0'},
    {'\0'}
  };

enum l0_menu
{
  TOOL=0,
  CLIENT,
  SALES,
  SYNC
};
enum sync_menu
{
  SAVE=0,
  LOAD
};

enum l1_menu
{
  ADD=0,
  LIST,
  DELETE
};

/*----------data structures---------*/
/**
 * @struct _tool
 * tool struct.
 */
typedef struct _tool
{
  void * next;
 uint32_t id_code;/*!<id code*/
 char desc[BUFF_LEN];/*!<name with description*/
 double price;/*!<price*/
}tool_t;


/**
 * @struct _client
 * client identification struct.
 */
typedef struct _client
{
  void * next;
  uint32_t id_code;
  char name[BUFF_LEN];
  char surname[BUFF_LEN];
  uint16_t cpf[4];
  uint16_t rg[3];
}client_t;


/**
 * @struct _sale_c
 * Sale control struct.
 */
typedef struct _sales_c
{
  void * next;
  uint32_t id_code;
  uint32_t tool_code;
  uint32_t client_code;
  double value;
}sales_c_t;

typedef struct _base
{
  void * next;
  uint32_t id_code;
}base_t;
/**
 * @union _generic
 * union for casting into when inserting into lists.
 */
typedef union generic
{
  struct _base base;
  struct _tool tool;
  struct _client client;
  struct _sales_c sales;
}generic_t;

/**
 * Insert element into linked list.
 * @param  head     list head
 * @param  toinsert element to insert into list tail
 * @return
 */
void insert(generic_t * head, generic_t * toinsert);

/**
 * delete element from list and re-link list pointers.
 * @param  head     the list head
 * @param  todelete to delete
 * @return          -1 on err
 */
int delete(generic_t * head, generic_t * todelete);

/**
 * find object by id in linked list.
 * @param  head      list head
 * @param  tofind_id id to find
 * @return           [description]
 */
generic_t * find(generic_t * head, uint32_t tofind_id);


#endif /* EXERC_PTO */
