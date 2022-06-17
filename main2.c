/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurleke <akurleke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:28:51 by akurleke          #+#    #+#             */
/*   Updated: 2022/06/16 16:02:59 by akurleke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	ft_check(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Invalid arguments!\n");
		return (0);
	}
	while (i < argc)
	{
		if (ft_philo_atoi(argv[i]) <= 0)
		{
			printf("Invalid arguments!\n");
			return (0);
		}
	//	printf("check %d\n", ft_philo_atoi(argv[i]));
		i++;
	}
	return (1);
}

int	ft_init_struct(int argc, char **argv, t_param *p)
{
		//t_param	*p;

		//p = (t_param *)malloc(sizeof(t_param));
		//if (!p)
		//	return (NULL);
		p->i = 0;
		p->died = 0;
		p->count = ft_philo_atoi(argv[1]);
		p->time_die = ft_philo_atoi(argv[2]);
		p->time_eat = ft_philo_atoi(argv[3]);
		p->time_sleep = ft_philo_atoi(argv[4]);
		p->stop = 0;
		p->count_eat = -1;
		if (argc == 6)
			p->count_eat = ft_philo_atoi(argv[5]);
		p->philos = malloc(sizeof(t_philo) * p->count);
		p->threads = malloc(sizeof(pthread_t) * p->count);
		p->fork = malloc(sizeof(pthread_mutex_t) * p->count);
		//p->m_died = malloc(sizeof(pthread_mutex_t));
		//p->print = malloc(sizeof(pthread_mutex_t));
		if (!p->threads || !p->philos || !p->fork)
			return (1);
		pthread_mutex_init(&p->print, NULL);
		pthread_mutex_init(&p->m_died, NULL);
	//	pthread_mutex_lock(&p->m_died);
		while (p->i <= p->count)
		{
			p->philos[p->i].time = ft_time_now();
			p->philos[p->i].number = p->i + 1;
			p->philos[p->i].fork_l = p->i;
			p->philos[p->i].fork_r = (p->i + 1) % p->count;
			pthread_mutex_init(&p->fork[p->i], NULL);
			p->i++;
		}
	return (0);
}

void	*ft_eat(void *param)
{
	t_param		*ph;
	int			i;
	int			n;

	i = 0;

	ph = (t_param *)param;
	n = ph->n;
	if (ph->philos[n].number % 2 != 0)
		usleep(ph->time_eat * 990);
	while (i < ph->count_eat || ph->count_eat == -1)
	{
		//pthread_mutex_lock(&ph->m_died);
		if (ph->died == 1)
		{
		//pthread_mutex_unlock(&ph->m_died);
			return (0);
		}
		pthread_mutex_lock(&ph->fork[ph->philos[n].fork_l]);
		pthread_mutex_lock(&ph->print);
		printf("%lu %d has taken a fork\n", ft_time_now() - ph->t_s, ph->philos[n].number);
		pthread_mutex_unlock(&ph->print);
		pthread_mutex_lock(&ph->fork[ph->philos[n].fork_r]);
			if (ph->died == 1)
		{
		//pthread_mutex_unlock(&ph->m_died);
			return (0);
		}
		pthread_mutex_lock(&ph->print);
		printf("%lu %d has taken a fork\n", ft_time_now() - ph->t_s, ph->philos[n].number);
		printf("%lu %d is eating\n", ft_time_now() - ph->t_s, ph->philos[n].number);
		pthread_mutex_unlock(&ph->print);
		ph->philos[n].time = ft_time_now();
		usleep(ph->time_eat * 1000);
		pthread_mutex_unlock(&ph->fork[ph->philos[n].fork_r]);
		pthread_mutex_unlock(&ph->fork[ph->philos[n].fork_l]);
			if (ph->died == 1)
		{
		//pthread_mutex_unlock(&ph->m_died);
			return (0);
		}
		pthread_mutex_lock(&ph->print);
		printf("%lu %d is sleeping\n", ft_time_now() - ph->t_s, ph->philos[n].number);
		pthread_mutex_unlock(&ph->print);
		usleep(ph->time_sleep * 1000);
			if (ph->died == 1)
		{
		//pthread_mutex_unlock(&ph->m_died);
			return (0);
		}
		pthread_mutex_lock(&ph->print);
		printf("%lu %d is thinking\n", ft_time_now() - ph->t_s, ph->philos[n].number);
		pthread_mutex_unlock(&ph->print);
		i++;
	}
	ph->stop++;
	return (0);
}

void	*print(void *philo)
{
	t_philo *ph;
	long	time_n;

	ph = (t_philo *)philo;
	printf("%lu № %d\n", ph->time, ph->number);
	usleep(5000);
	time_n = ft_time_now();
	printf("%lu № %d\n", time_n + ph->time, ph->number);
	return (0);
}

void	*ft_stop(void *param)
{
	t_param	*ph;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ph = (t_param *)param;
	while (ph->stop != ph->count)
	{
		usleep(2000);
		if (ph->time_die < (ft_time_now() - ph->philos[i].time))
		{
			pthread_mutex_lock(&ph->print);
			printf("%ld %d died\n", ft_time_now() - ph->t_s, ph->philos[i].number);
			ph->stop = ph->count;
			pthread_mutex_lock(&ph->m_died);
			ph->died = 1;
			pthread_mutex_unlock(&ph->m_died);

			pthread_mutex_unlock(&ph->print);

			//j = 0;
			// while (j < ph->count)
			// {
			// 	j++;
			// }
			return (0);
		}
		i++;
		if (i == ph->count)
			i = 0;
	}
	return (0);
}

int	ft_free(t_param *ph)
{

	if (ph->threads)
		free(ph->threads);
	if (ph->fork)
		free(ph->fork);
	if (ph->philos)
	 	free(ph->philos);
	// if (ph->print)
	// 	free(ph->print);
	// if (ph->m_died)
	// 	free(ph->m_died);
	return (0);

}

int	main(int argc, char **argv)
{
	t_param		param;
	pthread_t	threads_stop;
//	int 		count;
	int			i;

	i = 0;
	param.n = 0;
	if (ft_check(argc, argv))
	{
		if (ft_init_struct(argc, argv, &param))
			return (0);
		param.t_s = ft_time_now();
		pthread_create(&threads_stop, NULL, ft_stop, &param);
		pthread_detach(threads_stop);
		while (param.n < param.count)
		{
			pthread_create(&param.threads[i], NULL, ft_eat, &param);
			usleep(50);
		//	pthread_detach(param.threads[i]);
			param.n++;
		}
		i = 0;
	//	ft_stop(&param);

		while (i < param.count)
		{
			pthread_join(param.threads[i], NULL);
		//	printf("Hureeeeyyyy %d\n", i);
			i++;
		}

		ft_free(&param);

	}
	return (0);
}
