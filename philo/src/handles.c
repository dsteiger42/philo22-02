/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:08:55 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/18 14:19:03 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philosophers.h"

int	safe_mutex_handle(pthread_mutex_t *mutex, t_mutex_op op)
{
	int	result;

	result = 0;
	if (op == MUTEX_LOCK)
		result = pthread_mutex_lock(mutex);
	else if (op == MUTEX_UNLOCK)
		result = pthread_mutex_unlock(mutex);
	else if (op == MUTEX_INIT)
		result = pthread_mutex_init(mutex, NULL);
	else if (op == MUTEX_DESTROY)
		result = pthread_mutex_destroy(mutex);
	else
	{
		ft_putstr_fd("Error: Wrong mutex operation\n", 2);
		return (-1);
	}
	if (result != 0)
	{
		ft_putstr_fd("Error: Mutex operation failed\n", 2);
		return (-1);
	}
	return (0);
}

int	init_mutex(t_shared_data *shared)
{
	int	i;

	i = -1;
	while (++i < shared->phil[0].phil_nbr)
	{
		if (safe_mutex_handle(&shared->forks[i], MUTEX_INIT) != 0)
		{
			ft_putstr_fd("Error: Failed to initialize fork mutex\n", 2);
			return (1);
		}
	}
	if (safe_mutex_handle(&shared->print_mutex, MUTEX_INIT) != 0)
	{
		ft_putstr_fd("Error: Failed to initialize print mutex\n", 2);
		return (1);
	}
	if (safe_mutex_handle(&shared->simulation_mutex, MUTEX_INIT) != 0)
	{
		ft_putstr_fd("Error: Failed to initialize simulation mutex\n", 2);
		return (1);
	}
	return (0);
}

int	safe_thread_handle(pthread_t *thread, t_thread_op op,
		void *(*start_routine)(void *), void *arg)
{
	int	result;

	result = 0;
	if (op == THREAD_CREATE)
		result = pthread_create(thread, NULL, start_routine, arg);
	else if (op == THREAD_JOIN)
		result = pthread_join(*thread, NULL);
	else if (op == THREAD_DETACH)
		result = pthread_detach(*thread);
	else
	{
		ft_putstr_fd("Error: Wrong thread operation\n", 2);
		return (-1);
	}
	if (result != 0)
	{
		ft_putstr_fd("Error: Thread operation failed\n", 2);
		return (-1);
	}
	return (0);
}

int	create_threads(pthread_t *threads, t_phil *phil)
{
	int	i;

	i = -1;
	while (++i < phil[0].phil_nbr)
	{
		if (safe_thread_handle(&threads[i], THREAD_CREATE, start_routine,
				&phil[i]) != 0)
		{
			ft_putstr_fd("Error: Failed to create thread\n", 2);
			return (1);
		}
	}
	return (0);
}

void	wait_for_threads(pthread_t *threads, int phil_nbr)
{
	int	i;

	i = 0;
	while (i < phil_nbr)
	{
		if (safe_thread_handle(&threads[i], THREAD_JOIN, NULL, NULL) != 0)
		{
			ft_putstr_fd("Error: Failed to join threads", 2);
			return ;
		}
		i++;
	}
	return ;
}
