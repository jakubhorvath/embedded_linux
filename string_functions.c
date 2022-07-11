#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void process_input(char* input, int* machine_num, char* product, int* quantity, struct tm* current_time){
    time_t t = time(NULL);
    *current_time = *localtime(&t);

    char* token = strtok(input, " ");

    int counter = 0;
    while( token != NULL ) {
        switch (counter)
        {
        case 1:
            *machine_num = atoi(token);
            break;
        case 2:
            strcpy(product, token);
            break;
        case 3:
            *quantity = atoi(token);
            break;
        default:
            break;
        }
        counter++;
        token = strtok(NULL, " ");
    }
}

void write_to_sales_history(char* history_file, int machine_num, char* product, int quantity, struct tm* sale_time){
    FILE* f = fopen(history_file, "a");
    char time_buffer[26];
    strftime(time_buffer, 26, "%Y-%m-%d %H:%M:%S", sale_time);

    fprintf(f, "VM %d %s %d %s\n", machine_num, product, quantity, time_buffer);
    fclose(f);
}
