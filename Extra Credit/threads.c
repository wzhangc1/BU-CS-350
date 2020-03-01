#include <stdio.h>
#include <pthread.h>

volatile int counter1 = 0;
volatile int counter2 = 0;
volatile int counter3 = 0;
const int LOOPS = 10000000;

pthread_mutex_t lock1;
pthread_spinlock_t lock2;
pthread_rwlock_t lock3;

void *worker1(void *arg)
{
	for (int i = 0; i < LOOPS; i++)
	{
		pthread_mutex_lock(&lock1);
		counter1++;
		pthread_mutex_unlock(&lock1);
	}
	
	return NULL;
}

void *worker2(void *arg)
{
	for (int i = 0; i < LOOPS; i++)
	{
		pthread_spin_lock(&lock2);
		counter2++;
		pthread_spin_unlock(&lock2);
	}
	
	return NULL;
}

void *worker3(void *arg)
{
	for (int i = 0; i < LOOPS; i++)
	{
		pthread_rwlock_wrlock(&lock3);
		counter3++;
		pthread_rwlock_unlock(&lock3);
	}
	
	return NULL;
}

int main (int argc, char *argv[])
{
	pthread_t p1, p2, p3, p4, p5;
	pthread_t threads[5] = {p1, p2, p3, p4, p5};
	
	//Mutex-------------------------------------------------------------
	pthread_mutex_init(&lock1, NULL);
	
	for (int i = 0; i < 5; i++)
	{
		pthread_create(&threads[i], NULL, worker1, NULL);
		pthread_join(threads[i], NULL);
	}
	
	printf("Mutex value: %d\n", counter1);
	
	pthread_mutex_destroy(&lock1);
	
	//Spin--------------------------------------------------------------
	pthread_spin_init(&lock2, PTHREAD_PROCESS_PRIVATE);
	
	for (int i = 0; i < 5; i++)
	{
		pthread_create(&threads[i], NULL, worker2, NULL);
		pthread_join(threads[i], NULL);
	}
	
	printf("Spin lock value: %d\n", counter2);
	
	pthread_spin_destroy(&lock2);
	
	//ReadersWriter-----------------------------------------------------
	pthread_rwlock_init(&lock3, NULL);
	
	for (int i = 0; i < 5; i++)
	{
		pthread_create(&threads[i], NULL, worker3, NULL);
		pthread_join(threads[i], NULL);
	}
	
	printf("Read Write value: %d\n", counter3);
	
	pthread_rwlock_destroy(&lock3);
	
	return 0;
}
