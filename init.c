/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:25:52 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 18:03:47 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	chair_alloc(t_table *table)
{
	int	i;
	
	i = 0;
	table->chair = malloc(table->philo_n * sizeof(t_table));
	if (table->chair == NULL)
		return (-1);
	while (i < table->philo_n)
	{
		table->chair[i].philo.id = i + 1;
		table->chair[i].philo.lunch_n = 0;
		table->chair[i].philo.state = 'w';
		table->chair[i].philo.lunch_prev = 0;
		table->chair[i].fork.state = 'a';
	}
	return (0);
}

int	init(t_table *table, int argc, char **argv)
{
	table->philo_n = ft_atoi(argv[1]);
	table->die_t = ft_atoi(argv[2]);
	table->lunch_t = ft_atoi(argv[3]);
	table->sleep_t = ft_atoi(argv[4]);
	if (argc == 6)
		table->lunch_n = ft_atoi(argv[5]);
	else
		table->lunch_n = -1;
	if (chair_alloc(table) == -1)
		return (-1);
	return (0);
}
