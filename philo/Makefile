NAME = philo
FILES = freeying_destroying_mutexes.c \
		initializing_data.c \
		parsing_func.c \
		philo.c \
		routine_functions.c \
		utils_functions.c

OBJ = $(FILES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread 

all: $(NAME)

%.o : %.c philosophers.h
	$(CC) $(CFLAGS)  -c $< -o $@ 

$(NAME): $(OBJ)
	${CC} $(CFLAGS) ${OBJ}  -o ${NAME}

clean :
	rm -rf $(OBJ) 
fclean : clean
	rm -rf $(NAME) 

re: fclean all
