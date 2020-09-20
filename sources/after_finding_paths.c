/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_finding_paths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:56:53 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:56:56 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		sort_paths(t_path **paths, int paths_amount)
{
	int			i;
	t_path		*temp;

	if (!paths || !paths_amount)
		ft_error("invalid map");
	i = -1;
	while (++i < (paths_amount - 1))
	{
		if (paths[i]->current->steps > paths[i + 1]->current->steps)
		{
			temp = paths[i];
			paths[i] = paths[i + 1];
			paths[i + 1] = temp;
			i = -1;
		}
	}
}

t_path			**make_path_array(t_main *main)
{
	t_path		*start;
	t_path		**result;
	int			paths_amount;
	int			i;

	i = -1;
	start = main->paths;
	paths_amount = 0;
	while (start)
	{
		paths_amount++;
		start = start->next;
	}
	main->paths_amount = paths_amount;
	start = main->paths;
	if (!(result = (t_path**)ft_memalloc(sizeof(t_path*) * paths_amount)))
		ft_error("FAILED TO ALLOC PATH ARRAY");
	while (++i < paths_amount)
	{
		result[i] = start;
		start = start->next;
	}
	sort_paths(result, paths_amount);
	return (result);
}

void			count_steps(t_main *map)
{
	t_room		*current;
	t_room		*room;
	int			steps;
	t_path		*f;

	f = map->paths;
	while (f)
	{
		steps = 0;
		current = f->current;
		room = current;
		while (current->where)
		{
			steps += 1;
			current = current->where;
		}
		while (room->where)
		{
			room->steps = steps;
			room = room->where;
		}
		f = f->next;
	}
}
