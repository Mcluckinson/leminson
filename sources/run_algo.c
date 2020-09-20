/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:00:03 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 16:00:06 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Carly Yuriko on 9/19/20.
//

#include "lemin.h"

static t_main *pick_map(t_main *map1, t_main *map2)
{
	if (!map1->paths && !map2->paths)
		ft_error("no paths found");
	if (map1->paths && !map2->paths)
		return (map1);
	if (map2->paths && !map1->paths)
		return (map2);
	if (map1->paths_amount > map2->paths_amount)
		return (map1);
	if (map2->paths_amount > map1->paths_amount)
		return (map2);
	if (map1->paths->current->steps > map2->paths->current->steps)
		return (map1);
	return (map2);

}

static void	algo(t_main *map, int run)
{
	int rooms_done = 0;

	if (!run)
		rooms_done = power_levels(map);
	else
		rooms_done = power_levels_v2(map);
	delete_bad_kids(map->all_links_here, map);
	directions(map->all_links_here);
	count_connections(map->all_links_here);
	delete_worse_kids(map);
	create_paths(map);
}

t_main *run_algo(t_main *map1, t_main *map2)
{
	int run;

	run = 0;
	algo(map1, run);
	run = 1;
	algo(map2, run);
	return (pick_map(map1, map2));
}
