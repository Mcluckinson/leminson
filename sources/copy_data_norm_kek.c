/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_data_norm_kek.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:05:07 by cyuriko           #+#    #+#             */
/*   Updated: 2020/10/17 19:05:08 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_link	*copy_link(t_link *source, t_room *all_roomz)
{
	t_link *result;
	t_room *room_finder;

	room_finder = all_roomz;
	if (!(result = (t_link*)ft_memalloc(sizeof(t_link))))
		return (NULL);
	while (room_finder && (!result->first_room || !result->second_room))
	{
		if (ft_strequ(room_finder->name, source->first_room->name))
			result->first_room = room_finder;
		if (ft_strequ(room_finder->name, source->second_room->name))
			result->second_room = room_finder;
		room_finder = room_finder->next;
	}
	return (result);
}

t_link			*copy_linkz(t_main *source, t_room *roomz_copy)
{
	t_link *counter;
	t_link *result;
	t_link *result_counter;

	counter = source->all_links_here;
	if (!(result = copy_link(counter, roomz_copy)))
		ft_error("malloc failed");
	result_counter = result;
	counter = counter->next;
	while (counter)
	{
		result_counter->next = copy_link(counter, roomz_copy);
		if (!result_counter->next)
			ft_error("malloc failed");
		result_counter->next->prev = result_counter;
		result_counter = result_counter->next;
		counter = counter->next;
	}
	return (result);
}
