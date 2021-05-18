# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/14 19:33:24 by kshanti           #+#    #+#              #
#    Updated: 2021/05/18 22:57:39 by kshanti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishel_pars

HEAD = ./includes_parser
SRCS = ./srcs_parser/

CFLAGS = -Wall -Wextra -Werror

C_FILE =	$(SRCS)errors.c $(SRCS)parser.c\
			./main.c

O_FILE = $(C_FILE:.c=.o)

all:
	$(MAKE) $(NAME) -j 4

$(NAME): $(O_FILE)
	$(MAKE) -C ./libft bonus
	gcc $(O_FILE) ./libft/libft.a -o $(NAME)

%.o: %.c $(HEAD)
	gcc -c $(СFLAGS) $< -o $@

clean:
	@rm -f $(O_FILE)
	$(MAKE) -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re