NAME = pipex

CC = clang

SRCS = pipex.c

OBJ = $(SRCS:.c=.o)

FLAG = -Wall -Wextra 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAG) -o $@ $^ 

%.o: %.c
	$(CC) $(FLAG) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
