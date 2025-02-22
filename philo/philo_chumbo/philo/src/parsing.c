/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:09:00 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/05 13:19:54 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philosophers.h"

static int	check_int_args(char **argv, int start, int end)
{
	int		i;
	long	value;

	i = start;
	while (i <= end)
	{
		value = ft_atol(argv[i]);
		if (value <= 0 || value > INT_MAX)
		{
			ft_putstr_fd("Error: Arg should be a positive int < INT_MAX\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_phil(t_phil *phil, char **argv)
{
	phil->phil_nbr = ft_atol(argv[1]);
	phil->time_to_die = ft_atol(argv[2]);
	phil->time_to_eat = ft_atol(argv[3]);
	phil->time_to_sleep = ft_atol(argv[4]);
    phil->meals_to_eat = -1;
    if (argv[5])
        phil->meals_to_eat = ft_atol(argv[5]);
    phil->meals_eaten = 0;
	phil->last_meal_time = 0;
	phil->left_fork = NULL;
	phil->right_fork = NULL;
	phil->print_mutex = NULL;
	phil->time_to_think = phil->time_to_die - (phil->time_to_eat
			+ phil->time_to_sleep);
	if (phil->time_to_think < 0)
		phil->time_to_think = 0;
	return (0);
}

static int	valid_nbr_phil(t_phil *phil)
{
	if (phil->phil_nbr <= 0 || phil->phil_nbr > MAX_PHILOSOPHERS)
	{
		ft_putstr_fd("Error: Invalid number of phiosophers", 2);
		return (1);
	}
	return (0);
}

int	parsing(int argc, char **argv, t_phil phil[])
{
	if (check_int_args(argv, 1, argc - 1))
		return (1);
	if (init_phil(phil, argv))
		return (1);
	if (valid_nbr_phil(phil))
		return (1);
	return (0);
}
