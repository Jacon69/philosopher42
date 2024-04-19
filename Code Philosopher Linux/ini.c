/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:33:54 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/19 09:41:37 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_close_fork(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_mutex_destroy(philo[i].r_fork);
		i++;
	}
}

static void	ft_ini_philo2(t_philo *philo,
	t_program *program, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		philo[i].dead_lock = &program->dead_lock;
		philo[i].print_msg = &program->print_msg;
		philo[i].program = program;
		if (philo[i].id == program->num_of_philos)
			philo[i].l_fork = &fork[0];
		else
			philo[i].l_fork = &fork[i + 1];
		i++;
	}
}

void	ft_ini_fork(pthread_mutex_t	*fork, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&fork[i]);
			write(2, ERROR_MUTEX, 13);
			exit(1);
		}
		i++;
	}
}

//dead_flag 0 alives
void	ft_init_program(t_program *program, t_philo *philo, char *argv[])
{
	program->num_of_philos = (int) ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	program->star_simulation = 0;
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
	{
		write(2, ERROR_MUTEX, 13);
		ft_close_fork(philo);
		exit(1);
	}
	if (pthread_mutex_init(&program->print_msg, NULL) != 0)
	{
		pthread_mutex_destroy(&program->dead_lock);
		write(2, ERROR_MUTEX, 13);
		ft_close_fork(philo);
		exit(1);
	}
	if (argv[5])
		program->num_times_to_eat = (int) ft_atoi(argv[5]);
	else
		program->num_times_to_eat = INT_MAX;
	program->philos = philo;
	program->dead_flag = 0;
}

void	ft_init_philo(t_philo *philo, t_program *program, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].start_time = 0;
		if (pthread_mutex_init(&philo[i].lock_eating, NULL) != 0)
			ft_close_mutex(philo, i - 1, 0, 1);
		if (pthread_mutex_init(&philo[i].lock_meals_eaten, NULL) != 0)
			ft_close_mutex(philo, i - 1, 1, 1);
		if (pthread_mutex_init(&philo[i].lock_start_time, NULL) != 0)
			ft_close_mutex(philo, i - 1, 2, 1);
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].dead = &program->dead_flag;
		philo[i].r_fork = &fork[i];
		philo[i].num_of_philos = program->num_of_philos;
		i++;
	}
	ft_ini_philo2(philo, program, fork);
}
