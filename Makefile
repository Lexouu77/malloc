# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/27 01:48:43 by ahamouda          #+#    #+#              #
#    Updated: 2017/12/17 15:54:52 by ahamouda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Basics.

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LINK = libft_malloc.so

CC = clang

RM = rm -f

## Flags.

CFLAGS = -Wall -Werror -Wextra -Weverything -fPIC

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

SRC = check_mapped_size_and_type.c
SRC += display_type_and_address.c
SRC += end_free.c
SRC += free.c
SRC += ft_putchar.c
SRC += ft_putstr.c
SRC += ft_putnbr_hexa.c
SRC += ft_putnbr.c
SRC += ft_memcpy.c
SRC += get_block.c
SRC += get_map_size.c
SRC += get_map_type.c
SRC += malloc.c
SRC += realloc.c
SRC += show_alloc_mem.c

vpath %.c $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))

#.SILENT:

all : $(NAME) $(LINK)

$(NAME) : $(OBJECTS)
	$(CC) $^ -shared -o $@

$(LINK) :
	ln -sf $(NAME) $(LINK)



$(OBJECTS): $(HEADERS) | $(OBJ_PATH)

$(OBJECTS): $(OBJ_PATH)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(HEADER_PATH)

$(OBJ_PATH):
	@-mkdir -p $@

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME) $(LINK)

re: fclean all

test:
	gcc Test/test.c -L./ libft_malloc.so -I Includes

norme:
	-@ ! norminette -R CheckTopCommentHeader $(SRC_PATH) | grep -v -B 1 "^Norme" || true
	-@ ! norminette -R CheckTopCommentHeader $(HEADER_PATH) | grep -v -B 1 "^Norme" || true

#	cat $(SRC) | grep "include <*>" | sort -u

watch:
	watch "make norme" "50"

function:
	nm -u $(NAME)

.PHONY: re fclean clean norme watch function test
