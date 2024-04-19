/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 07:48:22 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/19 16:36:39 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		long long *parameter)
{
	pthread_mutex_lock (point);
	*parameter = ft_get_current_time();
	pthread_mutex_unlock (point);
}

// up death flag and send menssage 
void	ft_dead_monitor(t_program *program, int philo)
{
	int	change;

	change = 1;
	pthread_mutex_lock (&program->dead_lock);
	if (!program->dead_flag)
		program->dead_flag = 1;
	else
		change = 0;
	pthread_mutex_unlock (&program->dead_lock);
	if (change)
		ft_mensage(&program->philos[philo], 5);
}

void	ft_close_thread(t_philo *philo, int i)
{
	while (--i >= 0)
		pthread_detach(philo[i].thread);
}
