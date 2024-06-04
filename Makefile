NAME = server
NAMEC = client
NAMEB = server_bonus
NAMECB = client_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror

SRCS = server.c
SRCSC = client.c
SRCSB = server_bonus.c
SRCSCB = client_bonus.c

OBJ = $(SRCS:.c=.o)
OBJC = $(SRCSC:.c=.o)
OBJB = $(SRCSB:.c=.o)
OBJCB = $(SRCSCB:.c=.o)

LIBFT = ./Libft
LIBFTA = $(LIBFT)/libft.a
LIBS = -L$(LIBFT) -lft

all : $(NAME) $(NAMEC) $(LIBFTA)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(LIBFTA) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(NAMEC): $(LIBFTA) $(OBJC)
	$(CC) $(FLAGS) $(OBJC) $(LIBS) -o $(NAMEC)

bonus : $(NAMEB) $(NAMECB) $(LIBFTA)

$(NAMEB): $(LIBFTA) $(OBJB)
	$(CC) $(FLAGS) $(OBJB) $(LIBS) -o $(NAMEB)

$(NAMECB): $(LIBFTA) $(OBJCB)
	$(CC) $(FLAGS) $(OBJCB) $(LIBS) -o $(NAMECB)

$(LIBFTA):
	@$(MAKE) -C $(LIBFT)

clean :
	rm -f $(OBJ) $(OBJC) $(OBJB) $(OBJCB)
	@$(MAKE) -C $(LIBFT) clean

fclean : clean
	rm -f $(NAME) $(NAMEC) $(NAMEB) $(NAMECB)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all bonus clean fclean re