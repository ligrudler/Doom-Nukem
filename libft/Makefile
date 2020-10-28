# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 17:34:45 by gedemais          #+#    #+#              #
#    Updated: 2020/07/08 22:53:54 by gedemais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), $(OBJS), clean, fclean, re

DEF = \033[0m
GRA = \033[1m
SOU = \033[4m
BLI = \033[5m
BLA = \033[30m
RED = \033[31m
GRE = \033[32m
YEL = \033[33m
BLU = \033[34m
PUR = \033[35m
CYA = \033[36m
WHI = \033[37m
ORG = \033[1;31m

NAME = libft.a

CC = gcc

FLAGS = -Wall -Werror -Wextra

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    FLAGS += -g3 -fsanitize=address
endif

OPTI ?= 0
ifeq ($(OPTI), 1)
    FLAGS += -Ofast -march=native
endif

SRCS  =	ft_atoi.c \
		ft_atof.c\
		ft_strlcpy.c\
		ft_abs.c\
		ft_inbounds.c\
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_pctab.c \
		ft_pitab.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c\
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strmap.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strdel.c \
		ft_strncat.c \
		ft_strtrim.c \
		ft_strmapi.c \
		ft_strdup.c \
		ft_strncmp.c \
		ft_tolower.c \
		ft_strequ.c \
		ft_strncpy.c \
		ft_toupper.c \
		ft_striter.c \
		ft_strnequ.c \
		ft_striteri.c \
		ft_strnew.c \
		ft_strjoin.c \
		ft_strnstr.c \
		ft_strlcat.c \
		ft_strrchr.c \
		ft_strlen.c \
		ft_strsplit.c\
		ft_is_whitespace.c\
		ft_strrev.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_strfind.c \
		get_next_line.c \
		ft_strrealloc.c \
		ft_convert_base.c \
		ft_nblen.c \
		ft_strndup.c \
		ft_swap.c \
		ft_quicksort.c \
		ft_constrain.c \
		ft_to_degrees.c \
		ft_strwlen.c\
		ft_strclen.c\
		ft_to_radians.c\
		dynarray.c\
		dynarray_insert.c\
		dynarray_mem.c\
		dynarray_stack.c\
		ft_free_ctab.c\
		ft_tablen.c

INC=libft.h\
	get_next_line.h\
	dynarray.h

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "$(GRE)Libft successfully compiled !$(DEF)"

%.o: %.c $(INC)
	@tput civis
	@printf " Compiling $<"
	@printf "                                       \\r"
	@tput cnorm
	@$(CC) $(FLAGS) -c $<

clean: 
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

