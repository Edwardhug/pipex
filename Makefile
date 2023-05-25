NAME = pipex


CC = gcc

CFLAG = -Wall -Wextra -Werror -g3

SRCS =	main.c\
		ft_parsing.c\
		ft_free.c\
		ft_apply.c\
		ft_apply_cmd.c


INCLUDE = pipex.h

OBJS = $(SRCS:%.c=$(PATH_OBJS)%.o)

LIBFT_A = Libft/libft.a

PATH_SRCS = src/

PATH_INCLUDE = include/

PATH_OBJS = obj/

PATH_LIBFT = Libft/

# ----------------------------------variable bonus--------------------------

NAME_BONUS = pipex

SRCS_BONUS = pipex_bonus.c

OBJS_BONUS = $(SRCS_BONUS:%.c=$(PATH_OBJS)%.o)

PATH_SRCS_BONUS = src_bonus/

INCLUDE_BONUS = pipex_bonus.h

# ------------------------------------make----------------------------------

all: $(NAME)

$(NAME) : $(PATH_OBJS) $(OBJS) $(PATH_INCLUDE)$(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)


$(OBJS)	: $(PATH_OBJS)%.o: $(PATH_SRCS)%.c $(PATH_INCLUDE)$(INCLUDE) $(LIBFT_A)
				$(CC) $(CFLAG) -I$(PATH_INCLUDE) -I$(PATH_LIBFT) -c $< -o $@

# --------------------------------make bonus---------------------------------

bonus: $(PATH_OBJS) $(OBJS_BONUS) $(PATH_INCLUDE)$(INCLUDE_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_A) -o $(NAME)

$(OBJS_BONUS)	: $(PATH_OBJS)%.o: $(PATH_SRCS_BONUS)%.c $(PATH_INCLUDE)$(INCLUDE_BONUS) $(LIBFT_A)
				$(CC) $(CFLAG) -I$(PATH_INCLUDE) -I$(PATH_LIBFT) -c $< -o $@

# ----------------------------------utils------------------------------------

$(PATH_OBJS) :
				mkdir -p $(PATH_OBJS)

$(LIBFT_A)	:	FORCE
				make all -C $(PATH_LIBFT)

# ----------------------------------commands---------------------------------

clean:
	rm -rf ${OBJS} $(PATH_OBJS)
	@make clean -C $(PATH_LIBFT)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C $(PATH_LIBFT)

re: fclean all

FORCE: 

.PHONY: all re bonus clean fclean