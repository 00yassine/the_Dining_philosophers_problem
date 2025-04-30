NAME = philo
src = main.c check_arguments.c ft_atoi.c fill_struct.c get_time.c functions.c
objf = $(src:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):$(objf)
	cc $(objf) -o $(NAME)

clean:
	rm -rf $(objf)

fclean:clean
	rm -rf $(NAME)

re: fclean all

.SECONDARY: $(objf)
