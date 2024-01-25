/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_timestamp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:22:47 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/25 20:22:48 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_timestamp2(int id, char *message, long context_time)
{
	struct timeval	timestamp;
	long			combined_timestamp;

	gettimeofday(&timestamp, NULL);
	combined_timestamp = timestamp.tv_sec * US_PER_SEC + timestamp.tv_usec;
	fprintf(stdout, "%ld %d %s", combined_timestamp, id, message);
	fprintf(stdout, " %ld\n", context_time);
	fflush(stdout);
}

void	print_timestamp(int id, char *message)
{
	struct timeval	timestamp;
	long			combined_timestamp;

	gettimeofday(&timestamp, NULL);
	combined_timestamp = timestamp.tv_sec * US_PER_SEC + timestamp.tv_usec;
	fprintf(stdout, "%ld %d %s\n", combined_timestamp, id, message);
	fflush(stdout);
}

//void	print_timestamp(int id, char *message)
//{
//	struct timeval	timestamp;
//	long			combined_timestamp;
//
//	gettimeofday(&timestamp, NULL);
//	combined_timestamp = timestamp.tv_sec * US_PER_SEC + timestamp.tv_usec;
//	fprintf(stdout, "%ld %d %s\n", combined_timestamp, id, message);
//	fflush(stdout);
//}
