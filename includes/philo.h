/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:59:19 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/23 16:59:20 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

# define MS_PER_SEC 1000
# define US_PER_MS 1000

# define DEFAULT_ERR_CTX "Error"
# define NOT_ENOUGH_ARGS_ERR "Not enough arguments provided\n"
# define INVALID_ARGS_ERR "Provided arguments are not valid\n"

typedef struct s_philo
{
	int				id;
	long			time_to_die;
	long			time_to_eat;
	struct timeval	start_time;
}	t_philo;

int	ft_atoi(const char *str);

#endif
