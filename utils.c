/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:28:41 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 18:08:25 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void clean(t_table *table)
{
	int	i;

	i = 0;
	if (table->chair != NULL)
		free(table->chair);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;
	int	n;

	i = 0;
	s = 0;
	n = 0;
	if ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
	{
		while (((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
			i++;
	}
	if ((nptr[i] == '+' && ++s) || (nptr[i] == '-' && --s))
		i++;
	else
		s = 1;
	if ((nptr[i] != '\0') && nptr[i] >= 48 && nptr[i] <= 57)
	{
		while ((nptr[i] != '\0' && nptr[i] >= 48 && nptr[i] <= 57))
		{
			n = (n * 10) + (nptr[i] - '0');
			i++;
		}
	}
	return (n *= s);
}