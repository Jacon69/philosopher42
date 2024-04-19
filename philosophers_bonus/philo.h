/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:10:43 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/19 20:22:15 by jconde-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h> 
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>
# include <dispatch/dispatch.h>

# define PHILO_MAX 201
# define ERROR_ARG "Error number argument\n"
# define ERROR_SEM "Error semaphore\n"
# define ERROR_ARG2 "Invalid Arguments. Only possitive numbers\n"
# define ERROR_MAX "Max number of philosophers is 200\n"
# define ERROR_FORK "Error creating fork\n"
# define ERROR_THREAD "Error creating thread\n"
# define ERROR_MUTEX "Error creating mutex\n"
# define ERROR_MEN "Error allocation mem\n"

struct	s_philo;
struct	s_program;

typedef struct s_program
{
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	long long				star_simulation;
	int						num_of_philos;
	int						num_times_to_eat;
	pid_t					*proces;
	sem_t					*fork;
	sem_t					*mensage;
	struct s_philo			*philos;
}					t_program;

typedef struct s_philo
{
	int						id;
	sem_t					*fork;
	sem_t					*mensage;
	int						meals_eaten;
	long long				start_time;
	long long				star_simulation;
	pthread_mutex_t			lock_start_time;
	int						dead;
	int						num_times_to_eat;
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	t_program				*program;
}					t_philo;
//utils
long long	ft_get_current_time(void);
long long	ft_atoi(char *str);
void		ft_pause_milis(long long milis);
void		ft_mensage(t_philo *philo, int type);
void		ft_finish_proces(pid_t	*pid, int num_philo);
//ini
void		ft_init_program(t_program *program, t_philo *philo, char *argv[]);
void		ft_init_philo(t_philo *philo, t_program *program);

//cierre
void		ft_error_mutex( t_program *program, t_philo *philo, int i);
//process
int			ft_do_process(t_program *program);
void		*ft_monitor(void *pointer);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);

//mutex
long long	ft_get_long(pthread_mutex_t *point, long long *parameter);
void		ft_change_long(pthread_mutex_t *point,
				long long *parameter, long long value);

#endif