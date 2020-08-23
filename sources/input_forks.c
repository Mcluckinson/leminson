//
// Created by Carly Yuriko on 8/23/20.
//

#include "lemin.h"

static t_path **find_all_possible(t_room *room, t_link *links)
{
	int i;

	i = 0;
	while (i < room->inputs)
	{

	}
}

void delete_inputs_on_room(t_room *room, t_link *links)
{
	t_path **all_possible;

	if (!(all_possible = (t_path**)ft_memalloc(sizeof(t_path) * room->inputs)))
		ft_error("malloc failed");
	all_possible = find_all_possible();
	delete_input_friendship(all_possible);
}