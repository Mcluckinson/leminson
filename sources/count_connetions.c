/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_connetions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:57:28 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:57:30 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void count_headz(t_link *link)
{
	link->first_room->outputs++;
	link->second_room->inputs++;
}

void	count_connections(t_link *links)
{
	t_link *counter;

	counter = links;
	while (counter)
	{
		count_headz(counter);
		counter = counter->next;
	}
}
