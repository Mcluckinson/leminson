/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:00:42 by cyuriko           #+#    #+#             */
/*   Updated: 2020/09/20 16:00:45 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>

typedef	enum		e_direction
{
	START = 0,
	END = INT_MAX
}					t_direction;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				level;
	int				steps;
	int				inputs;
	int				outputs;
	struct s_room	*where;
	struct s_room	*next;
	struct s_ant	*ant;
}					t_room;

typedef struct		s_ant
{
	int				num;
	t_room			*curr_room;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_link
{
	t_room			*first_room;
	t_room			*second_room;
	int				checked;
	struct s_link	*prev;
	struct s_link	*next;
}					t_link;

typedef struct		s_path
{
	t_room			*current;
	struct s_path	*next;
}					t_path;

typedef struct		s_main
{
	int				ants;
	int				original_ants;
	int				max_lvl;
	t_room			*start;
	t_room			*end;
	t_ant			*first_ant;
	t_room			*all_rooms_here;
	t_link			*all_links_here;
	t_path			*paths;
	t_path			**path_array;
	int				paths_amount;
	int				start_connections;
	int				end_connections;
	int				del_me_fd;
	char			*courier;
	bool			report;
}					t_main;

/*
** reading input data
*/

int					read_ants(t_main *data);
int					read_links(t_main *data);
int					read_rooms(t_main *data);

/*
** validation
*/

int					is_link(char *line);
int					is_room(char *line);
int					is_comment(char *line);
int					valid_coords(t_room *room, t_room *list);
int					duplicate_links(t_link *link, t_main *data);

void				count_steps(t_main *map);
t_path				**make_path_array(t_main *main);
void				lets_go(t_main *map);
int					can_i_go_please(t_room *room);
void				make_oneway_step(t_main *main, t_path *best_path);
void				make_step(t_main *main);
int					make_start_step(t_ant *ant, t_main *main);
t_ant				*make_normal_step(t_ant *ant, t_main *main);
void				print_step(int ant_num, char *room_name, t_main *main);
t_ant				*del_ant(t_ant *ant, t_main *main);
int					count_links(t_link *linkz);
bool				check_ants_quantity(int quantity, char *line);

/*
** utils
*/

void				del_str_arr(char **to_delete);
int					split_bits(char *line, char c);
int					is_all_digits(char *line);
int					del_line_and_return(char *line, int ret);
void				delete_bad_kids(t_link *links, t_main *map);
void				delete_worse_kids(t_main *map);
void				delete_link(t_link *links, t_main *map);
void				clear_path(t_path *path);

/*
** freeshing
*/
void				free_map(t_main *map);
void				free_rooms(t_room *room);
t_main				*parse_input(char **av, t_main *map);
t_main				*structure_filling(t_main *map);
int					ft_error(const char *error);
t_main				*ant_colony_creation(int quant, t_main *map);
void				clear_reading_stuff(int fd);

/*
** algo
*/
void				directions(t_link *links);
void				count_connections(t_link *links);
void				delete_input(t_room *room, t_main *map);
void				create_paths(t_main *map);
void				delete_output(t_room *room, t_main *map);
t_path				*build_path_with_link(t_room *room,
								t_link *link, t_main *map);
int					power_levels(t_main *map);
int					power_levels_v2(t_main *map);
t_main				*run_algo(t_main *map1, t_main *map2);
void				start_end_link(t_main *main);

#endif
