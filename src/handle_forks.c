/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:20:37 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/25 21:20:37 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_fork **right_fork, t_fork **left_fork)
{
	pthread_mutex_unlock(&((*right_fork)->mutex));
	(*right_fork)->is_free = true;
	pthread_mutex_unlock(&((*left_fork)->mutex));
	(*left_fork)->is_free = true;
}

static int	try_take_right_fork(t_fork **right_fork, t_philo *philo)
{
	pthread_mutex_lock(&((*right_fork)->mutex));
	if ((*right_fork)->is_free && !philo->sim_status->should_stop)
	{
		(*right_fork)->is_free = false;
		print_log(philo->sim_log, philo->id, "has taken a right fork\n");
		return (SUCCESS);
	}
	else
	{
		pthread_mutex_unlock(&((*right_fork)->mutex));
		return (FAILURE);
	}
}

static int	try_take_left_fork(t_fork **left_fork, t_philo *philo)
{
	pthread_mutex_lock(&((*left_fork)->mutex));
	if ((*left_fork)->is_free && !philo->sim_status->should_stop)
	{
		(*left_fork)->is_free = false;
		print_log(philo->sim_log, philo->id, "has taken a left fork\n");
		return (SUCCESS);
	}
	else
	{
		pthread_mutex_unlock(&((*left_fork)->mutex));
		return (FAILURE);
	}
}

int	try_take_forks(t_philo *philo)
{
	print_log(philo->sim_log, philo->id, "is going to try to take forks\n");
	if (philo->sim_status->should_stop)
		return (FAILURE);
	if ((philo->id % 2) != 0)
	{
		if (try_take_right_fork(&philo->right_fork, philo) == FAILURE)
			return (FAILURE);
		if (try_take_left_fork(&philo->left_fork, philo) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (try_take_left_fork(&philo->left_fork, philo) == FAILURE)
			return (FAILURE);
		if (try_take_right_fork(&philo->right_fork, philo) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
