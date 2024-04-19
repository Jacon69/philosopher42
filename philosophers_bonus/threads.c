/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:35:04 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/18 20:24:40 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor(void *pointer)
{
	t_philo		*philo;
	long long	diff;

	philo = (t_philo *)pointer;
	while (1)
	{
		diff = ft_get_current_time()
			- ft_get_long(&philo->lock_start_time, &philo->start_time);
		if (diff > philo->time_to_die)
		{
			ft_mensage(philo, 5);
			sem_wait(philo->mensage);
			exit(0);
		}
	}
}

//Salida sin morirse
static void	ft_philo_rutine(t_philo *philo)
{
	if ((philo->id % 2) == 0)
		ft_pause_milis(5);
	while (1)
	{
		ft_eat(philo);
		if (philo->meals_eaten == philo->num_times_to_eat)
		{
			exit (2);
		}
		ft_sleep(philo);
		ft_think(philo);
	}
}

// el proceso del padre espera a que los hijos salgan 
//Si exit_status2 es que ha terminado de comer
void	ft_wait_father(t_program *program)
{
	int	i;	
	int	exit_status;
	int	empty;
	int	status;

	i = 0;
	exit_status = 2;
	empty = 1;
	while ((exit_status == 2) && (i < program->num_of_philos) && (empty != -1))
	{
		empty = waitpid(-1, &status, 0);
		exit_status = WEXITSTATUS(status);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status == 2)
				i++;
		}
	}
	if (++i == program->num_of_philos)
		ft_finish_proces(program->proces, program->num_of_philos);
	free(program->proces);
}

static void	ft_start_philo(t_program *program)
{
	int			i;
	pid_t		pid;
	pthread_t	observer;

	i = 0;
	while (i < program->num_of_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			program->philos[i].start_time = program->star_simulation;
			program->philos[i].star_simulation = program->star_simulation;
			pid = getpid();
			free(program->proces);
			pthread_create(&observer,
				NULL, ft_monitor, (void*) &program->philos[i]);
			ft_philo_rutine(&program->philos[i]);
			pthread_join(observer, NULL);
		}
		else
			program->proces[i] = pid;
		i++;
	}
}

int	ft_do_process(t_program *program)
{
	program->proces = malloc(sizeof(pid_t) * program->num_of_philos);
	if (!program->proces)
	{
		write(2, "Error Mem\n", 10);
		exit(1);
	}
	program->star_simulation = ft_get_current_time();
	ft_start_philo(program);
	ft_wait_father(program);
	return (0);
}
