/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:23:20 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/25 20:23:21 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philosopher_dead(t_philo *philosopher)
{
	struct timeval	current_time;
	long			elapsed_time;

	pthread_mutex_lock(&philosopher->shared_status->mutex);
	if (philosopher->shared_status->is_philosopher_dead)
	{
		pthread_mutex_unlock(&philosopher->shared_status->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philosopher->shared_status->mutex);
	gettimeofday(&current_time, NULL);
	elapsed_time = (
			current_time.tv_sec - philosopher->last_meal.tv_sec) * US_PER_SEC;
	elapsed_time += (current_time.tv_usec - philosopher->last_meal.tv_usec);
	if (elapsed_time >= (philosopher->time_to_die * US_PER_MS))
		return (true);
	return (false);
}

void	*handle_death(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->shared_status->mutex);
	if (philosopher->shared_status->is_philosopher_dead)
	{
		pthread_mutex_unlock(&philosopher->shared_status->mutex);
		return (NULL);
	}
	philosopher->shared_status->is_philosopher_dead = true;
	pthread_mutex_unlock(&philosopher->shared_status->mutex);
	print_timestamp(philosopher->id, DIE);
	return (NULL);
}
