DIR_INC = ./includes/

DIR_SRCS = ./srcs/

FUNC = 	utils_func.c main.c build_in_command.c

SRCS = $(addprefix $(DIR_SRCS), $(FUNC))

OBJS = $(SRCS:.c=.o)

NAME = minishell

GCC = gcc
FLAGS = -Wall -Wextra -Werror

%.o: %.c $(DIR_INC)minirt.h
	$(GCC) $(FLAGS) -I $(DIR_INC) -c $< -o $@

$(NAME): $(OBJS)
	$(GCC) $(FLAGS) -I $(DIR_INC) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


