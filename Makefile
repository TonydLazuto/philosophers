.PHONY		=	all clean fclean re bonus

NAME		=	philo

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	/bin/rm -f

INC			= 	philo.h

OBJ_DIR		=	obj

SRCS		=	philo.c \
				check.c \
				actions.c \
				utils.c \
				utils2.c \
				routines.c \
				init.c \
				time.c \
				lst_th.c

OBJS		=	$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: 			$(NAME)

$(NAME): 		$(OBJS)
				$(CC) -o $(NAME) $(OBJS) -lpthread

$(OBJ_DIR)/%.o:	%.c
				@mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

clean:			
				rm -rf $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all
