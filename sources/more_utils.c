

#include "lemin.h"

int			split_bits(char *line, char c)
{
	char	**split;
	int		i;
	int		j;

	i = -1;
	j = -1;
	split = NULL;
	if (!(split = ft_strsplit(line,  c)))
		return (0);
	while (split[++i])
		continue ;
	while (split[++j])
		ft_strdel(&split[j]);
	free(split);
	return (i);
}

void		del_str_arr(char **to_delete)
{
	int		i;

	i = -1;
	if (to_delete)
	{
		while(to_delete[++i])
			ft_strdel(&to_delete[i]);
		free(to_delete);
	}
}

void		clear_reading_stuff(int fd)
{
	char *line;

	while (get_next_line(fd, &line) > 0)
	{
		if (line)
			free(line);
	}
}
