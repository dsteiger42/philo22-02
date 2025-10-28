/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:26:05 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/18 14:18:59 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philosophers.h"

int	main(int argc, char **argv)
{
	t_shared_data	shared;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: Needs 4 or 5 arguments\n", 2);
		return (1);
	}
	if (ft_malloc(&shared))
		return (1);
	if (parsing(argc, argv, shared.phil))
		return (1);
	shared.start_time = get_current_time();
	shared.simulation_running = 1;
	if (init_mutex(&shared))
		return (clean(&shared), 1);
	assign_forks(shared.phil, &shared, shared.phil[0].phil_nbr);
	if (create_threads(shared.threads, shared.phil))
		return (1);
	monitor_phil(shared.phil);
	wait_for_threads(shared.threads, shared.phil[0].phil_nbr);
	destroy_forks(shared.forks, &shared.print_mutex, shared.phil[0].phil_nbr);
	clean(&shared);
	return (0);
}
