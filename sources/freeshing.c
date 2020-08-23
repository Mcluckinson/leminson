
#include "lemin.h"

/*
 * потом добавить чистку комнат и муравьев, тк если все збс при считывании, то
 * нужно будет все фришить в конце программы
 */

void		free_map(t_main *map)
{
	if (map)
		free(map);
}

void		free_rooms(t_room *room)
{
	if (!room)
		return ;
	while(room->next)
		free_rooms(room->next);////////а room?
	if (room->name)
		free(room->name);
	free(room);
}

void		free_split(char **split)
{
	int		i;

	i = 0;
	if (split)
	{
		while(split[i])
		{
			ft_strdel(&split[i]);
			i++;
		}
		free(split);
	}
	split = NULL;
}

void			free_path(t_room *current, t_main *map)
{
	t_room		*tmp;

	while (current && current->where != map->end)
	{
		if (current)
		{
			if (current->where)
				current->where->from = NULL;
		}
		tmp = current->where;
		current->where = NULL;
		current->from = NULL;
		current = tmp;
	}
	if (current)
		current->from = NULL;
}