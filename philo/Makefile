# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgomes-d <mgomes-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 07:42:21 by mgomes-d          #+#    #+#              #
#    Updated: 2023/03/22 08:54:08 by mgomes-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror $(THREAD_FLAG)
CFLAGS += -g -pthread
THREAD_FLAG = -fsanitize=thread
RM = rm -rf

INC_DIR = includes
SRCS_DIR = srcs
OBJS_DIR = objs

SRCS =	main.c \
		utils.c

OBJS = $(addprefix ${OBJS_DIR}/, ${SRCS:%.c=%.o})


COLOR_CYAN = \033[1;36m
COLOR_RED = \033[0;31m
COLOR_GREEN	= \033[0;32m
COLOR_RESET = \033[0m

all: ${NAME}

${OBJS_DIR}:
	@echo "${COLOR_CYAN}${NAME} ${COLOR_GREEN}COMPILING ->${COLOR_RESET}"
	
${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIR}
	@mkdir -p ${@D}
	@${CC} ${CFLAGS} -I ${INC_DIR} -c $< -o $@
	@echo "${COLOR_GREEN}.${COLOR_RESET}\c"

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "${COLOR_CYAN}${NAME} ${COLOR_GREEN}${OBJS_DIR} were created${COLOR_RESET}"
	@echo "${COLOR_CYAN}${NAME} ${COLOR_GREEN}${NAME} was created${COLOR_RESET}"

clean:
	@${RM} ${OBJS_DIR}
	@echo "${COLOR_CYAN}${NAME} ${COLOR_RED}${OBJS_DIR} were deleted${COLOR_RESET}"

fclean:	clean
	@${RM} ${NAME}
	@echo "${COLOR_CYAN}${NAME} ${COLOR_RED}${NAME} was deleted${COLOR_RESET}"

re: fclean all

.PHONY: all clean fclean re
