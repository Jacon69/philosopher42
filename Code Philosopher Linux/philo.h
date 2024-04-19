/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jconde-a <jconde-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:33:52 by jconde-a          #+#    #+#             */
/*   Updated: 2024/04/19 16:38:21 by jconde-a         ###   ########.fr       */
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

# define PHILO_MAX 201
# define ERROR_ARG "Error number argument \n"
# define ERROR_MALLOC "Error malloc \n"
# define ERROR_THREAD "Error thread \n"
# define ERROR_MUTEX "Error mutex \n"
# define ERROR_NUM "Invalid Arguments. Only possitive numbers\n"

typedef struct s_philo		t_philo;
typedef struct s_program	t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;	
	pthread_mutex_t	lock_eating;
	pthread_mutex_t	lock_meals_eaten;
	pthread_mutex_t	lock_start_time;
	int				eating;
	int				meals_eaten;
	long long		start_time;
	int				*dead;
	int				num_of_philos;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*print_msg;	
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	// pthread_mutex_t	*meal_lock;
	t_program		*program;

}					t_philo;

typedef struct s_program
{
	long long		time_to_die;
	long long		time_to_eat;
	long long		star_simulation;
	long long		time_to_sleep;
	int				num_of_philos;
	int				num_times_to_eat;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_msg;	
	//pthread_mutex_t	meal_lock;
	//pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

//utils
long long	ft_get_current_time(void);
long long	ft_atoi(char *str);
void		ft_mensage(t_philo *philo, int type);

//ini
void		ft_ini_fork(pthread_mutex_t	*fork, int num);
void		ft_init_program(t_program *program, t_philo *philo, char *argv[]);
void		ft_init_philo(t_philo *philo, t_program *program,
				pthread_mutex_t *fork);

//process
void		ft_do_threads(t_program *program);
void		ft_close_thread(t_philo *philo, int i);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
void		ft_dead_monitor(t_program *program, int philo);

//mutex
int			ft_get(pthread_mutex_t *point, int *parameter);
void		ft_change(pthread_mutex_t *point, int *parameter, int value);
long long	ft_get_long(pthread_mutex_t *point, long long *parameter);
void		ft_change_long(pthread_mutex_t *point,
				long long *parameter);
void		ft_close_mutex(t_philo *philo, int i, int n, int error);
void		ft_close_fork(t_philo *philo);

#endif