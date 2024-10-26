/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:50:11 by ahyildir          #+#    #+#             */
/*   Updated: 2024/06/27 15:50:12 by ahyildir         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->l_hand]);
	philo_msg("has taken a fork", philo->table, philo->id);
	if (philo->table->number_of_philos == 1)
		return (1);
	pthread_mutex_lock(&philo->table->forks[philo->r_hand]);
	philo_msg("has taken a fork", philo->table, philo->id);
	pthread_mutex_lock(&philo->table->die_check);
	philo_msg("is eating", philo->table, philo->id);
	philo->last_eat_time = get_current_time();
	pthread_mutex_unlock(&philo->table->die_check);
	ft_wait(philo->table->time_to_eat, philo->table);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->table->forks[philo->l_hand]);
	pthread_mutex_unlock(&philo->table->forks[philo->r_hand]);
	return (0);
}

void	*philosopher_routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->id % 2 == 1)
		usleep(15000);
	while (ph->table->is_died)
	{
		if (ph->table->is_full == 0 || ph->table->is_died == 0)
			break ;
		if (eat_meal(ph))
			return (NULL);
		philo_msg("is sleeping", ph->table, ph->id);
		ft_wait(ph->table->time_to_sleep, ph->table);
		philo_msg("is thinking", ph->table, ph->id);
	}
	return (NULL);
}

static void	check_if_dead(t_table *table)
{
	while (table->is_full)
	{
		table->i = -1;
		while (++table->i < table->number_of_philos && table->is_died)
		{
			pthread_mutex_lock(&table->die_check);
			if (time_diff(table->philo[table->i].last_eat_time,
					get_current_time()) > table->time_to_die)
			{
				philo_msg("is died", table, table->philo->id);
				table->is_died = 0;
			}
			pthread_mutex_unlock(&table->die_check);
			usleep(100);
		}
		if (table->is_died == 0)
			break ;
		table->i = 0;
		while (table->i < table->number_of_philos && table->max_meals != -1
			&& table->philo[table->i].meal_counter >= table->max_meals)
			table->i++;
		if (table->i == table->number_of_philos)
			table->is_full = 0;
	}
}

static void	clear_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philos)
		pthread_join((table->philo + i)->philos, NULL);
	i = -1;
	while (++i < table->number_of_philos)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->writing);
	pthread_mutex_destroy(&table->die_check);
	free(table->philo);
	free(table->forks);
}

int	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	table->sim_start_time = get_current_time();
	while (++i < table->number_of_philos)
	{
		if (pthread_create(&(table->philo + i)->philos, NULL,
				philosopher_routine, table->philo + i))
			return (1);
		(table->philo + i)->last_eat_time = get_current_time();
	}
	check_if_dead(table);
	clear_all(table);
	return (0);
}
