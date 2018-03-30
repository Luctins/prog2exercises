/**
 * @file exerc_pto.h
 * @author Lucas Martins Mendes
 */

#ifndef EXERC_PTO
#define EXERC_PTO

#define BUFF_LEN 100 /*!<default buffer lenght*/

/**
 * @struct base_struct
 * base struct containing just the next pointer
 */
typedef struct base_struct {
  struct base_struct *next;
}base_t;


/**
 * @struct _tool
 * tool struct.
 */
struct _tool
{
 uint32_t code;/*!<id code*/
 char desc[BUFF_LEN];/*!<name with description*/
 uint32_t price;/*!<price*/
};

/**
 * @union tool_node
 * node for inserting in linked lists.
 */
typedef union tool_node
{
  base_t base;
  struct _tool tool;
}tool_t;



/**
 * @struct _client
 * client identification struct.
 */
struct _client
{
  uint32_t id_code;
  char name[BUFF_LEN];
  char surname[BUFF_LEN];
  uint16_t cpf[4];
  const char cpf_fmt[12] = "%u.%u.%u-%u";
  uint16_t rg[3];
  const char rg_fmt[9] = "%u.%u.%u";
} client_t;

/**
 * @union client_node
 * client struct for using with linked lists.
 */
typedef union client_node
{
  base_t base;
  struct _client client;
}client_t;

/**
 * Sale control struct.
 */
struct sale_control
{
  uint32_t code;
  uint32_t tool_code;
  uint32_t client_code;
  uint32_t value;
  const char param_name[];
};


#endif /* EXERC_PTO */
