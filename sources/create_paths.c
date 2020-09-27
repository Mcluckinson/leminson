/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:57:41 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:57:44 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		delete_input_forks(t_main *map)
{
	t_room	*counter;
	int		lvl;

	lvl = 1;
	while (lvl <= map->max_lvl)
	{
		counter = map->all_rooms_here;
		while (counter)
		{
			if (counter->level == lvl)
				delete_input(counter, map);
			counter = counter->next;
		}
		lvl++;
	}
}

static void		delete_output_forks(t_main *map)
{
	t_room	*counter;
	int		lvl;

	lvl = map->max_lvl;
	while (lvl > 0)
	{
		counter = map->all_rooms_here;
		while (counter)
		{
			if (counter->level == lvl)
				delete_output(counter, map);
			counter = counter->next;
		}
		lvl--;
	}
}

static void		build_paths(t_main *map)
{
	build_all_paths(map);
	count_steps(map);
	if (map->paths)
	{
		if (!(map->path_array = make_path_array(map)))
			ft_error("malloc failed at building path array");
	}
}

void			create_paths(t_main *map)
{
	delete_input_forks(map);
	delete_output_forks(map);
	build_paths(map);
}
