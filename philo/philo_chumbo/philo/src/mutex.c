/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:20:06 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/18 14:18:48 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philosophers.h"

void	pick_forks(t_phil *phil)
{
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->left_fork);
		print_status(phil, "has taken the right fork");
		pthread_mutex_lock(phil->right_fork);
		print_status(phil, "has taken the left fork");
	}
	else
	{
		pthread_mutex_lock(phil->right_fork);
		print_status(phil, "has taken the left fork");
		pthread_mutex_lock(phil->left_fork);
		print_status(phil, "has taken the right fork");
	}
}

void	put_down_forks(t_phil *phil)
{
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
	print_status(phil, "has put down the forks");
}

void	assign_forks(t_phil *phil, t_shared_data *shared, int phil_nbr)
{
	int	i;

	i = 0;
	while (i < phil_nbr)
	{
		phil[i] = phil[0];
		phil[i].id = i + 1;
		phil[i].left_fork = &shared->forks[i];
		phil[i].right_fork = &shared->forks[(i + 1) % phil_nbr];
		phil[i].print_mutex = &shared->print_mutex;
		phil[i].simulation_mutex = &shared->simulation_mutex;
		phil[i].last_meal_time = get_current_time();
		phil[i].start_time = shared->start_time;
		phil[i].simulation_running = &shared->simulation_running;
		i++;
	}
}

void	destroy_forks(pthread_mutex_t *forks, pthread_mutex_t *print_mutex,
		int phil_nbr)
{
	int	i;

	i = 0;
	while (i < phil_nbr)
	{
		safe_mutex_handle(&forks[i], MUTEX_DESTROY);
		i++;
	}
	safe_mutex_handle(print_mutex, MUTEX_DESTROY);
}
