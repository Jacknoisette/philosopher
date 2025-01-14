/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:26:11 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/14 12:35:56 by jdhallen         ###   ########.fr       */
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
		pthread_create(&table->chair[i].philo.thread, NULL, philo_test, (void *)arg);
		i++;
	}
	return (0);
}

int	destroy_philo(t_table *table)
{
	int	i;
	
	i = 0;
	while (i < table->philo_n)
	{
		pthread_join(table->chair[i].philo.thread, NULL);
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