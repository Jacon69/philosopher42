/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:55:57 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/19 17:25:54 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//look value of protect params
int	ft_get(pthread_mutex_t *point, int *parameter)
{
	int	number;

	pthread_mutex_lock (point);
	number = *parameter;
	pthread_mutex_unlock (point);
	return (number);
}

//change value of protect params
void	ft_change(pthread_mutex_t *point, int *parameter, int value)
{
	pthread_mutex_lock (point);
	*parameter = value;
	pthread_mutex_unlock (point);
}

long long	ft_get_current_time(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = (te.tv_sec * 1000LL) + (te.tv_usec / 1000);
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

	time = ft_get_current_time() - philo->program->star_simulation;
	if (!ft_get (&philo->program->dead_lock, &philo->program->dead_flag))
	{
		pthread_mutex_lock (philo->print_msg);
		if (!ft_get (&philo->program->dead_lock, &philo->program->dead_flag))
		{
			if (type == 1)
				printf("%lld %i has taken a fork\n", time, philo->id);
			else if (type == 2)
				printf("%lld %i is eating\n", time, philo->id);
			else if (type == 3)
				printf("%lld %i is sleeping\n", time, philo->id);
			else if (type == 4)
				printf("%lld %i is thinking\n", time, philo->id);
		}
		pthread_mutex_unlock (philo->print_msg);
	}
	if (type == 5)
	{
		pthread_mutex_lock (philo->print_msg);
		printf("%lld %i died\n", time, philo->id);
		printf("tiempo comida %lld\n", ft_get_current_time() - philo->start_time);
		printf("comidas %d\n", philo->meals_eaten);
		printf("inicial %lld\n", ft_get_current_time() - philo->program->star_simulation);
		pthread_mutex_unlock (philo->print_msg);
	}
}
