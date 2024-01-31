/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_philo_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:02:14 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/31 14:02:16 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philosopher_dead(t_philo *philo)
{
	struct timeval	curr_time;
	long			et;

	gettimeofday(&curr_time, NULL);
	pthread_mutex_lock(&philo->meal->mutex);
	if (philo->meal->is_eating)
	{
		pthread_mutex_unlock(&philo->meal->mutex);
		return (false);
	}
	et = (curr_time.tv_sec - philo->meal->last_meal.tv_sec) * US_PER_SEC;
	et += (curr_time.tv_usec - philo->meal->last_meal.tv_usec);
	pthread_mutex_unlock(&philo->meal->mutex);
	if (et >= (philo->sim_params.time_to_die * US_PER_MS))
		return (true);
	return (false);
}

bool	has_philo_ate_all_the_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal->mutex);
	if (philo->meal->number_of_meals_left != UNSPECIFIED)
	{
		if (philo->meal->number_of_meals_left == 0)
		{
			pthread_mutex_unlock(&philo->meal->mutex);
			return (true);
		}
	}
	pthread_mutex_unlock(&philo->meal->mutex);
	return (false);
}

bool	should_philosopher_stop(t_sim_status *sim_status)
{
	bool	should_stop;

	pthread_mutex_lock(&sim_status->mutex);
	should_stop = sim_status->should_stop;
	pthread_mutex_unlock(&sim_status->mutex);
	return (should_stop);
}
