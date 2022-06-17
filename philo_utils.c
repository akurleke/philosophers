/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurleke <akurleke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:33:20 by akurleke          #+#    #+#             */
/*   Updated: 2022/06/07 14:07:06 by akurleke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_atoi(const char *str)
{
	int			i;
	int			sing;
	long int	nb;

	sing = 0;
	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-')
		sing = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	if (str[i] == '\0')
		return (0);
	if (ft_check_if_digit((char *)str))
		return (0);
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nb = 10 * nb;
		nb = nb + (str[i++] - '0');
		if (nb < -2147483648 || nb > 2147483647)
			return (0);
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

int	ft_check_if_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

long	ft_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}
