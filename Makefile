.PHONY		=	all clean fclean re bonus

NAME		=	philo

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	/bin/rm -f

INC			= 	philo.h

OBJ_DIR		=	obj

SRCS		=	philo.c \
				check.c \
				utils.c \
				utils2.c \
				init.c \
				routines.c \
				actions.c \
				clear.c \
				time.c

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
