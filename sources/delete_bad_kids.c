//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"
/*
 * this will delete links containing rooms with bad lvl and links between same-lvl rooms
 */
static bool	check_link(t_link *link)
{
	if (link)
	{
		if (link->first_room->level == -1 || link->second_room->level == -1 ||
		link->first_room->level == link->second_room->level)
			return (false);
	}
	return (true);
}

void	delete_link(t_link *link)
{
	t_link *to_delete;

	to_delete = link;
	if (link->next)
		link->next->prev = link->prev;
	if (link->prev)
		link->prev->next = link->next;
	if (!link->prev)
		link = link->next;
	if (!link->next)
		link->prev->next = NULL;
	free(to_delete);
	to_delete = NULL;
}

void 		delete_bad_kids(t_link *links)
{
	t_link *counter;

	counter = links;
	while (counter)
	{
		if (!check_link(counter))
			delete_link(counter);
		counter = counter->next;
	}
}