NAME = philo

SRCS = 0_main.c \
		1_init.c \
		2_routines.c \
		3_routine_utils.c \
		4_dismantle.c \
		5_utils.c \
		6_libftutils.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -g
PFLAG = -pthread

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(PFLAG) -o $(NAME)
	@echo Ready to dine with philosophers

clean:
	@rm -f $(OBJS) $(DEPS)

fclean: clean
	@rm -f $(NAME)
	@echo Clean slate

re: fclean all

.PHONY: all clean fclean re
-include $(DEPS)