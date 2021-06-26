# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 19:12:24 by kshanti           #+#    #+#              #
#    Updated: 2021/06/24 15:47:52 by kshanti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEAD = ./kshanti/includes_parser
SRCS = ./kshanti/srcs_parser/
SRCS2 = ./test_troxanna/srcs/
SRCS3 = $(SRCS2)build_in/
GNL = ./kshanti/get_next_line/
RL = -L/usr/local/Cellar/readline/8.1/include/readline/ -lreadline

CFLAGS = -Wall -Wextra -Werror

C_FILE =	$(SRCS)errors.c $(SRCS)parser.c $(SRCS)preparser.c $(SRCS)quotes.c\
			$(SRCS)utils.c $(SRCS)dollar.c $(SRCS)dollar_utils.c $(SRCS)redirect.c\
			$(SRCS)preparser_redirect.c\
			$(GNL)get_next_line.c $(GNL)get_next_line_utils.c\
			./main.c\
			$(SRCS2)exec_command.c $(SRCS2)ft_split.c $(SRCS2)utils_func.c\
			$(SRCS2)start_cmd.c $(SRCS3)build_in_command.c $(SRCS3)export.c $(SRCS3)echo.c $(SRCS3)cd.c

O_FILE = $(C_FILE:.c=.o)

all:
	$(MAKE) $(NAME) -j 4

$(NAME): $(O_FILE)
	$(MAKE) -C ./kshanti/libft bonus
	gcc $(O_FILE) ./kshanti/libft/libft.a $(RL) -o $(NAME)

%.o: %.c $(HEAD)
	gcc -c $(СFLAGS) $< -o $@

clean:
	@rm -f $(O_FILE)
	$(MAKE) -C ./kshanti/libft clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C ./kshanti/libft fclean

re: fclean all

.PHONY: all clean fclean re
