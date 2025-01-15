/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:50:03 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/15 17:31:47 by jdhallen         ###   ########.fr       */
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

typedef struct s_end
{
	int	live;
	int	finish;
}	t_end;

typedef struct s_philo
{
	struct	timeval lunch_prev;
	pthread_t	thread;
	t_end		end;
	char		state;
	int			id;
	int			lunch_n;
	int			gen;
}   t_philo;

typedef struct s_chair
{
	t_philo	philo;
	t_fork	fork;
}   t_chair;

typedef struct s_table
{
	struct	timeval start;
	t_chair	*chair;
	int 	philo_n;
	int 	lunch_n;
	long 	lunch_t;
	long 	die_t;
	long	sleep_t;
	int		end;
}   t_table;

typedef struct s_parg
{
	t_table *table;
	int id;
}	t_parg;

struct timeval	gettime(void);
long		time_dif(struct timeval inst, struct timeval start);
long			ft_atol(const char *nptr);
void 			clean(t_table *table);
void			printf_a(t_table *table);
void			*philo_life(void *args);
int				init(t_table *table, int argc, char **argv);
int 			core(int argc, char **argv);

#endif