NAME	= philo

SRCS	= philo.c params.c utils.c 
			
OBJS	= $(SRCS:.c=.o)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=thread -g

.PHONY = all clean fclean re

all: $(NAME)
	@echo "philo is ready"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean: 
	rm -f $(OBJS)
	@echo "cleaned"

fclean:	clean
	rm -f $(NAME)
	@echo "fcleaned"

re: fclean all
	@echo "re done"