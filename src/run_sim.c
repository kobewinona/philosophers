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

static int	is_philosopher_dead(t_philo *philo)
{
	struct timeval	current_time;
	long			elapsed_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->meal->mutex);
	if (philo->meal->is_eating)
	{
		pthread_mutex_unlock(&philo->meal->mutex);
		return (false);
	}
	elapsed_time = (current_time.tv_sec - philo->meal->last_meal.tv_sec) * US_PER_SEC;
	elapsed_time += (current_time.tv_usec - philo->meal->last_meal.tv_usec);
	pthread_mutex_unlock(&philo->meal->mutex);
	if (elapsed_time >= (philo->sim_params.time_to_die * US_PER_MS))
		return (true);
	return (false);
}

static int	create_threads(t_sim **sim)
{
	int			i;

	(*sim)->threads = (pthread_t *)malloc(
			(*sim)->params.number_of_philos * sizeof(pthread_t));
	if (!(*sim)->threads)
		return (ERROR);
	i = 0;
	while (i < (*sim)->params.number_of_philos)
	{
		if (pthread_create(&(*sim)->threads[i], NULL, philosopher_routine,
				&(*sim)->philos[i]) != SUCCESS)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static void	join_threads(t_sim **sim)
{
	int	i;

	i = 0;
	while (i < (*sim)->params.number_of_philos)
		pthread_join((*sim)->threads[i++], NULL);
}

static int	should_sim_stop(t_sim **sim)
{
	int	philos_finished_their_meals;
	int	i;

	philos_finished_their_meals = 0;
	i = 0;
	while (i < (*sim)->params.number_of_philos)
	{
		pthread_mutex_lock(&(*sim)->philos[i].meal->mutex);
		if ((*sim)->philos[i].meal->number_of_meals_left != UNSPECIFIED)
		{
			if ((*sim)->philos[i].meal->number_of_meals_left == 0)
				philos_finished_their_meals++;
			pthread_mutex_unlock(&(*sim)->philos[i].meal->mutex);
			if (philos_finished_their_meals == (*sim)->params.number_of_philos)
			{
				pthread_mutex_lock(&(*sim)->status.mutex);
				(*sim)->status.should_stop = true;
				pthread_mutex_unlock(&(*sim)->status.mutex);
				return (true);
			}
		}
		if (is_philosopher_dead(&(*sim)->philos[i]))
		{
			pthread_mutex_lock(&(*sim)->status.mutex);
			(*sim)->status.should_stop = true;
			pthread_mutex_unlock(&(*sim)->status.mutex);
			print_log(&(*sim)->log, (*sim)->philos[i].id, DIE);
			return (true);
		}
		usleep(MAX_MS_TO_ANNOUNCE_DEATH * US_PER_MS / 3);
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
