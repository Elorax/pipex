SRCS			=	ft_cmds.c \
					ft_find_path.c \
					ft_frees.c \
					ft_pipex.c \


OBJS			= $(SRCS:.c=.o)

CC			= gcc
RM			= rm -f

CFLAGS			= -Wall -Wextra -Werror -I.

NAME			= pipex

LIB				= libft.a

LIBPATH			= libft/

all:			$(NAME)

$(NAME):		$(OBJS)
				make -C $(LIBPATH) bonus
				gcc $(CFLAGS) -o $(NAME) $(SRCS) $(LIBPATH)$(LIB)

clean:
				rm -f $(OBJS) && make -C $(LIBPATH) clean

fclean:			clean
				rm -f $(NAME) && make -C $(LIBPATH) fclean

re:			fclean $(NAME)

.PHONY:			all clean fclean re
