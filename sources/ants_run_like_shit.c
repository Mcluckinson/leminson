/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_run_like_shit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 18:57:50 by cyuriko           #+#    #+#             */
/*   Updated: 2020/02/09 14:16:38 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			can_i_go_please(t_room *room)
{
	if (!room->ant)
		return (1);
	return (0);
}

static int	count_delta(t_path **path_array, int i)
{
	int delta;
	int i2;

	i2 = i;
	delta = 0;
	while (i2 > 0)
		delta += (path_array[i]->current->steps -
				path_array[--i2]->current->steps);
	return (delta);
}

static int	choose_way(t_ant *ant,
						t_path **path_array, int ways_amount, int ants_amount)
{
	int i;
	int delta;

	delta = 0;
	i = -1;
	while (++i < ways_amount)
	{
		if (i)
			delta = count_delta(path_array, i);
		if (ant->num > delta && ants_amount > delta)
		{
			if (can_i_go_please(path_array[i]->current))
				return (i);
		}
	}
	return (0);
}

int			make_start_step(t_ant *ant, t_main *main)
{
	int	way;

	way = choose_way(ant, main->path_array, main->paths_amount, main->ants);
	if (can_i_go_please(main->path_array[way]->current))
	{
		ant->curr_room = main->path_array[way]->current;
		main->path_array[way]->current->ant = ant;
		print_step(ant->num, main->path_array[way]->current->name, main);
		return (1);
	}
	return (0);
}
