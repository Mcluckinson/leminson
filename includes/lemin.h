

#ifndef LEMIN_H
#define LEMIN_H

#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

//#define START -2
//#define END 2147483647

typedef enum
{
    NOT_SET = -1,
    START = 0,
    END = INT_MAX
} direction;

typedef struct 		s_room
{
	char 			*name;	//название комнаты?
	int 			x;		//x координата комнаты
	int 			y;		//y координата комнаты
	int 			level;  // 1 Step 1 шаг
	int 			neighbours; //количество соседей
	int 			is_dead_end; //если тупик 1
	int 			steps;
	int 			is_part_of_path;
	int 			inputs;
	int 			outputs;
	struct s_room	*where;
	struct s_room	*from;
	struct s_room	*next;
	struct s_ant	*ant;
}					t_room;

typedef struct		s_ant
{
	int 			num;		//порядковый номер муравья
	t_room 			*curr_room;	//в какой комнате он сейчас находится
	struct s_ant	*next;		//указатель на следующего муравья
//	struct s_ant	*prev;
}					t_ant;

typedef struct 		s_link////структура со связью
{
	t_room			*first_room;////название говорит за себя
	t_room			*second_room;
	bool 			checked;
	bool			is_valid;
	bool			has_pair;
	struct s_link	*prev;
	struct s_link	*next;
}					t_link;

typedef struct 		s_path
{
	t_room 			*current;
	struct s_path	*next;
}					t_path;

typedef struct		s_main
{
	int 			ants;
	int 			original_ants;
	int 			max_lvl;
	t_room			*start;
	t_room			*end;
	t_ant			*first_ant;
	t_room			*all_rooms_here;
	t_link			*all_links_here;
	t_path			*paths;
	t_path 			**path_array;
	int 			paths_amount;
	int 			start_connections;
	int				end_connections;
	int 			del_me_fd;
	char 			*courier;
}					t_main;

/**
 * reading input data
 */

int					read_ants(t_main *data);
int					read_links(t_main *data);
int					read_rooms(t_main *data);

/**
 * validation
 */

int					is_link(char *line);
int					is_room(char *line);
int					is_comment(char *line);
int					valid_coords(t_room *room, t_room *list);
int					duplicate_links(t_link *link, t_main *data);


void				*count_steps(t_main *map);
t_path				**make_path_array(t_main *main);
void				lets_go(t_main *map);
int					can_i_go_please(t_room *room);
void				make_oneway_step(t_main  *main, t_path *best_path);
void				make_step(t_main  *main, t_path **path_array);
int					make_start_step(t_ant *ant, t_main *main);
t_ant				*make_normal_step(t_ant *ant, t_main *main);
void				print_step(int ant_num, char *room_name, t_main *main);
t_ant				*del_ant(t_ant *ant, t_main *main);

/*
 * utils
 */

void				del_str_arr(char **to_delete);//////////эти функции делают одно и то же, надо бы убрать одну из них, ту, что похуже
int					split_bits(char *line, char c);
int					is_all_digits(char *line);
int					del_line_and_return(char *line, int ret);
void 				delete_bad_kids(t_link *links);
void 				delete_worse_kids(t_link *links);
void 				delete_link(t_link *links);


/**
 * freeshing
 */

void				free_rooms(t_room *room);
t_main				*parse_input(char **av, t_main *map);
t_main				*structure_filling(t_main *map);
int 				ft_error(const char *error);
t_main				*ant_colony_creation(int quant, t_main *map);

/*
 * algo
 */
void 				directions(t_link *links);
void				count_connections(t_link *links);
void 				delete_input(t_room *room, t_main *map);
void 				create_paths(t_main *map);
void 				delete_output(t_room *room, t_main *map);
t_path 				*build_path_with_link(t_room *room, t_link *link, t_main *map);
int                	power_levels(t_main *map);

#endif
