/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:28:55 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/14 13:27:03 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <unistd.h>

void	*philo_test(void *args)
{
	struct	timeval;
	t_parg	*arg;

	arg = (t_parg *)args;
	printf("Hi, I am philosopher %i\n", arg->table->chair[arg->id].philo.id);
	while (arg->table->lunch_n > arg->table->chair[arg->id].philo.lunch_n)
	{
		if (arg->table->chair[arg->id].philo.state == 'w' || arg->table->chair[arg->id].philo.state = 't')
		{
			arg->table->chair[arg->id].philo.state = 'e';
			usleep(arg->table->lunch_t * 1000);
			arg->table->chair[arg->id].philo.lunch_n += 1;
			arg->table->chair[arg->id].philo.lunch_prev = gettimeofday(tv, NULL);
		}
	}
	return (free(arg), NULL);
}