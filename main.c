/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahyildir <ahyildir@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:49:52 by ahyildir          #+#    #+#             */
/*   Updated: 2024/06/27 15:49:53 by ahyildir         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		ft_error("Wrong amount of arguments!");
	if (parse_input(&table, av, ac))
		ft_error("An error occurred while parsing input!");
	if (start_simulation(&table))
		ft_error("An error occurred while starting the simulation!");
	return (0);
}
