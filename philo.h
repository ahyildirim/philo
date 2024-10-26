/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:50:06 by ahyildir          #+#    #+#             */
/*   Updated: 2024/06/27 15:50:07 by ahyildir         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define DEFAULT "\033[0m"

typedef struct s_philo
{
	int				id;
	int				r_hand;
	int				l_hand;
	int				meal_counter;
	long long		last_eat_time;
	pthread_t		philos;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				is_died;
	int				is_full;
	int				i;
	long long		sim_start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	die_check;
	t_philo			*philo;
}					t_table;

void				ft_error(char *str);
void				philo_msg(char *str, t_table *table, int id);
void				ft_wait(long long wait_time, t_table *table);

int					parse_input(t_table *table, char **str, int ac);
int					start_simulation(t_table *table);

long				ft_atol(const char *str);
long long			get_current_time(void);
long long			time_diff(long long past, long long present);

#endif
