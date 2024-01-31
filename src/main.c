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

static int	exit_with_error_message(char *err_msg)
{
	printf("Error: %s", err_msg);
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
	t_sim	*sim;

	if (argc < 5)
		exit_with_error_message(NOT_ENOUGH_ARGS_ERR);
	if (is_argv_valid((argc - 1), (argv + 1)) == false)
		exit_with_error_message(INVALID_ARGS_ERR);
	sim = (t_sim *)malloc(sizeof(t_sim));
	if (!sim)
		exit_with_error_message(UNKNOWN_ERR);
	memset(sim, 0, sizeof(t_sim));
	if (init_sim(&sim, argv) == ERROR)
	{
		handle_cleanup(&sim);
		exit_with_error_message(UNKNOWN_ERR);
	}
	run_sim(&sim);
	if (handle_cleanup(&sim) == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
