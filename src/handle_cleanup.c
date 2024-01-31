/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:46:52 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/31 12:46:53 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	cleanup_forks(t_fork **forks, int count)
{
	int	i;

	if ((*forks))
	{
		i = 0;
		while (i < count)
		{
			if (pthread_mutex_destroy(&(*forks)[i].mutex) != SUCCESS)
				return (ERROR);
			i++;
		}
		free((*forks));
	}
	return (SUCCESS);
}

static int	cleanup_philos(t_philo **philos, int count)
{
	int	i;

	if ((*philos))
	{
		i = 0;
		while (i < count)
		{
			if (pthread_mutex_destroy(&(*philos)[i].meal->mutex) != SUCCESS)
				return (ERROR);
			free((*philos)[i].meal);
			i++;
		}
		free((*philos));
	}
	return (SUCCESS);
}

int	handle_cleanup(t_sim **sim)
{
	int	ret_val;
	int	count;

	ret_val = SUCCESS;
	count = (*sim)->params.number_of_philos;
	if (pthread_mutex_destroy(&(*sim)->status.mutex) != SUCCESS)
		ret_val = ERROR;
	if (pthread_mutex_destroy(&(*sim)->log.mutex) != SUCCESS)
		ret_val = ERROR;
	if (cleanup_forks(&(*sim)->forks, count) == ERROR)
		ret_val = ERROR;
	if (cleanup_philos(&(*sim)->philos, count) == ERROR)
		ret_val = ERROR;
	if ((*sim)->threads)
		free((*sim)->threads);
	free((*sim));
	return (ret_val);
}
