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
	t_link *counter;

	counter = links;
	while (counter)
	{
		count_headz(counter);
		counter = counter->next;
	}
}