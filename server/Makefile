# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/22 11:05:13 by florian           #+#    #+#              #
#    Updated: 2017/11/28 07:52:51 by fpasquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= serveur

SRC_NAME		= main.c init_signaux.c general.c server.c client_manager.c		\
				  cwd_manager.c cwds.c send_cwd_client.c func_get.c func_cd.c	\
				  func_put.c
SRC_NAME_GEN	= check_ip_port.c cwd_manager.c send_get_data.c send_get_file.c

INCLUDES		= server.h

LIBRARY			= ../libft/libft.a

OTHERS			= libft Makefile auteur
ARCH			= 64
OTHER_FLAGS 	= -lpthread -lncurses

GCC				= gcc
CFLAGS			= -Wall -Wextra -Werror -o3
OBJ_NAME		= $(SRC_NAME:.c=.o)
OBJ_NAME_GEN	=$(SRC_NAME_GEN:.c=.o)

SRCDIR			= srcs
OBJDIR			= objs
OBJDIR_GEN		= ../general_objs
INCDIR			= incs

SRC				= $(addprefix $(SRCDIR)/, $(SRC_NAME))
OBJ				= $(addprefix $(OBJDIR)/, $(OBJ_NAME))
OBJ_GEN			= $(addprefix $(OBJDIR_GEN)/, $(OBJ_NAME_GEN))
INC				= $(addprefix $(INCDIR)/, $(INCLUDES))

All : $(NAME)

$(NAME) :  $(LIBRARY) $(OBJDIR) $(OBJ) $(OBJ_GEN)
	$(GCC) $(CFLAGS) $(OTHER_FLAGS) -m$(ARCH) -o $(NAME) $(OBJ) $(OBJ_GEN) $(LIBRARY)
	@echo "\033[0;32m"$(NAME) "DONE\033[0m"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INC)
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -m$(ARCH) -o $@ -c $<

$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM
	rm -rf $(OBJDIR)
	make -C ../libft fclear

re : fclean All

.PHONY: All clean fclean re
