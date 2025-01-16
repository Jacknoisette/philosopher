/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:29:25 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/16 17:14:27 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	search_fork(t_parg *arg, int id)
{
	while (arg->table->chair[id].fork.state == 'o')
	{
		if (death_condition(arg) == -1)
			return (-1);
		usleep(1);
	}
	pthread_mutex_lock(&arg->table->chair[id].fork.fork_mutex);
	if (death_condition(arg) == -1)
		return (-1);
	arg->table->chair[id].fork.state = 'o';
	printf("%li %i has taken a fork\n", time_dif(gettime(), arg->table->start),
		arg->table->chair[arg->id].philo.id);
	return (0);
}

int	lunch(t_parg *arg)
{
		// || arg->table->chair[arg->id].philo.id == arg->table->philo_n - 1)
	// while (eat_condition(arg) == -1 && death_condition(arg) == 0)
	// 	usleep(1);
	// if ((arg->table->chair[arg->id].philo.id - 1) % 2 == 0)
	// {
	// 	if (search_fork(arg, (arg->id + 1) % arg->table->philo_n) == -1)
	// 		return (-1);
	// 	if (search_fork(arg, arg->id) == -1)
	// 		return (-1);
	// }
	// else
	// {
		if (search_fork(arg, arg->id) == -1)
			return (-1);
		if (search_fork(arg, (arg->id + 1) % arg->table->philo_n) == -1)
			return (-1);
	// }
	arg->table->chair[arg->id].philo.state = 'e';
	printf("%li %i is eating\n", time_dif(gettime(), arg->table->start),
		arg->table->chair[arg->id].philo.id);
	if (dsleep(arg, arg->table->lunch_t) == -1)
		return (-1);
	pthread_mutex_unlock(&arg->table->chair[arg->id].fork.fork_mutex);
	pthread_mutex_unlock(&arg->table->chair[(arg->id + 1) % arg->table->philo_n]
		.fork.fork_mutex);
	arg->table->chair[arg->id].fork.state = 'a';
	arg->table->chair[(arg->id + 1) % arg->table->philo_n].fork.state = 'a';
	return (0);
}

int	eat(t_parg *arg)
{
	if (lunch(arg) == -1)
		return (-1);
	if (arg->table->chair[arg->id].philo.lunch_n != -1)
		arg->table->chair[arg->id].philo.lunch_n += 1;
	arg->table->chair[arg->id].philo.lunch_prev = gettime();
	return (0);
}

int	sleepy(t_parg *arg)
{
	printf("%li %i is sleeping\n", time_dif(gettime(),
			arg->table->start), arg->table->chair[arg->id].philo.id);
	arg->table->chair[arg->id].philo.state = 's';
	if (dsleep(arg, arg->table->sleep_t) == -1)
		return (-1);
	return (0);
}

void	think(t_parg *arg)
{
	printf("%li %i is thinking\n", time_dif(gettime(),
			arg->table->start), arg->table->chair[arg->id].philo.id);
	arg->table->chair[arg->id].philo.state = 't';
}
