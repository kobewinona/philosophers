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
	int	i;

	i = 0;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	pthread_t	*threads;

	if (argc != 6)
		handle_error(NULL, NOT_ENOUGH_ARGS_ERR);
	if (is_argv_valid((argc - 1), (argv + 1)) == false)
		handle_error(NULL, INVALID_ARGS_ERR);
	return (EXIT_SUCCESS);
}