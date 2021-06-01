DIR_INC = ./includes/

DIR_SRCS = ./srcs/

FUNC = 	utils_func.c main.c build_in/build_in_command.c build_in/export.c exec_command.c ft_split.c

SRCS = $(addprefix $(DIR_SRCS), $(FUNC))

OBJS = $(SRCS:.c=.o)

NAME = minishell

GCC = gcc
FLAGS = -Wall -Wextra -Werror

%.o: %.c $(DIR_INC)minirt.h
	$(GCC) $(FLAGS) -I $(DIR_INC) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C ../kshanti/libft
	$(GCC) $(FLAGS) -I $(DIR_INC) $(OBJS) ../kshanti/libft/libft.a -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) -C ../kshanti/libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C ../kshanti/libft fclean
	rm -f $(NAME)

re: fclean all


