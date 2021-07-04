SRCS = server.c utils.c

SRCS_CL = client.c utils.c

OBJS = ${SRCS:.c=.o}

OBJS_CL = ${SRCS_CL:.c=.o}

NAME_SER = server

NAME_CL = client

HEAD = ./utils_minitalk.h

RM = rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all:	${NAME_CL} ${NAME_SER}

${NAME_SER}:    ${OBJS} ${HEAD}
				${CC} ${CFLAGS} -o ${NAME_SER} ${OBJS}

${NAME_CL}:		${OBJS_CL} ${HEAD}
				${CC} ${CFLAGS} -o ${NAME_CL} ${OBJS_CL}

clean:
		${RM} ${OBJS} ${OBJS_CL}

fclean: clean
		${RM} ${NAME_SER} ${NAME_CL} ${OBJS} ${OBJS_CL}

re:     fclean all

.PHONY: fclean clean all re