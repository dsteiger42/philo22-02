/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:08:45 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/18 14:19:06 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philosophers.h"

void	ft_sleep(t_phil *phil)
{
	print_status(phil, "Is sleeping...");
	better_usleep(phil, phil->time_to_sleep);
}

void	ft_think(t_phil *phil)
{
	if (!get_simulation_running(phil))
		return ;
	print_status(phil, "is thinking");
	usleep(1000);
}

void	*one_phil(t_phil *phil)
{
	pthread_mutex_lock(phil->left_fork);
	print_status(phil, "has taken a fork");
	better_usleep(phil, phil->time_to_die);
	pthread_mutex_unlock(phil->left_fork);
	check_death(phil);
	return (NULL);
}

void	*start_routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	if (phil->phil_nbr == 1)
		return (one_phil(phil), NULL);
	while (get_simulation_running(phil))
	{
		if (check_death(phil) || (phil->meals_to_eat != -1 && phil->meals_eaten >= phil->meals_to_eat))
			break ;
		pick_forks(phil);
		if (check_death(phil))
			break ;
		print_status(phil, RED"is eating"RESET);
		pthread_mutex_lock(phil->print_mutex);
		phil->last_meal_time = get_current_time();
        phil->meals_eaten++;
		pthread_mutex_unlock(phil->print_mutex);
		better_usleep(phil, phil->time_to_eat);
		put_down_forks(phil);
		if (check_death(phil))
			break ;
		ft_sleep(phil);
		ft_think(phil);
	}
	return (NULL);
}

void	monitor_phil(t_phil *phil)
{
	int	i;
	int	all_philosophers_full;

	while (get_simulation_running(phil))
	{
		i = 0;
		all_philosophers_full = 1;
		while (i < phil[0].phil_nbr)
		{
			if (check_death(&phil[i]))
			{
				set_simulation_running(phil, 0);
				return ;
			}
			if (phil[i].meals_to_eat != -1 && phil[i].meals_eaten < phil[i].meals_to_eat)
				all_philosophers_full = 0;
			i++;
		}
		if (phil[0].meals_to_eat != -1 && all_philosophers_full)
		{
			set_simulation_running(phil, 0);
			printf("All philosophers have eaten their required meals.\n");
			return ;
		}
		usleep(1000);
	}
	return ;
}
