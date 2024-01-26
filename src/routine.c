/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:24:50 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/25 20:24:51 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	should_philosopher_stop(t_sim_status *sim_status)
{
	bool	should_stop;

	pthread_mutex_lock(&sim_status->mutex);
	should_stop = sim_status->should_stop;
	pthread_mutex_unlock(&sim_status->mutex);
	return (should_stop);
}

static int	try_eat(t_philo *philo)
{
	if (philo->right_fork->is_free && philo->left_fork->is_free)
	{
		if (try_take_forks(philo) == FAILURE)
		{
			print_log(philo->sim_log, philo->id, "has failed to take both forks\n");
			return (FAILURE);
		}
		else
		{
			print_log(philo->sim_log, philo->id, EAT);
			usleep(philo->sim_params.time_to_eat * US_PER_MS);
			gettimeofday(&philo->last_meal, NULL);
			if (philo->number_of_meals_left != UNSPECIFIED)
				philo->number_of_meals_left--;
			if (should_philosopher_stop(philo->sim_status) == true)
				return (FAILURE);
		}
		release_forks(&philo->right_fork, &philo->left_fork);
		print_log(philo->sim_log, philo->id, "has put down forks he took\n");
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

static int	try_think(t_philo *philo)
{
	int				time_to_die;
	int				time_to_eat;
	long			time_to_think;
	const long		min_think_time = 50;
	const double	fraction_of_life = 0.1;

	time_to_die = philo->sim_params.time_to_die;
	time_to_eat = philo->sim_params.time_to_eat;
	time_to_think = (long)(time_to_die * fraction_of_life);
	if (time_to_think <= min_think_time)
		time_to_think = min_think_time;
	if (time_to_think + time_to_die > time_to_eat)
		time_to_think = time_to_die - time_to_eat;
	if (time_to_think < 1)
		return (FAILURE);
	print_log(philo->sim_log, philo->id, THINK);
	usleep(time_to_think * US_PER_MS);
	if (should_philosopher_stop(philo->sim_status) == true)
		return (FAILURE);
	return (SUCCESS);
}

static int	try_sleep(t_philo *philo)
{
	print_log(philo->sim_log, philo->id, SLEEP);
	usleep(philo->sim_params.time_to_sleep * US_PER_MS);
	if (should_philosopher_stop(philo->sim_status) == true)
		return (FAILURE);
	return (SUCCESS);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	bool	should_continue;

	philo = (t_philo *)arg;
	should_continue = (philo->number_of_meals_left == UNSPECIFIED);
	while (should_continue || philo->number_of_meals_left > 0)
	{
		if (should_philosopher_stop(philo->sim_status) == true)
			return (NULL);
		if (try_eat(philo) == FAILURE)
		{
			if (should_philosopher_stop(philo->sim_status) == true)
				return (NULL);
			if (try_think(philo) == FAILURE)
				return (NULL);
		}
		if (should_philosopher_stop(philo->sim_status) == true)
			return (NULL);
		if (try_sleep(philo) == FAILURE)
			return (NULL);
	}
	return (NULL);
}
