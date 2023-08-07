###################
# //= Variables =//
###################

NAME = cub3d
CFLAGS = -Wall -Werror -Wextra -g
# LIBFT = ./lib/libft
MLX = ./lib/minilibx_linux

CC				= gcc
AR				= ar rcs
MKDIR			= mkdir
RM				= rm -rf

# HEADERS	= -I ./include -I $(LIBMLX) -I $(LIBFT)/include -I usr/include
HEADERS	= -I ./include -I $(LIBMLX) -I usr/include

# LIBS	= -lglfw -L /usr/lib $(LIBMLX)/libmlx_Linux.a $(LIBFT)/libft.a
# LIBS	= -L /usr/lib -L$(LIBMLX) -lmlx_Linux $(LIBFT)/libft.a -ldl -lXext -lX11 -lm -lz
LIBS	= -L /usr/lib -L$(LIBMLX) -lmlx_Linux  -ldl -lXext -lX11 -lm -lz

BOLD	= \033[1m
BLACK	= \033[30;1m
RED	= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

TSEP			= ${SEP}=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=${RESET}

###############
# //= Files =//
###############

SRC = 	key \
		main \
		parsing \
		parsing_tools \
		parsing_map \
		parsing_check \
		screen_utils \
		screen \
		sprite \
		gnl \
		utils \

FIL = $(addsuffix .c, $(addprefix src/, $(SRC)))

OBJ = $(FIL:.c=.o)

###############
# //= CMD =//
###############

all:			${NAME}

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(CC) -o $(NAME) -L $(MLX) $(CFLAGS) $(OBJ)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJ)
	rm -f bitmap.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all