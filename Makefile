# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-oub <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/01 20:07:18 by mait-oub          #+#    #+#              #
#    Updated: 2025/02/01 23:17:24 by mait-oub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR)

NAME = pipex
NAME_MANDATORY = .pipex_mandatory
NAME_BONUS = .pipex_bonus

UTILS_DIR = $(SRC_DIR)/utils
UTILS_FILES = \
	$(UTILS_DIR)/create_zombie.c \
	$(UTILS_DIR)/dprints.c \
	$(UTILS_DIR)/free_array.c \
	$(UTILS_DIR)/ft_itoa.c \
	$(UTILS_DIR)/ft_split.c \
	$(UTILS_DIR)/ft_strchr.c \
	$(UTILS_DIR)/ft_strjoin.c \
	$(UTILS_DIR)/ft_strlcat.c \
	$(UTILS_DIR)/ft_strlen.c \
	$(UTILS_DIR)/ft_strncmp.c \
	$(UTILS_DIR)/get_next_line.c \
	$(UTILS_DIR)/get_next_line_utils.c \
	$(UTILS_DIR)/pathjoin.c \
	$(UTILS_DIR)/xsleep.c

SRC_FILES = \
	$(SRC_DIR)/close_stdio.c \
	$(SRC_DIR)/create_child.c \
	$(SRC_DIR)/execute_child.c \
	$(SRC_DIR)/init_stdio.c \
	$(SRC_DIR)/pipex.c \
	$(SRC_DIR)/terminate.c \
	$(UTILS_FILES)

INC_FILES = \
	$(INC_DIR)/get_next_line.h \
	$(INC_DIR)/pipex.h \
	$(INC_DIR)/utils.h

MANDATORY_SRCS = $(SRC_FILES) $(SRC_DIR)/main.c
BONUS_SRCS = $(SRC_FILES) $(SRC_DIR)/main_bonus.c $(SRC_DIR)/heredoc_bonus.c

MANDATORY_OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(MANDATORY_SRCS))
BONUS_OBJS = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(BONUS_SRCS))

PREBUILD = $(OBJ_DIR) $(OBJ_DIR)/utils
$(PREBUILD):
	@mkdir -v -p $@

SYMB_LINKS = MANDATORY BONUS
$(SYMB_LINKS):
	@if [ "$(realpath $(NAME))" = "" ]; then \
		ln -svf $(NAME_$@) $(NAME); \
	elif [ "$(realpath $(NAME_$@))" != "$(realpath $(NAME))" ]; then \
		ln -svf $(NAME_$@) $(NAME); \
	else \
		echo "make: '$(NAME)' is up to date."; \
	fi

.DEFAULT_GOAL = all
.PHONY: clean $(SYMB_LINKS)

all: $(NAME_MANDATORY)

bonus: $(NAME_BONUS)

$(NAME_MANDATORY): $(INC_FILES) $(MANDATORY_OBJS) | MANDATORY
	$(CC) $(CFLAGS) -o $@ $(MANDATORY_OBJS)

$(NAME_BONUS): $(INC_FILES) $(BONUS_OBJS) | BONUS
	$(CC) $(CFLAGS) -o $@ $(BONUS_OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(PREBUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -v -rf $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -v -rf $(NAME) $(NAME_MANDATORY) $(NAME_BONUS)

re: fclean all
