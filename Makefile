NAME = philo

SRCS = 0_main.c \
		1_init.c \
		2_thread_init.c \
		3_utils.c \
		4_libftutils.c \
		5_dismantle.c

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
	@echo Almost clean

fclean: clean
	@rm -f $(NAME)
	@echo Clean slate baby

re: fclean all

.PHONY: all clean fclean re
-include $(DEPS)