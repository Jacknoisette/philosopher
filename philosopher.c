/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:28:55 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/16 16:51:00 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	death_condition(t_parg *arg)
{
	if (time_dif(gettime(), arg->table->chair[arg->id].philo.lunch_prev)
		< arg->table->die_t)
		return (0);
	return (-1);
}

int	eat_condition(t_parg *arg)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (i < arg->table->philo_n)
	{
		if (arg->table->chair[arg->id].philo.state == 'e')
			total++;
		i++;
	}
	if (total < arg->table->philo_n)
		return (0);
	return (-1);
}

int	dsleep(t_parg *arg, int param)
{
	int	i;

	i = 0;
	while (i < param)
	{
		usleep(1000);
		if (death_condition(arg) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	philo_action(t_parg *arg)
{
	if (arg->table->chair[arg->id].philo.state == 'w'
		|| arg->table->chair[arg->id].philo.state == 't')
	{
		if (eat(arg) == -1)
			return (-1);
	}
	else if (arg->table->chair[arg->id].philo.state == 'e')
	{
		if (sleepy(arg) == -1)
			return (-1);
	}
	else if (arg->table->chair[arg->id].philo.state == 's')
		think(arg);
	arg->table->chair[arg->id].philo.gen += 1;
	return (0);
}

void	*philo_life(void *args)
{
	t_parg	*arg;

	arg = (t_parg *)args;
	while (death_condition(arg) == 0)
	{
		if (arg->table->end == 1)
		{
			printf("%li %i finish\n", time_dif(gettime(), arg->table->start),
				arg->table->chair[arg->id].philo.id);
			arg->table->chair[arg->id].philo.end.finish = 1;
			return (free(arg), NULL);
		}
		if (arg->table->chair[arg->id].philo.lunch_n != -1
			&& arg->table->lunch_n != -1
			&& (arg->table->lunch_n
				== arg->table->chair[arg->id].philo.lunch_n))
			return (arg->table->chair[arg->id].philo.end.finish = 1,
				free(arg), NULL);
		if (philo_action(arg) == -1)
			break ;
	}
	printf("\033[34m%li %i died\033[0m\n", time_dif(gettime(),
			arg->table->start), arg->table->chair[arg->id].philo.id);
	arg->table->chair[arg->id].philo.end.live = 0;
	arg->table->chair[arg->id].philo.end.finish = 1;
	return (free(arg), NULL);
}
