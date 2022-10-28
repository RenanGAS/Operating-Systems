#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_THREADS 5

sem_t semaphore;

int value = 5;

void *thread_func(void *param)
{
    int id;
    id = *((int *)param);

    printf("\nTHREAD %d: Esperando para entrar na SC...\n", id);

    sem_wait(&semaphore);

    printf("\nTHREAD %d: Entrei!\n", id);

    value += 1;

    printf("\nTHREAD %d: Acrescentei 1!\n", id);

    printf("\nTHREAD %d: Vou sair da SC...\n", id);

    sem_post(&semaphore);

    printf("\nTHREAD %d: Adeus!\n", id);

    pthread_exit(0);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    
    int idThreads[NUM_THREADS];

    sem_init(&semaphore, 0, 1);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        idThreads[i] = i;
        pthread_create(&threads[i], NULL, (void *)&thread_func, (void *)&idThreads[i]);
    }

    printf("\nTHREAD %u: Esperando as threads terminarem de trabalhar...\n", getpid());

    /* Espera os threads encerrarem */
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);

    printf("\nTHREAD %u: Muito bem! Temos value = %d!\n\n", getpid(), value);

    return EXIT_SUCCESS;
}