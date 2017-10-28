# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/22 11:05:13 by florian           #+#    #+#              #
#    Updated: 2017/10/28 14:35:45 by fpasquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

All :
	make -C server server
	make -C client client

clean :
	make -C client clean
	make -C server clean

fclean : clean
	make -C client fclean
	make -C server fclean
	make -C libft fclear

re : fclean All
