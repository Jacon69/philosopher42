/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:21:35 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/19 20:21:24 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			return (write(2, ERROR_ARG2, 42), 0);
		i++;
	}
	if (ft_atoi(argv[1]) > PHILO_MAX)
		return (write(2, ERROR_MAX, 34), 0);
	return (1);
}

void	ft_cierre(int sig)
{
	(void)sig;
	sem_unlink("/forks");
	sem_unlink("/mensage");
	write(1, "Cierre\n", 7);
	exit(0);
}

//nº philo time-died  time-eat time-sleep nºlunchs
int	main(int argn, char *argv[])
{
	t_program				program;
	t_philo					philo[PHILO_MAX];

	signal(SIGINT, ft_cierre);
	if (argn != 5 && argn != 6)
		return (write(2, ERROR_ARG, 22), 1);
	if (ft_ckc_arg(argn, argv) == 0)
		return (1);
	ft_init_program(&program, philo, argv);
	ft_init_philo(philo, &program);
	ft_do_process(&program);
	ft_error_mutex(&program, philo, program.num_of_philos + 1);
	sem_close(program.mensage);
	sem_close(program.fork);
	sem_unlink("/forks");
	sem_unlink("/mensage");
	return (0);
}
