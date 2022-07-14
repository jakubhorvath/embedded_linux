#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int check_amount(char* file_path, char* product_name){
    FILE* f = fopen(file_path, "r");
    if (f == NULL){
        return -2;
    }
    size_t bufferLength = 255;
    char buffer[bufferLength];
    char* tk;
    while(fgets(buffer, bufferLength, f)) {
        buffer[strcspn(buffer, "\n")] = 0;
        tk = strtok(buffer, " ");
        // if token and product_name are equal
        if (!strcmp(tk, product_name)){
            tk = strtok(NULL," ");
            fclose(f);
            return atoi(tk);
        }
    }
    
    fclose(f);
    return -1;

}

int process_input(char* input, int* machine_num, char* product, int* quantity, struct tm* current_time, char* error){
    time_t t = time(NULL);
    *current_time = *localtime(&t);
    
    char* token = strtok(input, " ");
    char machine_file_path[] = "machineInventory.txt";
    char n;
    int counter = 0;
    int available_amount = 0;
    while( token != NULL ) {
        switch (counter)
        {
        case 1:
            *machine_num = atoi(token);
            n = token[0];
            machine_file_path[16] = n;
            break;
        case 2:
            strcpy(product, token);
            break;
        case 3:
            
            *quantity = atoi(token);
            available_amount = check_amount(machine_file_path, product);
            if (available_amount < 0){
                strcpy(error, "Error: Product not found in inventory");
                return 1;
            }
            else if (*quantity < 0 ){
                strcpy(error, "Error: Invalid quantity provided");
                return 1;
            } else if (available_amount < *quantity){
                strcpy(error, "Error: Not enough product available");
                return 1;
            } else{
                return 0;
            }
            break;
        default:
            break;
        }
        counter++;
        token = strtok(NULL, " ");
    }
    return 0;
}

void write_to_sales_history(char* history_file, int machine_num, char* product, int quantity, struct tm* sale_time){
    FILE* f = fopen(history_file, "a");
    char time_buffer[26];
    strftime(time_buffer, 26, "%Y-%m-%d %H:%M:%S", sale_time);

    fprintf(f, "VM %d %s %d %s\n", machine_num, product, quantity, time_buffer);
    fclose(f);
}
