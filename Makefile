# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/27 01:48:43 by ahamouda          #+#    #+#              #
#    Updated: 2017/12/03 15:45:43 by ahamouda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Basics.

NAME = malloc.a

CC = clang

RM = rm -f

## Flags.

CFLAGS = -Wall -Werror -Wextra

SFLAGS = -Weverything

OFLAGS = -O3 -march=native

DFLAGS = -g3 -fsanitize=address

## Lib/Header.

HEADER_PATH = ./includes

HEADER_FILE = malloc.h
#HEADER_FILE += ft_printf_struct.h

HEADER = $(HEADER_FILE:%.h=$(HEADER_PATH)/%.h)

LIB = ./malloc.a

## Objects/Sources.


OBJ_PATH = Objects
OBJECTS = $(addprefix $(OBJ_PATH)/, $(SRC:%.c=%.o))

SRC_PATH = Sources

SRC += malloc.c

NORMINETTE_TEST := $(shell norminette $(SRC_PATH) $(HEADER_PATH) | grep -B 1 Error)

#.SILENT:

all : $(NAME)

$(NAME) : $(OBJECTS)
	ar rc $@ $^
	ranlib $(NAME)

$(OBJECTS): $(HEADERS) | $(OBJ_PATH)

$(OBJECTS): $(OBJ_PATH)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(SFLAGS) -I $(HEADER_PATH)

$(OBJ_PATH):
	@-mkdir -p $@

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norme:
ifeq ($(NORMINETTE_TEST), )
	@echo "Everything ok!"
else
	@norminette $(SRC_PATH) $(HEADER_PATH) | grep -B 1 Error
endif

watch:
	watch "make norme" "20"

function:
	nm -u $(NAME)

.PHONY: re fclean clean norme watch function
