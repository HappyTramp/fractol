# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/24 09:19:49 by cacharle          #+#    #+#              #
#    Updated: 2020/02/24 09:57:58 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make
RM = rm -f

LIBFT_DIR = libft
MINILIBX_DIR = minilibx

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

OBJ_DIRS = $(shell find $(SRC_DIR) -type d | sed 's/src/obj/')

CC = gcc
CCFLAGS = -I$(LIBFT_DIR)/include -I$(MINILIBX_DIR) -I$(INCLUDE_DIR) \
		  -Wall -Wextra #-Werror
LDFLAGS = -L$(LIBFT_DIR) -lft \
		  -L$(MINILIBX_DIR) -lmlx \
		  -framework OpenGL -framework AppKit -lm

NAME = fractol
SRC_FILES = main.c \
			render.c \
			event.c \
			state.c

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INCLUDE = $(addprefix $(INCLUDE_DIR), fractol.h)

all: prebuild libft_all minilibx_all $(NAME)

bonus: all

prebuild:
	@for subdir in $(OBJ_DIRS); do mkdir -p $$subdir; done

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean: libft_clean minilibx_clean
	rm -f $(OBJ)

fclean: clean libft_fclean
	rm -f $(NAME)

re: fclean all

libft_all:
	$(MAKE) -C $(LIBFT_DIR) all

libft_clean:
	$(MAKE) -C $(LIBFT_DIR) clean

libft_fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean

minilibx_all:
	$(MAKE) -C $(MINILIBX_DIR) all

minilibx_clean:
	$(MAKE) -C $(MINILIBX_DIR) clean

