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

static int	do_eat(t_philo *philo)
{
	print_log(philo->sim_log, philo->id, THINK);
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->is_thinking = false;
	pthread_mutex_lock(&philo->meal->mutex);
	philo->meal->is_eating = true;
	pthread_mutex_unlock(&philo->meal->mutex);
	print_log(philo->sim_log, philo->id, EAT);
	usleep(philo->sim_params.time_to_eat * US_PER_MS);
	pthread_mutex_lock(&philo->meal->mutex);
	philo->meal->is_eating = false;
	gettimeofday(&philo->meal->last_meal, NULL);
	if (philo->meal->number_of_meals_left != UNSPECIFIED)
		philo->meal->number_of_meals_left--;
	pthread_mutex_unlock(&philo->meal->mutex);
	pthread_mutex_unlock(&(philo->right_fork->mutex));
	pthread_mutex_unlock(&(philo->left_fork->mutex));
	return (SUCCESS);
}

static int	do_sleep(t_philo *philo)
{
	print_log(philo->sim_log, philo->id, SLEEP);
	usleep(philo->sim_params.time_to_sleep * US_PER_MS);
	return (SUCCESS);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	bool	should_continue;

	philo = (t_philo *)arg;
	should_continue = (philo->meal->number_of_meals_left == UNSPECIFIED);
	while (should_continue || philo->meal->number_of_meals_left > 0)
	{
		if (should_philosopher_stop(philo->sim_status) == true)
			return (NULL);
		do_eat(philo);
		if (should_philosopher_stop(philo->sim_status) == true)
			return (NULL);
		do_sleep(philo);
	}
	return (NULL);
}
