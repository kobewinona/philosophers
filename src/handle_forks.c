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

//void	release_forks(t_fork **right_fork, t_fork **left_fork)
//{
////	pthread_mutex_lock(&((*right_fork)->mutex));
////	(*right_fork)->is_free = true;
//	pthread_mutex_unlock(&((*right_fork)->mutex));
////	pthread_mutex_lock(&((*left_fork)->mutex));
////	(*left_fork)->is_free = true;
//	pthread_mutex_unlock(&((*left_fork)->mutex));
//}
//
//static int	try_take_right_fork(t_fork **right_fork, t_philo *philo)
//{
//	pthread_mutex_lock(&((*right_fork)->mutex));
//	if ((*right_fork)->is_free && !philo->sim_status->should_stop)
//	{
//		(*right_fork)->is_free = false;
//		pthread_mutex_unlock(&((*right_fork)->mutex));
//		return (SUCCESS);
//	}
//	pthread_mutex_unlock(&((*right_fork)->mutex));
//	return (FAILURE);
//}
//
//static int	try_take_left_fork(t_fork **left_fork, t_philo *philo)
//{
//	pthread_mutex_lock(&((*left_fork)->mutex));
//	if ((*left_fork)->is_free && !philo->sim_status->should_stop)
//	{
//		(*left_fork)->is_free = false;
//		pthread_mutex_unlock(&((*left_fork)->mutex));
//		return (SUCCESS);
//	}
//	pthread_mutex_unlock(&((*left_fork)->mutex));
//	return (FAILURE);
//}
//
//int	try_take_forks(t_philo *philo)
//{
//	int	ret_val;
//
//	ret_val = FAILURE;
//	if ((philo->id % 2) != 0)
//	{
//		if (try_take_right_fork(&philo->right_fork, philo) == SUCCESS)
//		{
//			if (try_take_left_fork(&philo->left_fork, philo) == SUCCESS)
//				ret_val = SUCCESS;
//			else
//				release_forks(&philo->right_fork, &philo->left_fork);
//		}
//	}
//	else
//	{
//		if (try_take_left_fork(&philo->left_fork, philo) == SUCCESS)
//		{
//			if (try_take_right_fork(&philo->right_fork, philo) == SUCCESS)
//				ret_val = SUCCESS;
//			else
//				release_forks(&philo->right_fork, &philo->left_fork);
//		}
//	}
//	return (ret_val);
//}

void	release_forks(t_fork **right_fork, t_fork **left_fork)
{
	(*right_fork)->is_free = true;
	pthread_mutex_unlock(&((*right_fork)->mutex));
	(*left_fork)->is_free = true;
	pthread_mutex_unlock(&((*left_fork)->mutex));
}

int	try_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->is_free = false;
//	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->is_free = false;
//	pthread_mutex_unlock(&philo->left_fork->mutex);
//	if (philo->right_fork->is_free == false)
//	{
//		pthread_mutex_unlock(&philo->right_fork->mutex);
//		return (FAILURE);
//	}
//	pthread_mutex_lock(&philo->left_fork->mutex);
//	if (philo->left_fork->is_free == false)
//	{
//		pthread_mutex_unlock(&philo->right_fork->mutex);
//		pthread_mutex_unlock(&philo->left_fork->mutex);
//		return (FAILURE);
//	}
//	philo->right_fork->is_free = false;
//	philo->left_fork->is_free = false;
	return (SUCCESS);
}
