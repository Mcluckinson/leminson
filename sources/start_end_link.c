/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end_link.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:00:12 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 16:00:17 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		check_for_start_end_link(t_main *main)
{
	t_link	*go_go;

	go_go = main->all_links_here;
	while (go_go)
	{
		if ((go_go->first_room == main->start
		&& go_go->second_room == main->end)
		|| (go_go->first_room == main->end
		&& go_go->second_room == main->start))
			return (1);
		go_go = go_go->next;
	}
	return (0);
}

static void		start_end_way(t_main *main)
{
	t_ant	*ant;

	ant = main->first_ant;
	while (ant)
	{
		print_step(ant->num, main->end->name, main);
		ant = ant->next;
	}
	if (main->report)
		ft_error("ants moved in 1 step through a start-end connection!");
	exit(0);
}

void			start_end_link(t_main *main)
{
	if (check_for_start_end_link(main))
		start_end_way(main);
}
