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

static int	try_think(t_philo *philosopher)
{
	long			time_to_think;
	const long		min_think_time = 50;
	const double	fraction_of_life = 0.1;

	time_to_think = (long)(philosopher->time_to_die * fraction_of_life);
	if (time_to_think <= min_think_time)
		time_to_think = min_think_time;
	if (time_to_think + philosopher->time_to_eat > philosopher->time_to_die)
		time_to_think = philosopher->time_to_die - philosopher->time_to_eat;
	if (time_to_think < 1)
		return (FAILURE);
	print_timestamp2(philosopher->id, "is going to think for", time_to_think);
	fflush(stdout);
	print_timestamp(philosopher->id, THINK);
	usleep(time_to_think * US_PER_MS);
	if (is_philosopher_dead(philosopher))
		return (FAILURE);
	return (SUCCESS);
}

static int	try_eat(t_philo *philosopher)
{
	print_timestamp(philosopher->id, "is going to try to eat\n");
	if (philosopher->right_fork->is_free && philosopher->left_fork->is_free)
	{
		print_timestamp(philosopher->id, "is trying to take forks\n");
		if (try_take_forks(philosopher) == FAILURE)
		{
			print_timestamp(philosopher->id, "failed to take forks\n");
			release_forks(&philosopher->right_fork, &philosopher->left_fork);
			print_timestamp(philosopher->id, "released forks\n");
			return (FAILURE);
		}
	}
	else
	{
		print_timestamp(philosopher->id, "didn't find enough forks, poor guy(\n");
		return (FAILURE);
	}
	print_timestamp(philosopher->id, EAT);
	usleep(philosopher->time_to_eat * US_PER_MS);
	release_forks(&philosopher->right_fork, &philosopher->left_fork);
	if (is_philosopher_dead(philosopher))
		return (FAILURE);
	gettimeofday(&philosopher->last_meal, NULL);
	return (SUCCESS);
}

static int	try_sleep(t_philo *philosopher)
{
	print_timestamp(philosopher->id, SLEEP);
	usleep(philosopher->time_to_sleep * US_PER_MS);
	if (is_philosopher_dead(philosopher))
		return (FAILURE);
	return (SUCCESS);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	while (1)
	{
		if (try_eat(philosopher) == FAILURE)
		{
			if (try_think(philosopher) == FAILURE)
				return (handle_death(philosopher));
		}
		else
			philosopher->number_of_meals--;
		if (try_sleep(philosopher) == FAILURE)
			return (handle_death(philosopher));
	}
	return (NULL);
}
