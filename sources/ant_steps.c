/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_steps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 16:47:04 by cyuriko           #+#    #+#             */
/*   Updated: 2020/02/08 14:44:36 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			make_step(t_main *main)
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
			if (!make_start_step(ant, main))
				break ;
			ant = ant->next;
			continue ;
		}
		else if (ant->curr_room == main->end)
			ant = ant->next;
	}
	ft_putchar('\n');
}

t_ant			*del_ant(t_ant *ant, t_main *main)
{
	t_ant *start;

	start = main->first_ant;
	if (ant == start)
	{
		main->first_ant = main->first_ant->next;
		ft_memdel((void*)&ant);
		ant = main->first_ant;
	}
	else
	{
		while (start->next != ant)
			start = start->next;
		if (ant->next)
			start->next = ant->next;
		ft_memdel((void*)&ant);
		ant = start->next;
	}
	main->ants--;
	return (ant);
}

t_ant			*make_normal_step(t_ant *ant, t_main *main)
{
	ant->curr_room->ant = NULL;
	ant->curr_room = ant->curr_room->where;
	print_step(ant->num, ant->curr_room->name, main);
	if (ant->curr_room == main->end)
	{
		ant = del_ant(ant, main);
		return (ant);
	}
	ant = ant->next;
	return (ant);
}
