/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurleke <akurleke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:21:30 by akurleke          #+#    #+#             */
/*   Updated: 2022/06/16 14:35:10 by akurleke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

//#define malloc(x) NULL

typedef struct s_philo
{
	int			number;
	int			fork_l;
	int			fork_r;
	long		time;
}	t_philo;

typedef struct s_param
{
	int				count;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				count_eat;
	int				i;
	int				n;
	int				stop;
	int				died;
	unsigned long	t_s;
	pthread_t		*threads;
 	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	m_died;
	t_philo			*philos;

}	t_param;

int	ft_check(int argc, char **argv);
int	ft_philo_atoi(const char *str);
int	ft_isdigit(int ch);
int	ft_check_if_digit(char *str);

long	ft_time_now(void);
int		ft_init_struct(int argc, char **argv, t_param *p);
void	*ft_eat(void *param);
//void	ft_stop(t_param *ph);
void	*ft_stop(void *param);

// typedef struct s_philo
// {
// 	int		name;
// 	int		left_fork;
// 	int		right_fork;
// 	long	time_e;
// }	t_philo;

// typedef struct s_args
// {
// 	int				i;
// 	int				j;
// 	int				count;
// 	int				time_die;
// 	int				time_eat;
// 	int				time_sleep;
// 	int				me;
// 	int				stop;
// 	unsigned long	st;
// 	pthread_t		*threads;
// 	pthread_mutex_t	*print;
// 	t_philo			*ph;
// }	t_args;


// void	ft_free(t_args *p);

#endif
