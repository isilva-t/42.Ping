NAME = ft_ping

CC = cc
CFLAGS = -Wall -Wextra -Werror -I inc

SRCDIR = src
OBJDIR = obj

SOURCES = ft_ping.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): help.h $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) help.h

fclean: clean
	rm -f $(NAME)

re: fclean all

help.h: help.txt
	@echo "Generating help.h from help.txt..."
	@echo 'const char *help_text = ' > help.h
	@sed 's/\\/\\\\/g; s/"/\\"/g; s/^/"/; s/$$/\\n"/' help.txt >> help.h
	@echo ';' >> help.h

out:
	./out.sh

.PHONY: all clean fclean re

