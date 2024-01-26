/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:41:59 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/26 12:42:00 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO add sim start time in milliseconds and track all the actions since that time
static int	is_philosopher_dead(t_philo *philo)
{
	struct timeval	current_time;
	long			elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - philo->last_meal.tv_sec) * US_PER_SEC;
	elapsed_time += (current_time.tv_usec - philo->last_meal.tv_usec);
	if (elapsed_time >= (philo->sim_params.time_to_die * US_PER_MS))
		return (true);
	return (false);
}

static int	create_threads(t_sim **sim)
{
	int			i;
	int			j;

	(*sim)->threads = (pthread_t *)malloc(
			(*sim)->params.number_of_philosophers * sizeof(pthread_t));
	if (!(*sim)->threads)
		return (ERROR);
	i = 0;
	while (i < (*sim)->params.number_of_philosophers)
	{
		if (pthread_create(&(*sim)->threads[i], NULL, philosopher_routine,
				&(*sim)->philosophers[i]) != SUCCESS)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static void	join_threads(t_sim **sim)
{
	int	i;

	i = 0;
	while (i < (*sim)->params.number_of_philosophers)
		pthread_join((*sim)->threads[i++], NULL);
}

static int	should_sim_stop(t_sim **sim)
{
	int	i;

	i = 0;
	while (i < (*sim)->params.number_of_philosophers)
	{
		if (is_philosopher_dead(&(*sim)->philosophers[i]))
		{
			pthread_mutex_lock(&(*sim)->status.mutex);
			(*sim)->status.should_stop = true;
			pthread_mutex_unlock(&(*sim)->status.mutex);
			print_log(&(*sim)->log, (*sim)->philosophers[i].id, DIE);
			return (true);
		}
		i++;
	}
	return (false);
}

void	run_sim(t_sim **sim)
{
	int			ms_to_pause;

	ms_to_pause = (*sim)->params.time_to_die / 20;
	if (ms_to_pause > MAX_MS_TO_ANNOUNCE_DEATH || ms_to_pause <= 0)
		ms_to_pause = MAX_MS_TO_ANNOUNCE_DEATH;
	if (create_threads(&(*sim)) == ERROR)
		return ;
	while (1)
	{
		if (should_sim_stop(&(*sim)) == true)
		{
			join_threads(&(*sim));
			return ;
		}
		usleep(ms_to_pause * US_PER_MS);
	}
}
