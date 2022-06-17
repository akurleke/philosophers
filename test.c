# include <unistd.h>
# include <stdio.h>
//# include <stdlib.h>
//# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_test
{
    pthread_t   	th;
	int				tmp;
	pthread_mutex_t	mutex;
}		t_test;
pthread_mutex_t mutex;

void	*ft_test(void *data)
{
	t_test		*test;

	test = (t_test *)data;
	while (test->tmp < 8)
	{
		printf("trd 1 lock mutex\n");
		///pthread_mutex_lock(&mutex);
		if (test->tmp == 8)
			break;
		test->tmp++;
		printf("trd 1 %d\n", test->tmp);
	//	usleep(300000);
		//printf("trd 1 %d\n", test->tmp);
		//write(1, "chack\n", 6);
		//usleep(1000000);
		//pthread_mutex_unlock(&mutex);
		printf("trd 1 unlock mutex\n");
		//pthread_mutex_lock(&test->mutex);

	}
	return NULL;
	//pthread_mutex_unlock(&test->mutex);
}

// int main()
// {
// 	t_test		test;

// 	test.tmp = 0;
// 	pthread_mutex_init(&test.mutex, 0);
// 	pthread_create(&test.th, NULL, ft_test, &test);

// 	usleep(100);
// 	pthread_mutex_lock(&test.mutex);
// 	while (test.tmp < 8)
// 	{
// 	 	printf("trd 2 %d\n", test.tmp);
// 	// //	pthread_mutex_unlock(&test.mutex);
// 	// //	pthread_mutex_lock(&test.mutex);
// 	}
// 	printf("kek %d\n", test.tmp);
// 	pthread_mutex_unlock(&test.mutex);
// 	pthread_join(test.th, 0);
// 	return (0);
// }

static int counter = 0;

void	*ft_test2(void *data)
{
	t_test		*test;

	test = (t_test *)data;
	while (test->tmp < 8)
	{
		printf("trd 2 lock mutex\n");
	//	pthread_mutex_lock(&mutex);
		if (test->tmp == 8)
			break;
		test->tmp++;
		printf("trd 2 %d\n", test->tmp);
	//	usleep(300000);
		//printf("trd 2 %d\n", test->tmp);
		//write(1, "chack\n", 6);
		//usleep(1000000);
	//	pthread_mutex_unlock(&mutex);
		printf("trd 2 unlock mutex\n");
		//pthread_mutex_lock(&test->mutex);

	}
	return NULL;
	//pthread_mutex_unlock(&test->mutex);
}

char text[12];
int i = 0;

void *ft_text(void * data) {
	char *tmp = data;
	int j = 0;
	pthread_mutex_lock(&mutex);
	while (j < 5){
		text[i] = tmp[j];
		usleep(10);
		j++;
		i++;
	}
	text[i] = ' ';
	i++;
	usleep(10);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main() {
    pthread_t threads[2];
    size_t i;
	t_test		test;
test.tmp = 0;
char text2[5] = "hello";
char text3[5] = "world";
    printf("counter = %d\n", test.tmp);
    //Инициализация мьютекса
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&threads[0], NULL, ft_text, text2);
	pthread_create(&threads[1], NULL, ft_text, text3);
    pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	i = 0;
	// while (i < 12){
	// 	write(1, &text[i], 1);
	// 	i++;
	// }
	printf("%s\n", text);
    // pthread_create(&threads[1], NULL, ft_test2, &test);
	// //usleep()
	// 	while (test.tmp < 8)
	// {
	// 	printf("trd 3 lock mutex\n");
	// 	pthread_mutex_lock(&mutex);
	// 	printf("trd 3 %d\n", test.tmp);
	// 	usleep(300000);
	//  	//printf("trd 3 %d\n", test.tmp);
	// 	 pthread_mutex_unlock(&mutex);
	// 	 printf("trd 3 unlock mutex\n");
	// // //	pthread_mutex_unlock(&test.mutex);
	// // //	pthread_mutex_lock(&test.mutex);
	// }
    //     pthread_join(threads[0], NULL);
	// 	pthread_join(threads[1], NULL);
    // //Уничтожение мьютекса
    // pthread_mutex_destroy(&mutex);
    // printf("counter = %d", counter);
    return 0;
}


