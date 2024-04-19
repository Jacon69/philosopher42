/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:20:50 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/19 20:22:47 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void static	check_ini(t_program *program)
{
	if (program->mensage == SEM_FAILED)
	{
		write(2, ERROR_SEM, 16);
		sem_close(program->fork);
		sem_unlink("/forks");
		exit(1);
	}
}

void	ft_init_program(t_program *program, t_philo *philo, char *argv[])
{
	program->num_of_philos = (int) ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	program->fork = sem_open("/forks", O_CREAT, 0644, program->num_of_philos);
	program->mensage = sem_open("/mensage", O_CREAT, 0644, 1);
	if ((program->mensage == SEM_FAILED) || (program->fork == SEM_FAILED))
	{
		write(2, ERROR_SEM, 16);
		exit(1);
	}
	check_ini(program);
	sem_post(program->mensage);
	if (argv[5])
	{
		program->num_times_to_eat = (int) ft_atoi(argv[5]);
	}
	else
		program->num_times_to_eat = INT_MAX;
	program->philos = philo;
}

void	ft_error_mutex( t_program *program, t_philo *philo, int i)
{
	int	j;

	j = i;
	while (--i >= 0)
	{
		pthread_mutex_destroy(&philo[i].lock_start_time);
	}
	sem_close(program->fork);
	sem_close(program->mensage);
	sem_unlink("/forks");
	sem_unlink("/mensage");
	if (j != program->num_of_philos + 1)
	{
		write(2, ERROR_MUTEX, 18);
		exit(1);
	}
}

void	ft_init_philo(t_philo *philo, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].start_time = 0;
		if (pthread_mutex_init(&philo[i].lock_start_time, NULL) != 0)
			ft_error_mutex(program, philo, i);
		philo[i].meals_eaten = 0;
		philo[i].time_to_die = program->time_to_die;
		philo[i].time_to_eat = program->time_to_eat;
		philo[i].time_to_sleep = program->time_to_sleep;
		philo[i].num_times_to_eat = program->num_times_to_eat;
		philo[i].fork = program->fork;
		philo[i].mensage = program->mensage;
		i++;
	}
	printf("num of philos %d\n", program->num_of_philos);
	usleep (1000 * 5000);
}
