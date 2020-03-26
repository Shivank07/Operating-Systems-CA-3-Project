#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t mut_ex, writer_value;
int shared, reader_count = 0;

void *writerscode(void *ptr){
        pthread_mutex_lock(&writer_value);
        int x = rand() % 10;
        int m = ((int)ptr);
        printf("##################################################\n");
        printf("Writer%d Wait for Random time between 0ns and 10ns = %d\n", m, x);
        sleep(x);
        printf("Insert the number of time Writer%d want to write:\n", m);
        int k; 
        scanf("%d", &k);
        printf("Now Writer%d is writing... i.e. ADDING...\n", m);
        int j;
        for(j=0; j<t; j++){
                printf("Insert the %dth value to write:\n", (j+1));
                int u;
                scanf("%d", &u);
                shared = shared + u;
        }
        printf("UPDATED value of Shared variable = %d \n", shared);
        printf("##################################################\n");
        pthread_mutex_unlock(&writer_value);
}
