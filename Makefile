NAME =  philo

BNAME = 

CC = gcc

FLAGS = -Wall -Werror -Wextra

IDIR = -I. -I./libft -I../libft -I.. -I.

LIB = -L./libft -lft

MSRC = philo.c

BSRC = 

SUBSRCS = 

BONUSSUB = 

SUBOBJS = $(SUBSRCS:%.c=%.o)

SUBBOBJS = $(BONUSSUB:%.c=%.o)

all: $(NAME)

$(NAME): $(addprefix ./srcs/,$(SUBOBJS)) | ./libft/libft.a
	$(CC) $(FLAGS) $(IDIR) $(MSRC) -o $(NAME) $(addprefix ./srcs/,$(SUBOBJS)) $(LIB)

$(addprefix ./srcs/,$(SUBOBJS)):
	cd srcs && $(CC) $(FLAGS) $(IDIR) -c $(SUBSRCS)

bonus: $(addprefix ./srcs_bonus/,$(SUBBOBJS)) | ./libft/libft.a
	$(CC) $(FLAGS) $(IDIR) $(BSRC) -o $(BNAME) $(addprefix ./srcs_bonus/,$(SUBBOBJS)) $(LIB)

$(addprefix ./srcs_bonus/,$(SUBBOBJS)):
	cd srcs_bonus && $(CC) $(FLAGS) $(IDIR) -c $(BONUSSUB)

./libft/libft.a: ./libft/libft.h
	cd libft && $(MAKE) bonus && $(MAKE)

clean:
		/bin/rm -f *.o
		/bin/rm -f ./srcs/*.o ./srcs_bonus/*.o 
		cd libft && $(MAKE) clean

fclean: clean
		/bin/rm -f $(NAME) $(BNAME)
		cd libft && $(MAKE) fclean

re: fclean all $(BONUS) ./libft/libft.a
