NAME =  philo

BNAME = 

CC = gcc

FLAGS = -Wall -Werror -Wextra -pthread

IDIR = -I. -I.. -I.

MSRC = philo.c

BSRC = 

SUBSRCS = philotimeroutine.c philotools.c

BONUSSUB = 

SUBOBJS = $(SUBSRCS:%.c=%.o)

SUBBOBJS = $(BONUSSUB:%.c=%.o)

all: $(NAME)

$(NAME): $(addprefix ./srcs/,$(SUBOBJS))
	$(CC) $(FLAGS) $(IDIR) $(MSRC) -o $(NAME) $(addprefix ./srcs/,$(SUBOBJS)) $(LIB)

$(addprefix ./srcs/,$(SUBOBJS)):
	cd srcs && $(CC) $(FLAGS) $(IDIR) -c $(SUBSRCS)

bonus: $(addprefix ./srcs_bonus/,$(SUBBOBJS))
	$(CC) $(FLAGS) $(IDIR) $(BSRC) -o $(BNAME) $(addprefix ./srcs_bonus/,$(SUBBOBJS)) $(LIB)

$(addprefix ./srcs_bonus/,$(SUBBOBJS)):
	cd srcs_bonus && $(CC) $(FLAGS) $(IDIR) -c $(BONUSSUB)

clean:
		/bin/rm -f *.o
		/bin/rm -f ./srcs/*.o ./srcs_bonus/*.o 

fclean: clean
		/bin/rm -f $(NAME) $(BNAME)

re: fclean all $(BONUS)
