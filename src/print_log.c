/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:31:46 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/26 19:31:47 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_sim_log *log, int id, char *message)
{
	struct timeval	timestamp;
	long			combined_timestamp;

	gettimeofday(&timestamp, NULL);
	combined_timestamp = ((timestamp.tv_sec * US_PER_SEC) + timestamp.tv_usec);
	pthread_mutex_lock(&log->mutex);
	fprintf(stdout, "%ld %d %s\n", combined_timestamp, id, message);
	fflush(stdout);
	pthread_mutex_unlock(&log->mutex);
}
