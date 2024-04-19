/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:59:46 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/18 20:16:56 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_current_time(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

long long	ft_atoi(char *str)
{
	long long	number;
	int			sign;

	sign = 1;
	number = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\r')
	{
		str++;
	}
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		number *= 10;
		number += *str - '0';
		str++;
	}
	return (sign * number);
}

void	ft_mensage(t_philo *philo, int type)
{
	long long	time;

	sem_wait(philo->mensage);
	time = ft_get_current_time() - philo->star_simulation;
	if (type == 1)
		printf("%lld %i has taken a fork\n", time, philo->id);
	else if (type == 2)
		printf("%lld %i is eating\n", time, philo->id);
	else if (type == 3)
		printf("%lld %i is sleeping\n", time, philo->id);
	else if (type == 4)
		printf("%lld %i is thinking\n", time, philo->id);
	else if (type == 5)
		printf("%lld %i died\n", time, philo->id);
	sem_post(philo->mensage);
}

//look value of protect params
long long	ft_get_long(pthread_mutex_t *point, long long *parameter)
{
	long long	number;

	pthread_mutex_lock (point);
	number = *parameter;
	pthread_mutex_unlock (point);
	return (number);
}

//change value of protect params
void	ft_change_long(pthread_mutex_t *point,
	long long *parameter, long long value)
{
	pthread_mutex_lock (point);
	*parameter = value;
	pthread_mutex_unlock (point);
}
