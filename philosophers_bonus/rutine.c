/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:56:24 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/18 20:09:26 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->fork);
	ft_mensage(philo, 1);
	sem_wait(philo->fork);
	ft_mensage(philo, 1);
	ft_mensage(philo, 2);
	ft_change_long(&philo->lock_start_time,
		&philo->start_time, ft_get_current_time());
	ft_pause_milis(philo->time_to_eat);
	sem_post(philo->fork);
	sem_post(philo->fork);
	philo->meals_eaten++;
}

void	ft_sleep(t_philo *philo)
{
	ft_mensage(philo, 3);
	ft_pause_milis(philo->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_mensage(philo, 4);
}

void	ft_finish_proces(pid_t	*pid, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
}

void	ft_pause_milis(long long milis)
{
	usleep(milis * 1000);
}
