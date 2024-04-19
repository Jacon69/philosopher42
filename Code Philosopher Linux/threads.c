/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:34:37 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/19 18:48:26 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function is part of monitor

static void	ft_moni_philo2(int i, t_program	*program)
{
	long long	now;
	long long	diff;

	now = ft_get_current_time();
	if (ft_get(&program->philos[i].lock_meals_eaten,
			&program->philos[i].meals_eaten) != 0)
		diff = now - ft_get_long(&program->philos[i].lock_start_time,
				&program->philos[i].start_time);
	else
		diff = now - program->star_simulation;
	if ((diff > program->time_to_die)
		&& (!ft_get(&program->philos[i].lock_eating,
				&program->philos[i].eating)))
		ft_dead_monitor(program, i);
}
// This function is part of monitor

static int	ft_moni_philo(int i, t_program	*program, int check)
{
	if (!ft_get(&program->philos[i].lock_eating,
			&program->philos[i].eating))
	{
		if (ft_get(&program->philos[i].lock_meals_eaten,
				&program->philos[i].meals_eaten)
			< program->num_times_to_eat)
			ft_moni_philo2(i, program);
		else
			check++;
	}
	return (check);
}

//check controls if everybody have finished to eat
static void	*ft_monitor(void *pointer)
{
	t_program	*program;
	int			i;
	int			check;

	check = 0;
	program = (t_program *)pointer;
	//while ((!ft_get (&program->dead_lock, &program->dead_flag))&& check < program->num_of_philos)
	while (check < program->num_of_philos)

	{
		i = 0;
		check = 0;
		//while ((i < program->num_of_philos) && (!ft_get (&program->dead_lock, &program->dead_flag)))
		while ((i < program->num_of_philos))
		{
			check = ft_moni_philo(i, program, check);
			if (ft_get (&program->dead_lock, &program->dead_flag))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

static void	*ft_philo_rutine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if ((philo->id % 2) == 0)
		usleep(1000);
	while ((!ft_get (&philo->program->dead_lock,
				&philo->program->dead_flag))
		&& (philo->meals_eaten
			< philo->program->num_times_to_eat))
	{
		if (!ft_get (&philo->program->dead_lock, &philo->program->dead_flag))
			ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	ft_do_threads(t_program *program)
{
	pthread_t	observer;
	int			i;

	i = 0;
	program->star_simulation = ft_get_current_time();
	while (i < program->num_of_philos)
	{
		program->philos[i].start_time = program->star_simulation;
		if (pthread_create(&program->philos[i].thread, NULL,
				ft_philo_rutine, (void*) &program->philos[i]) != 0)
			ft_close_thread(program->philos, i);
		i++;
	}
	i = 0;
	if (pthread_create(&observer, NULL, ft_monitor, (void *) program) != 0)
		ft_close_thread(program->philos, program->num_of_philos);
	while (i < program->num_of_philos)
	{
		pthread_join (program->philos[i].thread, NULL);
		i++;
	}
	pthread_join(observer, NULL);
}
