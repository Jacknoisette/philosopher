/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:26:11 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/13 18:09:43 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int core(int argc, char **argv)
{
	t_table	table;
    
	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arg"), 0);
	if (init(&table, argc, argv) == -1)
		return (clean(&table), -1);
	return (0);
}