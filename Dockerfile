FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
	ca-certificates \
	build-essential \
	git \
	make \
	libx11-dev \
	libxext-dev \
	libbsd-dev \
	zlib1g-dev \
	xauth \
	&& update-ca-certificates \
	&& rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN rm -rf mlx_linux \
	&& git clone https://github.com/42Paris/minilibx-linux.git mlx_linux \
	&& make -C mlx_linux CC='cc -std=gnu17'

RUN cc -Wall -Wextra -Werror -Imlx_linux \
	so_long_main.c so_long_0.c so_long_1.c g_n_l.c g_n_l_u.c ft_printf.c parsing_0.c parsing_1.c parsing_2.c \
	-Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -lz -lbsd \
	-o so_long

CMD ["./so_long", "maps/map_0.ber"]