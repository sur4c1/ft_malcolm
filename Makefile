include source.mk

NAME	=	ft_malcolm

OBJS	=	$(addsuffix .o, $(SRCS))
INCS	=	$(addsuffix .h, $(SRCS))

SDIR	=	srcs/
ODIR	=	objs/
IDIR	=	incs/
LDIR	=	libs/

LIBS	=	$(LDIR)libft/libft.a

CC		=	cc
CFLAGS	=	-I$(IDIR) $(addprefix -I, $(dir $(LIBS))) -Wall -Werror -Wextra
LFLAGS	=	$(addprefix -L, $(dir $(LIBS))) -lft

RM		=	rm -rf
LN		=	ln -sf
MKDIR	=	mkdir -p
ECHO	=	echo

all: $(LIBS) $(NAME)
clean:
	$(RM) $(ODIR)
	$(MAKE) -C $(LDIR)libft fclean
fclean: clean
	$(RM) $(NAME)
re: fclean all

$(NAME):	$(addprefix $(ODIR), $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(ODIR)%.o: $(SDIR)%.c $(IDIR)%.h
	$(MKDIR) $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LDIR)libft/libft.a:
	$(MAKE) -C $(LDIR)libft

source.mk:
	./configure

.PHONY: all clean fclean re
