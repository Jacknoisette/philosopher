/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:28:41 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/16 12:34:56 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

struct timeval	gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t);
}

unsigned long	time_dif(struct timeval inst, struct timeval start)
{
	return (((inst.tv_sec - start.tv_sec) * 1000)
		+ (inst.tv_usec - start.tv_usec) / 1000);
}

void	clean(t_table *table)
{
	int	i;

	i = 0;
	if (table->chair != NULL)
		free(table->chair);
}

void	printf_a(t_table *table)
{
	int	i;

	i = 0;
	while (table->philo_n > i)
	{
		printf("\nPhilosopher %i is currently %c and his fork is %c\nHe live %i gen, he ate %i time\n", table->chair[i].philo.id, table->chair[i].philo.state, table->chair[i].fork.state, table->chair[i].philo.gen, table->chair[i].philo.lunch_n);
		i++;
	}
}

long	ft_atol(const char *nptr)
{
	long	i;
	long	n;

	i = 0;
	n = 0;
	if ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
	{
		while (((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
			i++;
	}
	if (nptr[i] == '+')
		i++;
	if ((nptr[i] != '\0') && nptr[i] >= 48 && nptr[i] <= 57)
	{
		while ((nptr[i] != '\0' && nptr[i] >= 48 && nptr[i] <= 57))
		{
			n = (n * 10) + (nptr[i] - '0');
			i++;
		}
	}
	return (n);
}
