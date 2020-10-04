/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_one_way.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 15:49:08 by cyuriko           #+#    #+#             */
/*   Updated: 2020/02/09 15:58:10 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	make_start_oneway_step(t_ant *ant, t_main *main, t_path *best_way)
{
	if (can_i_go_please(best_way->current))
	{
		ant->curr_room = best_way->current;
		best_way->current->ant = ant;
		print_step(ant->num, best_way->current->name, main);
		return (1);
	}
	return (0);
}

void		make_oneway_step(t_main *main, t_path *best_path)
{
	t_ant	*ant;

	ant = main->first_ant;
	while (ant != NULL)
	{
		if (ant->curr_room != main->start)
		{
			if (!can_i_go_please(ant->curr_room->where))
				break ;
			ant = make_normal_step(ant, main);
			continue ;
		}
		else if (ant->curr_room == main->start)
		{
			if (!make_start_oneway_step(ant, main, best_path))
				break ;
			ant = ant->next;
			continue ;
		}
		else if (ant->curr_room == main->end)
			ant = ant->next;
	}
	ft_putchar('\n');
}
