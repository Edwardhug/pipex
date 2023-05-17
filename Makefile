NAME = pipex

CC = gcc

CFLAG = -Wall -Wextra -Werror

SRCS =	main.c\
		ft_error.c\
		ft_init_pipex.c

INCLUDE = pipex.h

OBJS = $(SRCS:%.c=$(PATH_OBJS)%.o)

LIBFT_A = Libft/libft.a

PATH_SRCS = src/

PATH_INCLUDE = include/

PATH_OBJS = obj/

PATH_LIBFT = Libft/

all: $(NAME)


$(NAME) : $(PATH_OBJS) $(OBJS) $(PATH_INCLUDE)$(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)


$(OBJS)	: $(PATH_OBJS)%.o: $(PATH_SRCS)%.c $(PATH_INCLUDE)$(INCLUDE) $(LIBFT_A)
				$(CC) $(CFLAG) -I$(PATH_INCLUDE) -I$(PATH_LIBFT) -c $< -o $@


$(PATH_OBJS) :
				mkdir -p $(PATH_OBJS)

$(LIBFT_A)	:	FORCE
				make all -C $(PATH_LIBFT)


clean:
	rm -rf ${OBJS} $(PATH_OBJS)
	@make clean -C $(PATH_LIBFT)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C $(PATH_LIBFT)

re: fclean all

FORCE: 

.PHONY: all re bonus clean fclean