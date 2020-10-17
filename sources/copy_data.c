/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:04:55 by cyuriko           #+#    #+#             */
/*   Updated: 2020/10/17 19:04:57 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		copy_start_end(t_main *source, t_main *dest)
{
	t_room *dest_rooms;

	dest_rooms = dest->all_rooms_here;
	while (dest_rooms)
	{
		if (ft_strequ(dest_rooms->name, source->start->name))
			dest->start = dest_rooms;
		if (ft_strequ(dest_rooms->name, source->end->name))
			dest->end = dest_rooms;
		dest_rooms = dest_rooms->next;
	}
	if (dest->start == dest->end || !dest->start || !dest->end)
		ft_error("something wrong with rooms");
}

static t_room	*copy_room(t_room *source)
{
	t_room *result;

	if (!(result = (t_room*)ft_memalloc(sizeof(t_room))))
		return (NULL);
	result->name = ft_strdup(source->name);
	if (!result->name)
	{
		free(result);
		return (NULL);
	}
	result->x = source->x;
	result->y = source->y;
	return (result);
}

static t_room	*copy_roomz(t_main *source)
{
	t_room *counter;
	t_room *result;
	t_room *result_counter;

	counter = source->all_rooms_here;
	if (!(result = copy_room(counter)))
		ft_error("malloc failed");
	result_counter = result;
	counter = counter->next;
	while (counter)
	{
		result_counter->next = copy_room(counter);
		if (!result_counter->next)
			ft_error("malloc failed");
		result_counter = result_counter->next;
		counter = counter->next;
	}
	return (result);
}

static void		copy_rest(t_main *source, t_main *result)
{
	t_room *finder;

	if (!source || !result)
		ft_error("something wrong at copying");
	finder = result->all_rooms_here;
	result->ants = source->ants;
	result->original_ants = source->original_ants;
	copy_start_end(source, result);
	ant_colony_creation(result->ants, result);
	result->report = source->report;
	while (finder)
	{
		if (ft_strequ(finder->name, source->start->name))
			result->start = finder;
		if (ft_strequ(finder->name, source->end->name))
			result->end = finder;
		if (result->start && result->end)
			break ;
		finder = finder->next;
	}
}

t_main			*copy_data(t_main *source)
{
	t_main *result;

	result = NULL;
	if (!source)
		ft_error("something went wrong so i'm exiting safely kek");
	if (!(result = (t_main*)ft_memalloc(sizeof(t_main))))
		return (NULL);
	result->all_rooms_here = copy_roomz(source);
	result->all_links_here = copy_linkz(source, result->all_rooms_here);
	copy_rest(source, result);
	return (result);
}
