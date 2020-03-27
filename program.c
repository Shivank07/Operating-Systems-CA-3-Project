#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>


pthread_mutex_t mut_ex, writer_value;
int shared, reader_count = 0;

void *writerscode(void *ptr){
        pthread_mutex_lock(&writer_value);
        int x = rand() % 10;
        int m = ((int)ptr);
        printf("\n\n");
        printf("Writer%d waits for Random time (0 to 10ns) = %d\n", m, x);
        sleep(x);
        printf("Insert the number of times Writer%d want to write:\n", m);
        int k; 
        scanf("%d", &k);
        printf("\n|-- Writer%d is currently performing Write operation (adding) --|\n", m);
        int j;
        for(j=0; j<k; j++){
                printf("Insert value#%d to write:\n", (j+1));
                int u;
                scanf("%d", &u);
                shared = shared + u;
        }
        printf("Updated value of Shared variable = %d \n", shared);
        printf("\n");
        pthread_mutex_unlock(&writer_value);
}
void *readerscode(void *ptr){
        //Entry Part
        pthread_mutex_lock(&mut_ex);
        reader_count++;
        if(reader_count==1){
                pthread_mutex_lock(&writer_value);//No writer should come
        }
        pthread_mutex_unlock(&mut_ex);//so next reader can come
        //Exit Part
        int x = rand() % 10;
        int m = ((int)ptr);
        printf("Reader%d waits for Random time (0 to 10ns) = %d\n", m, x);
        sleep(x);
        printf("Insert the number of times Reader%d want to read:\n", m);
        int k;
        scanf("%d", &k);
        printf("\n|-- Reader%d is currently performing Read operation --|\n", m);
        int j;
        for(j=0; j<k; j++){
                printf("Reader%d reads the shared value as %d\n", m, shared);
        }
        printf("The number of Readers present = %d\n", reader_count);
        pthread_mutex_lock(&mut_ex);
        reader_count--;
        if(reader_count==0){//Now writer can come if they want
                pthread_mutex_unlock(&writer_value);
        }
        pthread_mutex_unlock(&mut_ex);
}
