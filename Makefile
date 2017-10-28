# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/22 11:05:13 by florian           #+#    #+#              #
#    Updated: 2017/10/28 17:48:34 by fpasquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= general

SRC_NAME		= init_ncurses.c

INCLUDES		= general.h

LIBRARY			= libft/libft.a

OTHERS			= libft Makefile auteur
ARCH			= 64
OTHER_FLAGS 	= -lncurses

GCC				= gcc
CFLAGS			= -Wall -Wextra -Werror -o3
OBJ_NAME		= $(SRC_NAME:.c=.o)

SRCDIR			= srcs
OBJDIR			= objs
INCDIR			= incs

SRC				= $(addprefix $(SRCDIR)/, $(SRC_NAME))
OBJ				= $(addprefix $(OBJDIR)/, $(OBJ_NAME))
INC				= $(addprefix $(INCDIR)/, $(INCLUDES))

All : $(NAME)

$(NAME) : $(LIBRARY) $(OBJDIR) $(OBJ)
	make -C client client
	make -C server server

$(LIBRARY) :
	make -C libft libft$(ARCH)
	@echo "\033[0;32mCOMPILE LIBFT ${ARCH}\033[0m"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INC)
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -m$(ARCH) -o $@ -c $<

$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(OBJ)
	make -C client clean
	make -C server clean

fclean : clean
	rm -rf $(OBJDIR)
	make -C client fclean
	make -C server fclean
	make -C libft fclear

re : fclean All
