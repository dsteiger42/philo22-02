/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:09:10 by dsteiger          #+#    #+#             */
/*   Updated: 2025/02/18 14:21:46 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_PHILOSOPHERS 200
# define RED "\033[0;31m"
# define RESET "\033[0m"

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum s_mutex_op
{
	MUTEX_LOCK,
	MUTEX_UNLOCK,
	MUTEX_INIT,
	MUTEX_DESTROY
}					t_mutex_op;

typedef enum s_thread_op
{
	THREAD_CREATE,
	THREAD_JOIN,
	THREAD_DETACH
}					t_thread_op;

typedef struct s_phil
{
	int				id;
	int				phil_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
    int				meals_to_eat;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*simulation_mutex;
	int				*simulation_running;
	long long		start_time;
}					t_phil;

typedef struct s_shared_data
{
	t_phil			*phil;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	simulation_mutex;
	long long		start_time;
	int				simulation_running;
}					t_shared_data;

// actions
void				ft_sleep(t_phil *phil);
void				ft_think(t_phil *phil);
void				*one_phil(t_phil *phil);
void				*start_routine(void *arg);
void				monitor_phil(t_phil *phil);

// handles
int					safe_mutex_handle(pthread_mutex_t *mutex, t_mutex_op op);
int					init_mutex(t_shared_data *shared);
int					safe_thread_handle(pthread_t *thread, t_thread_op op,
						void *(*start_routine)(void *), void *arg);
int					create_threads(pthread_t *threads, t_phil *phil);
void				wait_for_threads(pthread_t *threads, int phil_nbr);

// malloc free
int					ft_malloc(t_shared_data *shared);
void				clean(t_shared_data *shared);

// mutex
void				pick_forks(t_phil *phil);
void				put_down_forks(t_phil *phil);
void				assign_forks(t_phil *phil, t_shared_data *shared,
						int phil_nbr);
void				destroy_forks(pthread_mutex_t *forks,
						pthread_mutex_t *print_mutex, int phil_nbr);

// parsing
int					parsing(int argc, char **argv, t_phil phil[]);

// utils
void				ft_putstr_fd(char *str, int fd);
long				ft_atol(const char *str);
long long			get_current_time(void);
void				print_status(t_phil *phil, const char *status);
void				better_usleep(t_phil *phil, long sleep_time);
int					check_death(t_phil *phil);
int					get_simulation_running(t_phil *phil);
void				set_simulation_running(t_phil *phil, int value);

#endif
