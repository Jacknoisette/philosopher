/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:50:03 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 18:08:38 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <time.h>
# include <limits.h>

# ifndef ERROR
#  define ERROR -1
# endif

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	char			state;
}   t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	long long	lunch_prev;
	char		state;
	int			id;
	int			lunch_n;
}   t_philo;

typedef struct s_chair
{
	t_philo	philo;
	t_fork	fork;
}   t_chair;

typedef struct s_table
{
	t_chair	*chair;
	int 	philo_n;
	int 	lunch_n;
	int 	lunch_t;
	int 	die_t;
	int 	sleep_t;
}   t_table;

void 	clean(t_table *table);
int		init(t_table *table, int argc, char **argv);
int 	core(int argc, char **argv);
int		ft_atoi(const char *nptr);

#endif