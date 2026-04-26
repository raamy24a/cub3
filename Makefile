# **************************************************************************** #
#                                    CONFIG                                    #
# **************************************************************************** #

NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

LIBFT_DIR   = libft
MLX_DIR     = minilibx

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

INCLUDES    = -Iinclude -I$(LIBFT_DIR) -I$(MLX_DIR)

SRC_DIR     = src
OBJ_DIR     = obj

# ************************************************************************** #
#                             LISTE DES SOURCES                              #
# ************************************************************************** #

SRCS = \
	src/main.c \
	src/init.c \
	src/render.c \
	src/raycast.c \
	src/raycast_helper.c \
	src/raycast_helper_two.c \
	src/moving.c \
	src/texturing.c \
	parsing/free.c \
	parsing/check_map.c \
	parsing/ft_error.c \
	parsing/init_parse.c \
	parsing/parsing_utils.c \
	parsing/parsing.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)
	@rm -f $(NAME)

re: fclean all

san: CFLAGS += -fsanitize=address,leak
san: all

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re san valgrind