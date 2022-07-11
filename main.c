#include "string_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    int machine_num;
    char* product_name = (char*) malloc(12*sizeof(char));
    int quantity;
    struct tm sale_time;

    FILE *sales_history_file = fopen("sales_history.txt", "w");

    char input1[100] = "VM 1 coke 10"; 
    process_input(input1, &machine_num, product_name, &quantity, &sale_time);
    write_to_sales_history(sales_history_file, machine_num, product_name, quantity, &sale_time);

    sleep(2);

    char input2[100] = "VM 2 sprite 10"; 
    process_input(input2, &machine_num, product_name, &quantity, &sale_time);
    write_to_sales_history(sales_history_file, machine_num, product_name, quantity, &sale_time);

    sleep(2);
    
    char input3[100] = "VM 3 snickers 10"; 
    process_input(input3, &machine_num, product_name, &quantity, &sale_time);
    write_to_sales_history(sales_history_file, machine_num, product_name, quantity, &sale_time);

    sleep(2);
    
    char input4[100] = "VM 4 water 10"; 
    process_input(input4, &machine_num, product_name, &quantity, &sale_time);
    write_to_sales_history(sales_history_file, machine_num, product_name, quantity, &sale_time);

    fclose(sales_history_file);
}