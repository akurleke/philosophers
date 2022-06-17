# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct          s_data;

typedef struct  s_philo
{
	int             index;
	long long       last_eat;
	int             lfork;
	int	            rfork;
	int             eat_count;
	struct s_data	*data;
	pthread_mutex_t mutex;
}               t_philo;


typedef struct  s_data
{
	int         count;
	int	        time_to_die;
	int         time_to_eat;
	int         time_to_sleep;
	int	        must_eat;
	int         end;
	long long   start;

	t_philo	*philosophers;
	pthread_mutex_t *forks_m;
	pthread_mutex_t write_m;
	pthread_mutex_t is_dead;

}               t_data;


int		    ft_exit(char *s);
int         ft_init(t_data *data, int argc, char **argv);
int		    ft_is_digit(char *s);
int	        ft_atoi(char *str);
long long	ft_get_time(void);
void        ft_print_status(t_philo *philosopher, char *message);
void     	ft_clear(t_data *data);

int	ft_atoi(char *str)
{
	int	i;
	int	sing;
	int	nb;

	sing = 0;
	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-')
		sing = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nb = 10 * nb;
		nb = nb + (str[i] - '0');
		i++;
	}
	if (sing == 1)
		nb = -nb;
	return (nb);
}


int	ft_isdigit(int ch)
{
	if ((ch >= 48) && (ch <= 57))
		return (1);
	else
		return (0);
}


void    ft_init_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->count)
    {
        data->philosophers[i].index = i + 1;
        data->philosophers[i].lfork = i;
        data->philosophers[i].rfork = (i + 1) % data->count;
        data->philosophers[i].eat_count = 0;
        data->philosophers[i].data = data;
        pthread_mutex_init(&data->philosophers[i].mutex, NULL);
        i++;
    }
}

int     ft_init_mutexes(t_data *data)
{
    int i;

    i = 0;
    if (!(data->forks_m = malloc(sizeof(pthread_mutex_t) * data->count)))
        return (1);
    while (i < data->count)
    {
        pthread_mutex_init(&data->forks_m[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->write_m, NULL);
    pthread_mutex_init(&data->is_dead, NULL);
    pthread_mutex_lock(&data->is_dead);
    return (0);
}

int     ft_init(t_data *data, int argc, char **argv)
{
    int i;

	i = 1;
    data->philosophers = NULL;
    data->forks_m = NULL;
	while (i < argc)
	{
		if (ft_is_digit(argv[i]) || ft_atoi(argv[i]) > 2147483647)
			return (1);
		i++;
	}
    data->end = 0;
	data->count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (i == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
    data->philosophers = malloc(sizeof(t_philo) * data->count);
    if (!(data->philosophers))
        return (1);
    ft_init_philos(data);
	return (ft_init_mutexes(data));
}

int		ft_exit(char *s)
{
	printf("%s\n", s);
	return (-1);
}

int		ft_is_digit(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void    ft_print_status(t_philo *philosopher, char *message)
{
    pthread_mutex_lock(&philosopher->data->write_m);
    printf("%lld %d %s\n", (ft_get_time() - philosopher->data->start), philosopher->index, message);
    if (*message != 'd')
        pthread_mutex_unlock(&philosopher->data->write_m);
}

void     ft_clear(t_data *data)
{
	int	i;

	if (data->forks_m)
	{
		i = 0;
		while (i < data->count)
			pthread_mutex_destroy(&data->forks_m[i++]);
		if (data->forks_m)
			free(data->forks_m);
	}
	if (data->philosophers)
	{
		i = 0;
		while (i < data->count)
			pthread_mutex_destroy(&data->philosophers[i++].mutex);
		if (data->philosophers)
			free(data->philosophers);
	}
	pthread_mutex_destroy(&data->write_m);
	pthread_mutex_destroy(&data->is_dead);
    free(data);
	// printf("check\n");
}

long long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}


void    *ft_is_dead(void *philo)
{
	t_philo *p;
	long long time;

	p = (t_philo *)philo;
	while (1 && p->eat_count != p->data->must_eat)
	{
		pthread_mutex_lock(&p->mutex);
		time = ft_get_time() - p->last_eat;
		if ((time > p->data->time_to_die))
		{
			ft_print_status(p, "died");
			ft_clear(p->data);
			pthread_mutex_unlock(&p->data->is_dead);
			return ((void *)0);
		}
		usleep(1000);
		pthread_mutex_unlock(&p->mutex);
	}
	return (NULL);
}

void    ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_m[philo->lfork]);
	pthread_mutex_lock(&philo->data->forks_m[philo->rfork]);
	philo->last_eat = ft_get_time();
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->forks_m[philo->lfork]);
	pthread_mutex_unlock(&philo->data->forks_m[philo->rfork]);
}

void    ft_sleep_and_think(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	ft_print_status(philo, "is thinking");
}

void    *ft_routine(void *philo)
{
	pthread_t	tid;
	t_philo *philosopher;

	philosopher = (t_philo *)philo;
	if (pthread_create(&tid, NULL, &ft_is_dead, philo))
		return ((void *)1);
	pthread_detach(tid);
	while (1 && philosopher->eat_count != philosopher->data->must_eat)
	{
		ft_eat(philosopher);
		ft_sleep_and_think(philosopher);
		if (philosopher->eat_count == philosopher->data->must_eat)
			philosopher->data->end++;
	}
	if (philosopher->data->end == philosopher->data->count)
	{
		printf("Everyone ate enough\n");
		ft_clear(philosopher->data);
		pthread_mutex_unlock(&philosopher->data->is_dead);
	}
	return ((void *)0);
}

int     ft_create_threads(t_data *data)
{
	int         i;
	t_philo     *ph;
	pthread_t   tid;

	i = 0;
	ph = data->philosophers;
	ph->data->start = ft_get_time();
	while (i < data->count)
	{
		ph[i].last_eat = ft_get_time();
		if (pthread_create(&tid, NULL, &ft_routine, &(ph[i])))
			return (1);
		pthread_detach(tid);
		i++;
	}
	return (0);
}

int	    main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (ft_exit("Error: invalid arguments"));
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 dead\n");
		return (0);
	}
	if (!(data = malloc(sizeof(t_data))))
		return (ft_exit("Error"));
	if (ft_init(data, argc, argv))
	{
		ft_clear(data);
		return (ft_exit("Error"));
	}
	if (ft_create_threads(data))
	{
		ft_clear(data);
		return (ft_exit("Error"));
	}
	//pthread_mutex_lock(&(data->is_dead));
	// ft_clear(data);
	return (0);
}
