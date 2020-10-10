#include "lemin.h"
static void copy_start_end(t_main *source, t_main *dest)
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
static t_link *copy_link(t_link *source, t_room *all_roomz)
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

t_link *copy_linkz(t_main *source, t_room *roomz_copy)
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

static t_room *copy_room(t_room *source)
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

static t_room *copy_roomz(t_main *source)
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

static void copy_rest(t_main *source, t_main *result)
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
		{
			result->start = finder;
			break ;
		}
		finder = finder->next;
	}
	finder = result->all_rooms_here;
	while (finder)
	{
		if (ft_strequ(finder->name, source->end->name))
		{
			result->end = finder;
			break ;
		}
		finder = finder->next;
	}
}

t_main *copy_data(t_main *source)
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