/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:18:02 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/18 14:17:49 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philosophers.h"

int	ft_malloc(t_shared_data *shared)
{
	shared->phil = malloc(sizeof(t_phil) * MAX_PHILOSOPHERS);
	if (!shared->phil)
		return (1);
	shared->forks = malloc(sizeof(pthread_mutex_t) * MAX_PHILOSOPHERS);
	if (!shared->forks)
	{
		free(shared->phil);
		return (1);
	}
	shared->threads = malloc(sizeof(pthread_t) * MAX_PHILOSOPHERS);
	if (!shared->threads)
	{
		free(shared->phil);
		free(shared->forks);
		return (1);
	}
	return (0);
}

void	clean(t_shared_data *shared)
{
	free(shared->phil);
	free(shared->forks);
	free(shared->threads);
}
