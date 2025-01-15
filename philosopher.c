/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:28:55 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/15 18:12:30 by jdhallen         ###   ########.fr       */
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
	printf("%li %i has taken a fork\n", time_dif(gettime(), arg->table->start), arg->table->chair[arg->id].philo.id);
	arg->table->chair[id].fork.state = 'o';
	return (0);
}

int	lunch(t_parg *arg)
{
	if (search_fork(arg, arg->id) == -1)
		return (-1);
	if (search_fork(arg, (arg->id + 1) % arg->table->philo_n) == -1)
		return (-1);
	arg->table->chair[arg->id].philo.state = 'e';
	printf("%li %i is eating\n", time_dif(gettime(), arg->table->start), arg->table->chair[arg->id].philo.id);
	usleep(arg->table->lunch_t * 1000);
	pthread_mutex_unlock(&arg->table->chair[arg->id].fork.fork_mutex);
	pthread_mutex_unlock(&arg->table->chair[(arg->id + 1) % arg->table->philo_n].fork.fork_mutex);
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

void	sleepy(t_parg *arg)
{
	printf("%li %i is sleeping\n", time_dif(gettime(), arg->table->start), arg->table->chair[arg->id].philo.id);
	arg->table->chair[arg->id].philo.state = 's';
	usleep(arg->table->sleep_t * 1000);
}

void	think(t_parg *arg)
{
	printf("%li %i is thinking\n", time_dif(gettime(), arg->table->start), arg->table->chair[arg->id].philo.id);
	arg->table->chair[arg->id].philo.state = 't';
}

void	*philo_life(void *args)
{
	t_parg	*arg;

	arg = (t_parg *)args;
	// printf("Hi, I am philosopher %i\n", arg->table->chair[arg->id].philo.id);
	while (death_condition(arg) == 0)
	{
		if (arg->table->end == 1)
			return (arg->table->chair[arg->id].philo.end.finish = 1, free(arg), NULL);
		if (arg->table->chair[arg->id].philo.lunch_n != -1 &&
			arg->table->lunch_n != -1 &&
			(arg->table->lunch_n ==  arg->table->chair[arg->id].philo.lunch_n))
			return (arg->table->chair[arg->id].philo.end.finish = 1, free(arg), NULL);
		if (arg->table->chair[arg->id].philo.state == 'w' || arg->table->chair[arg->id].philo.state == 't')
		{
			if (eat(arg) == -1)
				break ;
		}
		else if (arg->table->chair[arg->id].philo.state == 'e')
			sleepy(arg);
		else if (arg->table->chair[arg->id].philo.state == 's')
			think(arg);
		arg->table->chair[arg->id].philo.gen += 1;
	}
	return (printf("%li %i died\n", time_dif(gettime(),
		arg->table->start), arg->table->chair[arg->id].philo.id),
		arg->table->chair[arg->id].philo.end.live = 0,
		arg->table->chair[arg->id].philo.end.finish = 1, free(arg),NULL);
}
