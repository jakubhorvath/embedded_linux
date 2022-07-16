#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdint.h>
#include "string_functions.h"
#include <time.h>

pthread_t* tid = NULL;
int* cfd = NULL;
int count = 0;
char *READY = "The vending machine is ready to use\n";
char *RECV = "The order have been received\n";
int status = 0;

void *thread_proc_refill(void* arg){
    while (0 == 0)
    {
        //We will handle the refilling function here
        printf("Refilling...\n");
        status = 1;
        sleep(20);
        status = 0;
        sleep(40);
    }
    
}
void *thread_proc(void* arg){
    
    int temp = *((int*)arg);
    char buffer[1024];
    
    memset(buffer, 0, sizeof(buffer));
    char file_path[40] = "salesHistory.txt";
    while (0 == 0)
    {
        int r = recv(temp,buffer,sizeof(buffer),0);
        int machine_number;
        char* product = (char*) malloc(20*sizeof(char));
        char* error = (char*) malloc(100*sizeof(char));
        int quantity;
        struct tm current_time;
        int value = process_input(buffer,&machine_number,product,&quantity,&current_time,error);
        printf("%d\n",value);
        if(value == 1){
            send(temp,error,strlen(error),0);
        }else
        {
            write_to_sales_history(file_path, machine_number,product,quantity,&current_time);
            while(status == 1){
                printf("On refilling process\n");
                sleep(2);
            }
            send(temp,RECV,strlen(RECV),0);
        }
    } 
}

void signal_handler(int sig)
{
    //Free allocated memory 
    free(cfd);
    cfd = NULL;
    free(tid);
    tid = NULL;
    count = 0;
    exit(0); //Terminate the main process
}

int main(int argc, char** argv)
{
    signal(SIGINT, signal_handler);
    int sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in saddr;
    struct sockaddr caddr; 
    int clen = sizeof(caddr);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(5000);
    saddr.sin_addr.s_addr = 0; 
    bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));
    listen(sfd, 10);
    pthread_t refill_thread;
    pthread_create(&refill_thread,NULL,thread_proc_refill,NULL);
    while (0 == 0)
    {
        int tmp = accept(sfd, (struct sockaddr*)&caddr, &clen);
        if (tmp >= 0)
        {
            tid = (pthread_t*)realloc(tid,sizeof(pthread_t)*(count+1));
            cfd = (int*)realloc(cfd, (count + 1) * sizeof(int));
            cfd[count] = tmp;
            send(tmp,READY,strlen(READY),0);
            int* arg = (int*)calloc(1, sizeof(int));
            *arg = tmp;
            pthread_create(&tid[count], NULL, thread_proc, arg);
            count += 1;
        }
    }
}