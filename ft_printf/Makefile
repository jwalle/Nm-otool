# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/05 11:39:59 by jwalle            #+#    #+#              #
#    Updated: 2016/07/01 13:19:38 by jwalle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FAT_FLAGS = -arch i386 -arch x86_64

CC = clang
CFLAGS = -Wall -Werror -Wextra $(FAT_FLAGS)
SRCDIR = ./srcs/

SRCO = $(SRC:.c=.o)

ODIR = ./objs/

INC = -I./includes
LINK_P = -L. -lftprintf

SRC =			ft_printf.c \
				ft_parse.c \
				ft_parse_two.c \
				ft_atoi_hex.c \
				arg_is_int.c \
				arg_is_u.c \
				arg_is_c.c \
				arg_is_wc.c \
				arg_is_string.c \
				arg_is_wstring.c \
				arg_is_p.c \
				ft_init.c \
				ft_intlen.c \
				print_number.c \
				format.c \
				misc.c \
				bonus_color.c \
				lib_one.c \
				lib_two.c \

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(ODIR), $(OBJ))

all: $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(addprefix $(ODIR), $(OBJ))
	ranlib $(NAME)

$(ODIR)%.o : $(SRCDIR)%.c
		@mkdir -p $(ODIR)
		$(CC) $(CFLAGS) -c $^ $(INC) -o $@

clean:
	/bin/rm -f $(addprefix $(ODIR), $(OBJ))
	/bin/rm -rf $(ODIR)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all
