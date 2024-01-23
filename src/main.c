/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:39:22 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/23 14:39:31 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	handle_error(char *err_ctx, char *err_msg)
{
	if (!err_ctx)
		printf("%s: %s", DEFAULT_ERR_CTX, err_msg);
	else
		printf("%s: %s", err_ctx, err_msg);
	exit(EXIT_FAILURE);
}

int	is_argv_valid(int argc, char **argv)
{
	while (argc--)
	{
		if (ft_atoi(argv[argc]) <= 0)
			return (false);
	}
	return (true);
}

int	is_philosopher_dead(struct timeval start_time, long time_to_die)
{
	struct timeval	current_time;
	long			elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - start_time.tv_sec) * MS_PER_SEC;
	elapsed_time += (current_time.tv_usec - start_time.tv_usec) / US_PER_MS;
	if (elapsed_time >= time_to_die)
	{
		printf("Philosopher X died\n");
		return (true);
	}
	return (false);
}

int	main(int argc, char **argv)
{
	struct timeval	start_time;
	long			time_to_die;

	if (argc < 5)
		handle_error(NULL, NOT_ENOUGH_ARGS_ERR);
	if (is_argv_valid((argc - 1), (argv + 1)) == false)
		handle_error(NULL, INVALID_ARGS_ERR);
	gettimeofday(&start_time, NULL);
	time_to_die = ft_atoi(argv[2]);
	while (1)
	{
		if (is_philosopher_dead(start_time, time_to_die))
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
