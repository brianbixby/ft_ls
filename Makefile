# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbixby <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/07 00:05:09 by bbixby            #+#    #+#              #
#    Updated: 2018/12/15 07:08:48 by bbixby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CFLAGS = -Wall -Werror -Wextra
RM = /bin/rm -rf
INC = -I=ft_ls.h -I=./ft_printf/ft_printf.h
FT_PRINTF_PATH = ft_printf/
CFILES = ./main.c ./ft_helpers1.c ./ft_errors.c ./ft_prints.c ./ft_sorts.c ./ft_sorts2.c ./ft_details.c ./ft_free.c ./ft_queue.c ./ft_routecat.c ./ft_foreachdir.c ./ft_listhelpers.c
OFILES = $(CFILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OFILES)
	@make -C $(FT_PRINTF_PATH)
	gcc $(CFLAGS) $(INC) ./ft_printf/libftprintf.a $(CFILES) -o $(NAME)
	# gcc -g $(INC) -fsanitize=address ./ft_printf/libftprintf.a $(CFILES) -o $(NAME)

clean:
	@make -C $(FT_PRINTF_PATH)/ clean
	$(RM) $(OFILES)

fclean: clean
	@make -C $(FT_PRINTF_PATH)/ fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean, fclean, all, re
