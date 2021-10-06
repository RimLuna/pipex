NAME	= 	pipex

SRCS 	=	srcs/arg.c  srcs/bzero.c  srcs/error.c  \
			srcs/getenv.c  srcs/getpaths.c  srcs/getpstruct.c \
			srcs/memalloc.c  srcs/mem.c  srcs/memset.c \
			srcs/pipex.c  srcs/strcmp.c  srcs/strdup.c  srcs/strjoin.c \
			srcs/strlen.c  srcs/strncmp.c  srcs/strnew.c  srcs/split.c

OBJS 	=	${SRCS:.c=.o}
MAIN	=	srcs/main.c

HEADER	=	-I./includes/

CC 		=	gcc
CFLAGS 	=	-Wall -Wextra -Werror -g

.c.o:		%.o : %.c
					@gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

$(NAME):	./includes/pipex.h $(SRCS) $(MAIN)
			$(CC) $(HEADER) $(SRCS) $(MAIN) -o ${NAME}

all: 		${NAME}

clean:
				@rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
				@rm -f $(NAME)

re:			fclean all