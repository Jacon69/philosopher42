/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:55:15 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/19 17:18:26 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//With two forks the philo eats
static void	ft_eatfood(t_philo *philo)
{
	int	eaten;

	ft_change(&philo->lock_eating, &philo->eating, 1);
	ft_mensage(philo, 1);
	ft_change_long(&philo->lock_start_time,
		&philo->start_time);
	ft_mensage(philo, 2);
	while ((ft_get_current_time()
			- ft_get_long(&philo->lock_start_time, &philo->start_time))
		< philo->program->time_to_eat)
	{
	}
	pthread_mutex_unlock (philo->r_fork);
	pthread_mutex_unlock (philo->l_fork);
	ft_change(&philo->lock_eating, &philo->eating, 0);
	eaten = ft_get(&philo->lock_meals_eaten, &philo->meals_eaten);
	eaten = eaten + 1;
	ft_change(&philo->lock_meals_eaten, &philo->meals_eaten, eaten);
}

void	ft_eat(t_philo *philo)
{
	if (ft_get (&philo->program->dead_lock, &philo->program->dead_flag))
		return ;
	while (philo->num_of_philos == 1)
	{
		if (ft_get (&philo->program->dead_lock, &philo->program->dead_flag))
			return ;
	}
	pthread_mutex_lock (philo->r_fork);
	if (ft_get (&philo->program->dead_lock, &philo->program->dead_flag))
	{
		pthread_mutex_unlock (philo->r_fork);
		return ;
	}
	ft_mensage(philo, 1);
	pthread_mutex_lock (philo->l_fork);
	if (ft_get (&philo->program->dead_lock, &philo->program->dead_flag))
	{
		pthread_mutex_unlock (philo->r_fork);
		pthread_mutex_unlock (philo->l_fork);
		return ;
	}
	ft_eatfood(philo);
}

void	ft_sleep(t_philo *philo)
{
	long long	t_sleep;

	t_sleep = ft_get_current_time();
	if (ft_get (&philo->program->dead_lock, &philo->program->dead_flag))
		return ;
	ft_mensage(philo, 3);
	if (ft_get (&philo->program->dead_lock, &philo->program->dead_flag))
		return ;
	while ((ft_get_current_time() - t_sleep) < philo->program->time_to_sleep)
	{
	}
}

void	ft_think(t_philo *philo)
{
	ft_mensage(philo, 4);
}
