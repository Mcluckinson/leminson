.PHONY: all, $(NAME), clean, fclean, re

NAME = lem-in

SRC_PATH = ./sources/
OBJ_PATH = ./objects/
INC_PATH = ./includes/
LIB_PATH = ./libft

INC = -I .  -I $(INC_PATH) -I $(LIB_PATH) -I ./ \
    		-I src/ \

FLAGS = 	-c -g -MMD -MP -Wall -Wextra -Werror

LIB = 		-L$(LIB_PATH) -lft

SRC = after_finding_paths.c ant_steps.c ants_run_like_shit.c build_path.c count_connetions.c create_paths.c\
delete_bad_kids.c delete_worse_kidz.c error_manager.c find_directions.c freeshing.c go.c input_forks.c\
lemin.c move_one_way.c output_forks.c parser_and_filling.c power_levels_v2.c power_lvl_2.c read_ants.c\
read_links.c read_rooms.c run_algo.c start_end_link.c utils.c valid.c

OBJ = $(SRC:.c=.o)

OBJ_A = $(addprefix $(OBJ_PATH),$(OBJ))

SRC_A = $(addprefix $(SRC_PATH),$(SRC))
DEP_A = $(OBJ_A:.o=.d)

all: $(NAME)

$(NAME): $(OBJ_A)
	Make -C $(LIB_PATH)
	gcc $(OBJ_A) $(INC) $(LIB) -o $(NAME)

-include $(DEP_A)
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	gcc $(FLAGS) $(INC) $< -o $@

clean:
	@clear
	@Make -C $(LIB_PATH) clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@Make -C $(LIB_PATH) fclean
	@rm -f $(NAME)

re: fclean all