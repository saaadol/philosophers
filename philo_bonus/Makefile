NAME = philo_bonus
FILES = initializing_data.c \
		parsing_function.c \
		philo_bonus.c \
		routine_functions.c \
		utils_functions.c

OBJ = $(FILES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror 


all: $(NAME)

%.o : %.c philosophers_bonus.h
	$(CC) $(CFLAGS)  -c $< -o $@ 

$(NAME): $(OBJ)
	${CC} $(CFLAGS) ${OBJ}  -o ${NAME}

clean :
	rm -rf $(OBJ) 
fclean : clean
	rm -rf $(NAME) 

re: fclean all
