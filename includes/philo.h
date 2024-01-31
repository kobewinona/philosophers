/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:59:19 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/23 16:59:20 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

// magic numbers
# define UNSPECIFIED -2
# define ERROR -1
# define SUCCESS 0
# define FAILURE 1

# define MAX_MS_TO_ANNOUNCE_DEATH 8
# define FREQ_RATIO_TO_UPDATE_STATUS 20

# define MS_PER_SEC 1000
# define US_PER_SEC 1000000
# define US_PER_MS 1000

// error messages
# define NOT_ENOUGH_ARGS_ERR "Not enough arguments provided\n"
# define INVALID_ARGS_ERR "Provided arguments are not valid\n"
# define UNKNOWN_ERR "Unknown error occurred\n"

// timestamp messages
# define THINK "is thinking\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define DIE "died\n"

# define FORK "has taken a fork\n"

// structures

typedef struct s_sim_params
{
	int		number_of_philos;
	int		number_of_meals;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
}	t_sim_params;

typedef enum e_stop_event
{
	NO_STOP_EVENT,
	PHILO_DIED,
	NO_MEALS_LEFT,
}	t_stop_event;

typedef struct s_sim_status
{
	pthread_mutex_t	mutex;
	bool			should_stop;
	t_stop_event	stop_event;
	int				philo_id;
}	t_sim_status;

typedef struct s_sim_log
{
	pthread_mutex_t	mutex;
	struct timeval	start_time;
}	t_sim_log;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			is_free;
	bool			is_contested;
}	t_fork;

typedef struct s_meal
{
	pthread_mutex_t	mutex;
	bool			is_eating;
	int				number_of_meals_left;
	struct timeval	last_meal;
}	t_meal;

typedef struct s_philo
{
	int				id;
	t_sim_params	sim_params;
	t_sim_status	*sim_status;
	t_sim_log		*sim_log;
	t_fork			*left_fork;
	t_fork			*right_fork;
	bool			is_thinking;
	t_meal			*meal;
}	t_philo;

typedef struct s_sim
{
	t_sim_params	params;
	t_sim_status	status;
	t_sim_log		log;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		*threads;
}	t_sim;

// functions
// /src
int		init_sim(t_sim **sim, char **argv);
void	run_sim(t_sim **sim);

void	*philosopher_routine(void *arg);
bool	is_philosopher_dead(t_philo *philo);
bool	has_philo_ate_all_the_meals(t_philo *philo);
bool	should_philosopher_stop(t_sim_status *sim_status);

int		try_take_forks(t_philo *philo);
void	release_forks(t_fork **right_fork, t_fork **left_fork);

void	print_log(t_sim_log *log, int id, char *message);

int		handle_cleanup(t_sim **sim);

// /utils
int		ft_atoi(const char *str);

#endif
