#include "stdio.h"

int check_amount(char* file_path, char* product_name);

/*
 * input - the input string obtained from the user
 * machine_num - pointer to int where the machine number will be stored
 * product - string pointer  where the product name will be stored
 * quantity - pointer to int where quantity of the product will be stored
 * current_time - pointer to struct tm* where the time of the purchase will be stored
 */

int process_input(char* input, int* machine_num, char* product, int* quantity, struct tm* current_time, char* error);

/*
 * history_file - pointer to opened output file
 * machine_num - number of machine obtained from "process_input" function
 * product - product name obtained from "process_input" function
 * quantity - quantity of product obtained from "process_input" function
 * sale_time - time of sale obtained from "process_input" function
 */
void write_to_sales_history(char* history_file, int machine_num, char* product, int quantity, struct tm* sale_time);

/*
 * machine_num - number of machine
 * commodity_name - the name of the product to be changed
 * amount - the amount of the product to be changed to
 */
int machine_change_product(int machine_num, char* commodity_name, int amount);
/* this function opens the file at machineInventory{machine_num}.txt 
   and changes the number of commodities available to the value of amount
*/

void change_all();