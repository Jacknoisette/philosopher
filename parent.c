/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:26:11 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/15 18:29:30 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	create_philo(t_table *table)
{
	t_parg *arg;
	int	i;
	
	i = 0;
	while (i < table->philo_n)
	{
		arg = malloc(sizeof(t_parg));
		arg->table = table;
		arg->id = i;
		pthread_create(&table->chair[i].philo.thread, NULL, philo_life, (void *)arg);
		i++;
	}
	return (0);
}

int	stop_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_n)
	{
		if (table->chair[i].philo.end.finish == 0)
			return (0);
		i++;
	}
	return (1);
}

int	destroy_philo(t_table *table)
{
	int	i;
	
	i = 0;
	while (1)
	{
		if (i == table->philo_n )
			i = 0;
		if (table->chair[i].philo.end.live == 0)
		{
			table->end = 1;
			break ;
		}
		if (stop_destroy(table) == 1)
			break ;
		usleep(1);
		i++;
	}
	i = 0;
	while (i < table->philo_n)
	{
		table->chair[i].philo.end.finish = 1;
		pthread_join(table->chair[i].philo.thread, NULL);
		i++;
	}
	i = 0;
	while (i < table->philo_n)
	{
		pthread_mutex_destroy(&table->chair[i].fork.fork_mutex);
		i++;
	}
	return (0);
}

int core(int argc, char **argv)
{
	t_table	table;
    
	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arg\n"), 0);
	if (init(&table, argc, argv) == -1)
		return (clean(&table), -1);
	create_philo(&table);
	destroy_philo(&table);
	printf_a(&table);
	return (clean(&table), 0);
}