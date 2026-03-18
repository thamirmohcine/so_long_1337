# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 22:20:40 by mthamir           #+#    #+#              #
#    Updated: 2024/06/18 22:20:47 by mthamir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := so_long
DOCKER_IMAGE := so_long_1337
MAP ?= maps/map_0.ber

CC := cc

FLAGS := -Wall -Wextra -Werror

UNAME_S := $(shell uname -s)

MLX_DIR := mlx_linux

ifeq ($(UNAME_S),Linux)
FLAGS += -std=gnu17
MLX_INC := -I$(MLX_DIR)
MLX_FLAGS := -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
MLX_LIB := $(MLX_DIR)/libmlx_Linux.a
else
MLX_INC :=
MLX_FLAGS := -lmlx -framework OpenGL -framework AppKit
MLX_LIB :=
endif

SRC := so_long_main.c so_long_0.c so_long_1.c g_n_l.c g_n_l_u.c ft_printf.c parsing_0.c parsing_1.c parsing_2.c

OBJ := $(SRC:.c=.o)

HEADER := so_long.h

all : $(NAME)

$(NAME) : $(OBJ) $(MLX_LIB)
	$(CC) $(FLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) $(MLX_INC) -c $< -o $@

$(MLX_DIR)/libmlx_Linux.a:
	@cd $(MLX_DIR) && ./configure > /dev/null 2>&1 || true
	$(MAKE) -C $(MLX_DIR) -f Makefile.gen CC='$(CC) -std=gnu17' all

clean :
	rm -f $(OBJ)
	@if [ "$(UNAME_S)" = "Linux" ] && [ -f $(MLX_DIR)/Makefile.gen ]; then $(MAKE) -C $(MLX_DIR) -f Makefile.gen clean; fi

fclean : clean
	rm -f $(NAME)

re : fclean all

docker-build:
	docker build -t $(DOCKER_IMAGE) .

docker-rebuild:
	docker build --no-cache -t $(DOCKER_IMAGE) .

docker-run:
	xhost +local:docker >/dev/null 2>&1 || true
	docker run --rm -it -e DISPLAY=$$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro $(DOCKER_IMAGE)

docker-run-map:
	xhost +local:docker >/dev/null 2>&1 || true
	docker run --rm -it -e DISPLAY=$$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro $(DOCKER_IMAGE) ./so_long $(MAP)

docker-clean:
	docker rmi $(DOCKER_IMAGE)

.PHONY: all clean fclean re docker-build docker-rebuild docker-run docker-run-map docker-clean