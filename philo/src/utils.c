/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:09:14 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/18 14:18:41 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philosophers.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

long	ft_atol(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (result);
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	print_status(t_phil *phil, const char *status)
{
	long long	current_time;

	if (!get_simulation_running(phil))
		return ;
	current_time = get_current_time();
	pthread_mutex_lock(phil->print_mutex);
	printf("%lld %d %s\n", current_time - phil->start_time, phil->id, status);
	pthread_mutex_unlock(phil->print_mutex);
}

void	better_usleep(t_phil *phil, long sleep_time)
{
	long long	wake_up;

	wake_up = get_current_time() + sleep_time;
	while (get_current_time() < wake_up)
	{
		if (!get_simulation_running(phil))
			break ;
		usleep(100);
	}
}
