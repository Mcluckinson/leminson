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

//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"

/*
 * this will count amount of links entering and leaving each room
 */
static void count_headz(t_link *link)
{
	link->first_room->outputs++;
	link->second_room->inputs++;
}

void	count_connections(t_link *links)
{
	/*
	 * debug thing delete me
	 */
	int multiple_inputs_ttl = 0;
	t_link *counter;

	counter = links;
	while (counter)
	{
		count_headz(counter);
		if (counter->second_room->inputs > 1 && counter->second_room->level != END)///del me
			multiple_inputs_ttl++;//del me
		counter = counter->next;
	}
	printf("total rooms with multiple inputs: %d\n", multiple_inputs_ttl);////del me
}
