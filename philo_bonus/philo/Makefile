NAME = philo
FILES = philo/freeying_destroying_mutexes.c \
		philo/initializing_data.c \
		philo/parsing_func.c \
		philo/philo.c \
		philo/routine_functions.c \
		philo/utils_functions.c

OBJ = $(FILES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

%.o : %.c philo/philosophers.h
	$(CC) $(CFLAGS)  -c $< -o $@ 

$(NAME): $(OBJ)
	${CC} ${OBJ}  -o ${NAME}

clean :
	rm -rf $(OBJ) 
fclean : clean
	rm -rf $(NAME) 

re: fclean all
