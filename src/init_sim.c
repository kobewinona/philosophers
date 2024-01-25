/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:31:27 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/24 15:31:28 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_forks(t_fork **forks, int number_of_philosophers)
{
	int		i;

	*forks = (t_fork *)malloc((number_of_philosophers + 1) * sizeof(t_fork));
	if (!(*forks))
		return (ERROR);
	i = 0;
	while (i < number_of_philosophers)
	{
		(*forks)[i].is_free = true;
		pthread_mutex_init(&(*forks)[i].mutex, NULL);
		i++;
	}
	return (SUCCESS);
}

static int	create_philosophers(t_philo **philosophers,
	t_fork **forks, t_status **status, char **argv)
{
	int		number_of_philosophers;
	int		i;

	number_of_philosophers = ft_atoi(argv[1]);
	*philosophers = (t_philo *)malloc(number_of_philosophers * sizeof(t_philo));
	if (!(*philosophers))
		return (ERROR);
	memset((*philosophers), 0, (number_of_philosophers * sizeof(t_philo)));
	i = 0;
	while (i < number_of_philosophers)
	{
		(*philosophers)[i].id = i;
		(*philosophers)[i].shared_status = (*status);
		gettimeofday(&(*philosophers)[i].last_meal, NULL);
		(*philosophers)[i].left_fork = &((*forks)[i]);
		(*philosophers)[i].right_fork = &(
				(*forks)[((i + 1) % number_of_philosophers)]);
		(*philosophers)[i].time_to_die = ft_atoi(argv[2]);
		(*philosophers)[i].time_to_eat = ft_atoi(argv[3]);
		(*philosophers)[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			(*philosophers)[i].number_of_meals = ft_atoi(argv[5]);
		i++;
	}
	return (SUCCESS);
}

static int	create_threads(pthread_t **threads,
	t_philo *context, void *routine, int count)
{
	int			i;
	int			j;

	*threads = (pthread_t *)malloc(count * sizeof(pthread_t));
	if (!(*threads))
		return (ERROR);
	i = 0;
	while (i < count)
	{
		if (pthread_create(&(*threads)[i], NULL, routine, &context[i]))
		{
			j = 0;
			while (j < i)
				pthread_cancel((*threads)[j++]);
			free((*threads));
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

static void	join_threads(pthread_t **threads, int count, t_status *status)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_lock(&status->mutex);
		if (status->is_philosopher_dead)
		{
			pthread_mutex_unlock(&status->mutex);
			break ;
		}
		pthread_mutex_unlock(&status->mutex);
		pthread_join((*threads)[i], NULL);
		i++;
	}
}

int	init_sim(t_philo **philosophers, t_fork **forks,
	pthread_t **threads, char **argv)
{
	t_status	*status;
	int			number_of_philosophers;

	number_of_philosophers = ft_atoi(argv[1]);
	*forks = NULL;
	if (create_forks(forks, number_of_philosophers) == ERROR)
		return (ERROR);
	status = (t_status *)malloc(sizeof(t_status));
	if (!status)
		return (ERROR);
	pthread_mutex_init(&status->mutex, NULL);
	status->is_philosopher_dead = false;
	*philosophers = NULL;
	if (create_philosophers(philosophers,
			forks, &status, argv) == ERROR)
	{
		return (ERROR);
	}
	*threads = NULL;
	if (create_threads(threads, (*philosophers), philosopher_routine,
			number_of_philosophers) == ERROR)
		return (ERROR);
	join_threads(threads, number_of_philosophers, status);
	return (SUCCESS);
}
