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

static int	try_take_right_fork(t_fork **right_fork, int philosopher_id)
{
	if ((*right_fork)->is_free)
	{
		pthread_mutex_lock(&((*right_fork)->mutex));
		(*right_fork)->is_free = false;
		print_timestamp(philosopher_id, RIGHT_FORK);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

static int	try_take_left_fork(t_fork **left_fork, int philosopher_id)
{
	if ((*left_fork)->is_free)
	{
		pthread_mutex_lock(&((*left_fork)->mutex));
		(*left_fork)->is_free = false;
		print_timestamp(philosopher_id, LEFT_FORK);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int	try_take_forks(t_philo *philosopher)
{
	if ((philosopher->id % 2) != 0)
	{
		if (try_take_right_fork(&philosopher->right_fork,
				philosopher->id) == FAILURE)
			return (FAILURE);
		if (try_take_left_fork(&philosopher->left_fork,
				philosopher->id) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (try_take_left_fork(&philosopher->left_fork,
				philosopher->id) == FAILURE)
			return (FAILURE);
		if (try_take_right_fork(&philosopher->right_fork,
				philosopher->id) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
