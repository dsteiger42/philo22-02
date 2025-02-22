/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:20:57 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/18 14:18:35 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philosophers.h"

int	check_death(t_phil *phil)
{
	long long	current_time;

	pthread_mutex_lock(phil->print_mutex);
	current_time = get_current_time();
	if (current_time - phil->last_meal_time > phil->time_to_die)
	{
		if (get_simulation_running(phil))
		{
			printf("%s%lld %d died%s\n", RED, current_time - phil->start_time,
				phil->id, RESET);
			set_simulation_running(phil, 0);
			pthread_mutex_unlock(phil->print_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(phil->print_mutex);
	return (0);
}

int	get_simulation_running(t_phil *phil)
{
	int	value;

	pthread_mutex_lock(phil->simulation_mutex);
	value = *phil->simulation_running;
	pthread_mutex_unlock(phil->simulation_mutex);
	return (value);
}

void	set_simulation_running(t_phil *phil, int value)
{
	pthread_mutex_lock(phil->simulation_mutex);
	*phil->simulation_running = value;
	pthread_mutex_unlock(phil->simulation_mutex);
}
