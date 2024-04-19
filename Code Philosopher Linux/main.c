/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:33:40 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/19 09:38:47 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_close_mutex(t_philo *philo, int i, int n, int error)
{
	int	j;

	j = 0;
	ft_close_fork(philo);
	pthread_mutex_destroy(&philo->program->dead_lock);
	pthread_mutex_destroy(&philo->program->print_msg);
	if (n == 1)
		pthread_mutex_destroy(&philo[i + 1].lock_eating);
	if (n == 2)
	{
		pthread_mutex_destroy(&philo[i + 1].lock_eating);
		pthread_mutex_destroy(&philo[i + 1].lock_meals_eaten);
	}
	while (j < i)
	{
		pthread_mutex_destroy(&philo[j].lock_eating);
		pthread_mutex_destroy(&philo[j].lock_meals_eaten);
		pthread_mutex_destroy(&philo[j].lock_start_time);
		j++;
	}
	if (error == 1)
		exit(1);
}

static int	ft_check_num(char *stream)
{
	while (*stream)
	{
		if (*stream < '0' || *stream > '9')
		{
			return (0);
		}
		stream++;
	}
	return (1);
}

static int	ft_ckc_arg(int argn, char *argv[])
{
	int	i;

	i = 1;
	while (i < argn)
	{
		if (ft_check_num(argv[i]) == 0)
		{
			return (write(2, ERROR_NUM, 42), 0);
		}
		i++;
	}
	if (ft_atoi(argv[1]) > PHILO_MAX)
		return (write(2, "Too much philosophers\n", 22), 0);
	return (1);
}

//arguments: nº philo time-died  time-eat time-sleep nºlunchs
int	main(int argn, char *argv[])
{
	t_program		program;
	pthread_mutex_t	fork[PHILO_MAX];
	t_philo			philo[PHILO_MAX];
	int				i;

	if (argn != 5 && argn != 6)
		return (write(2, ERROR_ARG, 23), 1);
	if (ft_ckc_arg(argn, argv) == 0)
		return (1);
	ft_ini_fork(fork, ft_atoi(argv[1]));
	ft_init_program(&program, philo, argv);
	ft_init_philo(philo, &program, fork);
	ft_do_threads(&program);
	ft_close_mutex(philo, program.num_of_philos, 0, 0);
	pthread_mutex_destroy(&program.dead_lock);
	pthread_mutex_destroy(&program.print_msg);
	i = -1;
	while (++i < program.num_of_philos)
		pthread_mutex_destroy(&fork[i]);
	return (0);
}
