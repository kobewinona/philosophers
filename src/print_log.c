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

//void	print_log(t_sim_log *log, int id, char *message)
//{
//	struct timeval	timestamp;
//	long			ms_res;
//
//	gettimeofday(&timestamp, NULL);
//	ms_res = (timestamp.tv_sec / US_PER_SEC) + (timestamp.tv_usec);
//	pthread_mutex_lock(&log->mutex);
//	printf("%ld %d %s", ms_res * US_PER_MS, id, message);
//	pthread_mutex_unlock(&log->mutex);
//}

void	print_log(t_sim_log *log, int id, char *message)
{
	struct timeval	curr_time;
	long			elapsed_ms;

	gettimeofday(&curr_time, NULL);
	elapsed_ms = (curr_time.tv_sec - log->start_time.tv_sec) * MS_PER_SEC;
	elapsed_ms += (curr_time.tv_usec - log->start_time.tv_usec) / US_PER_MS;
	pthread_mutex_lock(&log->mutex);
	printf("%ld %d %s", elapsed_ms, id, message);
	pthread_mutex_unlock(&log->mutex);
}
