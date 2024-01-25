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

#include "philo.h"

static void	cleanup(t_philo **philosophers, t_fork **forks,
		pthread_t **threads, int number_of_philosophers)
{
	int	i;

	print_timestamp(philosophers[0]->id, "cleaning up this mess\n");
	if ((*philosophers))
	{
		pthread_mutex_destroy(&(*philosophers)[0].shared_status->mutex);
		free((*philosophers));
	}
	if (forks && (*forks))
	{
		i = 0;
		while (i < number_of_philosophers)
		{
			pthread_mutex_destroy(&(*forks)[i].mutex);
			i++;
		}
		free((*forks));
	}
	if (threads && (*threads))
		free((*threads));
}

static int	exit_with_error_message(char *err_msg)
{
	printf("%s: %s", DEFAULT_ERR_CTX, err_msg);
	exit(EXIT_FAILURE);
}

static int	is_argv_valid(int argc, char **argv)
{
	while (argc--)
	{
		if (ft_atoi(argv[argc]) <= 0)
			return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	int			number_of_philosophers;
	pthread_t	*threads;
	t_philo		*philosophers;
	t_fork		*forks;

	if (argc < 5)
		exit_with_error_message(NOT_ENOUGH_ARGS_ERR);
	if (is_argv_valid((argc - 1), (argv + 1)) == false)
		exit_with_error_message(INVALID_ARGS_ERR);
	number_of_philosophers = ft_atoi(argv[1]);
	if (init_sim(&philosophers, &forks, &threads, argv) == ERROR)
	{
		cleanup(&philosophers, &forks, &threads, number_of_philosophers);
		exit_with_error_message(UNKNOWN_ERR);
	}
	cleanup(&philosophers, &forks, &threads, number_of_philosophers);
	return (EXIT_SUCCESS);
}
