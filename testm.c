#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

pthread_mutex_t	mutex;
int				i = 0;

void	*ft_print()
{
	printf ("trd 1\n");
	while (i < 8)
		i++;
	return NULL;
}

void	*ft_print1()
{
	//pthread_mutex_lock(&mutex);
	printf ("trd 2\n");
	while (i < 8)
		i++;
	return NULL;
	//pthread_mutex_unlock(&mutex);
}



int main ()
{
	pthread_t	threads[2];

	pthread_mutex_init(&mutex, 0);
	pthread_create(&threads[0], NULL, ft_print, NULL);
	pthread_create(&threads[1], NULL, ft_print1, NULL);
	while (i < 8)
	{
		printf ("%d\n", i);
	}

	pthread_join(threads[0], 0);
	pthread_join(threads[1], 0);

	return (0);
}
