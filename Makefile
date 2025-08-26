NAME = ft_ping

CC = cc
CFLAGS = -Wall -Wextra -Werror -I inc

SRCDIR = src
OBJDIR = obj

SOURCES = ft_ping.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

out:
	./out.sh

.PHONY: all clean fclean re

