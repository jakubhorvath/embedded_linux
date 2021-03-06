#include "stdio.h"

/*
 * input - the input string obtained from the user
 * machine_num - pointer to int where the machine number will be stored
 * product - string pointer  where the product name will be stored
 * quantity - pointer to int where quantity of the product will be stored
 * current_time - pointer to struct tm* where the time of the purchase will be stored
 */

void process_input(char *input, int *machine_num, char *product, int *quantity, struct tm *current_time);

/*
 * history_file - pointer to opened output file
 * machine_num - number of machine obtained from "process_input" function
 * product - product name obtained from "process_input" function
 * quantity - quantity of product obtained from "process_input" function
 * sale_time - time of sale obtained from "process_input" function
 */
void write_to_sales_history(FILE *history_file, int machine_num, char *product, int quantity, struct tm *sale_time);