include scripts/srcs.mk
include scripts/incs.mk

NAME=doom-nukem

CC=gcc
FLAGS= -Wall -Werror -Wextra

# Flags variables
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    FLAGS += -g3 -fsanitize=address
endif

OPTI ?= 0
ifeq ($(OPTI), 1)
    FLAGS += -Ofast -march=native
endif

SRCS_PATH=srcs/
SRCS=$(addprefix $(SRCS_PATH), $(SRCS_NAME))

INCS_PATH=includes/
INCS=$(addprefix $(INCS_PATH), $(INCS_NAME))

OBJS=$(SRCS:.c=.o)

########################## Librarys ######################
MLX_PATH = mlx_opengl/
MLX = $(MLX_PATH)libmlx.a
MLX_OBJS_NAME = mlx_init_loop.o\
				mlx_int_str_to_wordtab.o\
				mlx_new_image.o\
				mlx_new_window.o\
				mlx_shaders.o\
				mlx_xpm.o

LIB_PATH = libft/
LIB = libft/libft.a

LOPENAL = $(shell pkg-config --libs openal)
IOPENAL = $(shell pkg-config --cflags openal)

LSNDFILE = $(shell pkg-config --libs sndfile)
ISNDFILE = $(shell pkg-config --cflags sndfile)

LFREETYPE = freetype-2.10.1/libfreetype.a
IFREETYPE = -Ifreetype-2.10.1/include/ 

LPNG = $(shell pkg-config --libs libpng)
IPNG = $(shell pkg-config --cflags libpng)

LBZ2 = $(shell find ~/.brew -iname libbz2.a)
IBZ2 = -I$(shell find ~/.brew -iname include | grep bzip2)

##########################################################

all: install $(NAME)

install: scripts/install.sh
	@bash scripts/install.sh

$(NAME): $(LIB) $(MLX) $(OBJS)
	$(CC) $(FLAGS) -I $(INCS_PATH) -I $(MLX_PATH) -I $(LIB_PATH) $(IBZ2) -o $(NAME) $(OBJS) $(MLX) $(LIB) $(LOPENAL) $(LSNDFILE) $(LFREETYPE) $(LPNG) $(LBZ2) -lpthread -framework OpenGL -framework AppKit

$(SRCS_PATH)%.o: $(SRCS_PATH)%.c $(INCS)
	@tput civis
	@printf " Compiling $<"
	@printf "                                       \\r"
	@tput cnorm
	@$(CC) $(FLAGS) -I $(INCS_PATH) -I$(MLX_PATH) -I$(LIB_PATH) $(IOPENAL) $(ISNDFILE) $(IFREETYPE) $(IPNG) $(IBZ2) -o $@ -c $<

$(MLX): $(MLX_PATH)
	@echo "Making MinilibX..."
	@make -C $(MLX_PATH) -j4
	@echo "MinilibX successfully compiled !"
	@echo "Making Doom_Nukem..."

$(LIB): $(LIB_PATH)
	@echo "Making Libft..."
	@make -C $(LIB_PATH) -j4

clean:
	@rm -rf $(OBJS)
	@make -C $(LIB_PATH) clean
	@echo "Libft clean"
	@make -C $(MLX_PATH) clean

fclean: clean
	@make -C $(LIB_PATH) fclean
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM

re: fclean all
