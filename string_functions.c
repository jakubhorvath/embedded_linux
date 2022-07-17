#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>

bool isproduct(char* file_text, size_t index, char* product_name){
    int i = 0;
    while (file_text[index] == product_name[i]){
        index++;
        i++;
        if (product_name[i] == '\0')
            return true;
    }
    return false;
}


int machine_change_product(int machine_num, char* commodity_name, int amount){
    char c=machine_num+'0';
    char file_path[] = "machineInventoryn.txt";
    file_path[16] = c;

    int fd = open(file_path, O_RDWR, S_IRUSR | S_IWUSR);
    struct stat sb;
    if (fstat(fd, &sb) == 1){
        perror("couldnt get filesize\n");
    } 
    char* file_in_memory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("%s\n", file_in_memory);
    for (size_t i=0; i<sb.st_size; i++){
        if (isproduct(file_in_memory, i, commodity_name)){
            if (amount < 10){
                file_in_memory[i+strlen(commodity_name)+1] = '0';
                file_in_memory[i+strlen(commodity_name)+2] = amount+'0';
            }
            else{
                strncpy(file_in_memory+i+strlen(commodity_name)+1, "10", 2);
            }
            break;
        }
    }    
}

void change_all(){
    char file_path[] = "machineInventoryn.txt";
    char c;
    for (int i=1; i<4; i++){
        c = i+'0';
        file_path[16] = c;
        FILE* f = fopen(file_path, "r+");
        machine_change_product(i, "apple", 10);
        size_t bufferLength = 255;
        char buffer[bufferLength];
        char* tk;
        size_t line_num = 0;
        while(fgets(buffer, bufferLength, f)) {
            line_num++;
            if (line_num == 1){
                continue;
            }
            buffer[strcspn(buffer, "\n")] = 0;
            tk = strtok(buffer, " ");
            tk = strtok(NULL," ");
            printf("%s\n", tk);
            machine_change_product(i, tk, 10);
        }
    }

}

int check_amount(char* file_path, char* product_name){
    FILE* f = fopen(file_path, "r");
    if (f == NULL){
        return -2;
    }
    size_t bufferLength = 255;
    char buffer[bufferLength];
    char* tk;
    size_t line_num = 0;
    while(fgets(buffer, bufferLength, f)) {
        line_num++;
        if (line_num == 1){
            continue;
        }
        buffer[strcspn(buffer, "\n")] = 0;
        tk = strtok(buffer, " ");
        tk = strtok(NULL," ");
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
    char machine_file_path[] = "machineInventoryn.txt";
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
                strcpy(error, "Error: Product not found in inventory\n");
                return 1;
            }
            else if (*quantity < 0 ){
                strcpy(error, "Error: Invalid quantity provided\n");
                return 1;
            } else if (available_amount < *quantity){
                strcpy(error, "Error: Not enough product available\n");
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
