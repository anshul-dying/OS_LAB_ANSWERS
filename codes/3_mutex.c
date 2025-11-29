#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
pthread_mutex_t wrt;
int readcount = 0;
int data = 1;

void* reader(void *arg)
{
    int id = *(int*)arg;

    // enter
    pthread_mutex_lock(&mutex);
    readcount++;
    if(readcount == 1)
        pthread_mutex_lock(&wrt);
    pthread_mutex_unlock(&mutex);

    printf("Reader %d reads data = %d\n", id, data);

    // exit
    pthread_mutex_lock(&mutex);
    readcount--;
    if(readcount == 0)
        pthread_mutex_unlock(&wrt);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* writer(void* arg)
{
    int id = *(int*)arg;

    pthread_mutex_lock(&wrt);
    data++;
    printf("Writer %d writes data = %d\n", id, data);
    pthread_mutex_unlock(&wrt);

    return NULL;
}

int main()
{
    pthread_t r[3], w[3];

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&wrt, NULL);

    int rID[3] = {1,2,3};
    int wID[3] = {1,2,3};

    for(int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &rID[i]);

    for(int i = 0; i < 3; i++)
        pthread_create(&w[i], NULL, writer, &wID[i]);

    for(int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);

    for(int i = 0; i < 3; i++)
        pthread_join(w[i], NULL);

    return 0;
}
