/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:58:42 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 15:58:45 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_path	*shortest_way(t_path *paths)
{
	t_path		*tmp;
	t_path		*actual;

	tmp = paths;
	actual = paths;
	while (tmp)
	{
		if (tmp->current->steps < actual->current->steps)
			actual = tmp;
		tmp = tmp->next;
	}
	return (actual);
}

static int		go_one_way(t_main *main)
{
	int		i;
	t_path	*best_way;

	i = 0;
	best_way = shortest_way(main->paths);
	while (main->ants)
	{
		++i;
		make_oneway_step(main, best_way);
	}
	if (main->report)
	{
		ft_putstr("path completed in ");
		ft_putnbr(i);
		ft_error(" turns!");
	}
	return (0);
}

static int		go_many_ways(t_main *main)
{
	int		i;

	i = 0;
	while (main->ants)
	{
		++i;
		make_step(main);
	}
	if (main->report)
	{
		ft_putstr("path completed in ");
		ft_putnbr(i);
		ft_error(" turns!");
	}
	return (0);
}

void			lets_go(t_main *main)
{
	if (main->paths_amount == 1 || main->end_connections == 1
	|| main->start_connections == 1)
		go_one_way(main);
	else
		go_many_ways(main);
}
