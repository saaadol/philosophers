NAME = philo_bonus
FILES = philo_bonus/initializing_data.c \
		philo_bonus/parsing_function.c \
		philo_bonus/philo_bonus.c \
		philo_bonus/routine_functions.c \
		philo_bonus/utils_functions.c

OBJ = $(FILES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

%.o : %.c philo_bonus/philosophers_bonus.h
	$(CC) $(CFLAGS)  -c $< -o $@ 

$(NAME): $(OBJ)
	${CC} ${OBJ}  -o ${NAME}

clean :
	rm -rf $(OBJ) 
fclean : clean
	rm -rf $(NAME) 

re: fclean all
