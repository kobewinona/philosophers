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
# define ERROR 0
# define FAILURE 1
# define SUCCESS 2

# define MS_PER_SEC 1000
# define US_PER_SEC 1000000
# define US_PER_MS 1000

// error messages
# define DEFAULT_ERR_CTX "Error"
# define NOT_ENOUGH_ARGS_ERR "Not enough arguments provided\n"
# define INVALID_ARGS_ERR "Provided arguments are not valid\n"
# define UNKNOWN_ERR "Unknown error occurred\n"

// timestamp messages
# define THINK "is thinking\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define DIE "died\n"

# define FORK "has taken a fork\n"
# define LEFT_FORK "has taken left fork\n"
# define RIGHT_FORK "has taken right fork\n"

typedef struct s_fork
{
	bool			is_free;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_status
{
	pthread_mutex_t	mutex;
	int				is_philosopher_dead;
}	t_status;

typedef struct s_philo
{
	int				id;
	t_status		*shared_status;
	struct timeval	last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_meals;
}	t_philo;

// functions
// /src
int		init_sim(t_philo **philosophers, t_fork **forks,
			pthread_t **threads, char **argv);
void	*philosopher_routine(void *arg);

int		try_take_forks(t_philo *philosopher);
void	release_forks(t_fork **right_fork, t_fork **left_fork);

int		is_philosopher_dead(t_philo *philosopher);
void	*handle_death(t_philo *philosopher);

void	print_timestamp(int id, char *message);
void	print_timestamp2(int id, char *message, long context_time);

// /utils
int		ft_atoi(const char *str);

#endif
