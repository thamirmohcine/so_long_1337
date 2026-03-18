# so_long_1337

A small 2D tile-based game built in C using MiniLibX.
The program loads a `.ber` map, validates it, renders the level, and lets the player collect all coins before reaching the exit.

---

## 📦 Installation

### Prerequisites
- **C compiler** `cc`
- **make**
- **MiniLibX (mlx)**

### Native build (auto OS detection)
The Makefile now auto-detects your OS:
- **Linux**: uses local `mlx_linux/`, builds MLX automatically, and links with X11.
- **macOS**: keeps framework-based MiniLibX linking.

Linux packages (Debian/Ubuntu):
```bash
sudo apt update
sudo apt install build-essential make libx11-dev libxext-dev zlib1g-dev git
```

`mlx_linux/` is managed as a git submodule.

If you clone this repo for the first time:
```bash
git clone --recurse-submodules https://github.com/thamirmohcine/so_long_1337
```

If you already cloned without submodules:
```bash
git submodule update --init --recursive
```

### Build
```bash
make
```

### Docker guide (recommended for all users)

This project includes Docker support directly in the `Makefile`.

#### 1) Build image
```bash
make docker-build
```

#### 2) Run game (default map)
```bash
make docker-run
```

#### 3) Run a specific map
```bash
make docker-run-map MAP=maps/map_1.ber
```

#### 4) Rebuild image from scratch (after code/texture changes)
```bash
make docker-rebuild
```

#### 5) Remove image (optional)
```bash
make docker-clean
```

### Docker prerequisites
- Docker installed and daemon running.
- X11 display available on host.
- `xhost` available (used automatically by `docker-run` and `docker-run-map`).

### Direct Docker commands (manual alternative)
```bash
docker build -t so_long_1337 .
xhost +local:docker
docker run --rm -it -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro so_long_1337
docker run --rm -it -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro so_long_1337 ./so_long maps/map_1.ber
```

### Troubleshooting Docker run
- If changes do not appear, rebuild image: `make docker-rebuild`.
- If GUI does not open, ensure host X server is active and `DISPLAY` is set.
- If keyboard does not work, click once inside the game window to focus it.

### Clean / Rebuild
```bash
make clean
make fclean
make re
```

---

## 🚀 Usage

Run the executable with a `.ber` map file:

```bash
./so_long maps/map_0.ber
```

Other sample maps included:
- `maps/map_1.ber`
- `maps/map_2.ber`

### Main entry example (`so_long_main.c`)
```c
int	main(int ac, char **av)
{
	t_game	game;
	int		i;

	i = 0;
	if (ac != 2)
		return (ft_printf("usage: ./a.out filename.ber\n"), 1);
	check_map_extention(av[1]);
	game.prg_name = av[0];
	initial_var(&game);
	game.f_name = av[1];
	game.hight = get_num_of_lines(&game);
	game.map_l = malloc ((game.hight + 1) * sizeof(char *));
	if (!game.map_l)
		return (write (2, strerror(errno), ft_strlen(strerror(errno))));
	game.fd = open(game.f_name, O_RDONLY);
	if (game.fd == -1)
	{
		ft_printf("%s\n", strerror(errno));
		exit(1);
	}
	go_pars(&game);
	creat_window(&game);
	close(game.fd);
	return (0);
}
```

---

## Controls

- `↑` Move up
- `↓` Move down
- `→` Move right
- `←` Move left
- `ESC` Exit game
- Window close button (`X`) exits the game

---

## Map Rules (Validation)

- File extension must be `.ber`
- Map must be rectangular
- Map must be surrounded by walls (`1`)
- Allowed characters only: `1`, `0`, `P`, `E`, `C`
- Exactly one player (`P`)
- Exactly one exit (`E`)
- At least one collectible (`C`)
- Player must be able to reach all collectibles and the exit

---

## Project Structure

- `so_long_main.c` — app entry, map loading, startup flow
- `so_long_0.c` / `so_long_1.c` — movement, rendering, MLX loop/hooks
- `parsing_0.c` / `parsing_1.c` / `parsing_2.c` — map checks and path validation
- `g_n_l.c` / `g_n_l_u.c` — custom `get_next_line`
- `ft_printf.c` — lightweight custom `printf`
- `so_long.h` — shared structs, prototypes, constants
- `maps/` — `.ber` map files
- `textures/` — expected `.xpm` sprite assets

---

## Output

- Executable name: `so_long`
