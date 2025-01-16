/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:36:15 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/16 16:47:46 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

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
}	t_fork;

typedef struct s_end
{
	int	live;
	int	finish;
}	t_end;

typedef struct s_philo
{
	struct timeval	lunch_prev;
	pthread_t		thread;
	t_end			end;
	char			state;
	int				id;
	int				lunch_n;
	int				gen;
}	t_philo;

typedef struct s_chair
{
	t_philo	philo;
	t_fork	fork;
}	t_chair;

typedef struct s_table
{
	unsigned long	lunch_t;
	unsigned long	die_t;
	unsigned long	sleep_t;
	struct timeval	start;
	t_chair			*chair;
	int				philo_n;
	int				lunch_n;
	int				end;
}	t_table;

typedef struct s_parg
{
	t_table	*table;
	int		id;
}	t_parg;

struct timeval	gettime(void);
unsigned long	time_dif(struct timeval inst, struct timeval start);
long			ft_atol(const char *nptr);
void			clean(t_table *table);
void			printf_a(t_table *table);
void			*philo_life(void *args);
int				init(t_table *table, int argc, char **argv);
int				core(int argc, char **argv);
int				death_condition(t_parg *arg);
int				dsleep(t_parg *arg, int param);
int				search_fork(t_parg *arg, int id);
int				lunch(t_parg *arg);
int				eat(t_parg *arg);
int				sleepy(t_parg *arg);
void			think(t_parg *arg);
int				eat_condition(t_parg *arg);

#endif