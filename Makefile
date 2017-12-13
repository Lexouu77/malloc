# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/27 01:48:43 by ahamouda          #+#    #+#              #
#    Updated: 2017/12/13 19:34:35 by ahamouda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Basics.

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = clang

RM = rm -f

## Flags.

CFLAGS = -Wall -Werror -Wextra -Weverything

#SFLAGS = -Weverything
#OFLAGS = -O3 -march=native
#DFLAGS = -g3 -fsanitize=address

## Lib/Header.

HEADER_PATH = ./Includes

HEADER_FILE = malloc.h
#HEADER_FILE += malloc_struct.h ???

HEADER = $(HEADER_FILE:%.h=$(HEADER_PATH)/%.h)

#LIB = ./malloc.a

## Objects/Sources.


OBJ_PATH = Objects
OBJECTS = $(addprefix $(OBJ_PATH)/, $(SRC:%.c=%.o))

SRC_PATH = ./Sources
SRC_SUBDIR += .

SRC = end_free.c
SRC += free.c
SRC += ft_putstr.c
SRC += get_block.c
SRC += get_map_size.c
SRC += get_map_type.c
SRC += itoa_base.c
SRC += malloc.c
SRC += realloc.c
SRC += show_alloc_mem.c

vpath %.c $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))

#.SILENT:

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o $@ $< -I $(HEADER_PATH)
	ln -sf $(NAME) libft_malloc.so


$(OBJECTS): $(HEADERS) | $(OBJ_PATH)

$(OBJECTS): $(OBJ_PATH)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -I $(HEADER_PATH)

$(OBJ_PATH):
	@-mkdir -p $@

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norme:
	-@ ! norminette -R CheckTopCommentHeader $(SRC_PATH) | grep -v -B 1 "^Norme" || true
	-@ ! norminette -R CheckTopCommentHeader $(HEADER_PATH) | grep -v -B 1 "^Norme" || true

watch:
	watch "make norme" "50"

function:
	nm -u $(NAME)

.PHONY: re fclean clean norme watch function
