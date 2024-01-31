NAME			= philo

CC				= gcc -fsanitize=thread
#CC				= gcc -fsanitize=address
#CC				= gcc
#CFLAGS			= -g -Wall -Wextra -Werror -MMD
CFLAGS			= -g -MMD
RM				= rm -rf
INCLUDES		= ./includes

SRCS_DIR		= ./src
UTILS_DIR		= ./utils
OBJS_DIR		= ./obj

rwildcard		= $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SRCS			= $(call rwildcard, $(SRCS_DIR)/, *.c) $(call rwildcard, $(UTILS_DIR)/, *.c)
OBJS 			= $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS 			= $(OBJS:.o=.d)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I$(INCLUDES)

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -pthread -I$(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(OBJS_DIR) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all