/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:28:16 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/25 16:21:56 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>

# include "mlx.h"
# include "libft.h"
# include "libft_math.h"

# define WINDOW_TITLE "fractol"

# define FRACTOL_RESOLUTION_MEDIUM

# ifdef FRACTOL_RESOLUTION_HIGH
#  define WINDOW_WIDTH 1600
#  define WINDOW_HEIGHT 1200
# elif defined(FRACTOL_RESOLUTION_MEDIUM)
#  define WINDOW_WIDTH 1024
#  define WINDOW_HEIGHT 768
# else
#  define FRACTOL_RESOLUTION_LOW
#  define WINDOW_WIDTH 800
#  define WINDOW_HEIGHT 600
# endif
// # define WINDOW_WIDTH_DOUBLE 640.0
// # define WINDOW_HEIGHT_DOUBLE 480.0

# define MLXK_ESC 53
# define MLXK_UP 126
# define MLXK_DOWN 125
# define MLXK_LEFT 123
# define MLXK_RIGHT 124
# define MLXK_H 4
# define MLXK_J 38
# define MLXK_K 40
# define MLXK_L 37
# define MLXK_D 2
# define MLXK_F 3
# define MLXK_PLUS 24
# define MLXK_MINUS 27

# define MLX_MOUSE_SCROLL_UP 5
# define MLX_MOUSE_SCROLL_DOWN 4

# define MLX_LITTLE_ENDIAN 0
# define MLX_BIG_ENDIAN 1

# define ZOOM_SPEED 1.2

typedef union
{
	unsigned int	hexcode;
	struct
	{
		uint8_t		b;
		uint8_t		g;
		uint8_t		r;
		uint8_t		alpha;
	}				rgb;
}					t_color;

typedef struct
{
	uint8_t			h;
	uint8_t			s;
	uint8_t			l;
}					t_color_hsl;

typedef struct
{
	int				width;
	int				height;
	void			*id;
	char			*data;
	int				depth;
	int				size_line;
	int				endian;
}					t_image;

typedef struct
{
	double			r;
	double			i;
}					t_complex;

struct				s_state;

typedef int			(*t_func_fractal)(struct s_state *state, t_complex z);

typedef struct		s_state
{
	bool			running;
	bool			updated;
	void			*mlx_ptr;
	void			*window_ptr;
	t_image			window;
	t_color			*palette;
	t_func_fractal	func;
	t_complex		center;
	t_complex		plane;
	t_complex		c;
	int				iterations;
	int				offsets[WINDOW_HEIGHT];
}					t_state;

typedef struct
{
	t_state			*state;
	int				offset;
	t_complex		z;
}					t_render_routine_arg;

/*
** state.c
*/

int					state_init(t_state *state, char *fractal_name);
int					state_destroy(t_state *state);
void 				state_update_palette(t_state *state);

/*
** render.c
*/

int					render_update(t_state *state);

/*
** event.c
*/

int					event_quit(t_state *state);
int					event_keydown(int key, t_state *state);
int					event_mouse(int button, int x, int y, t_state *state);
int					event_mouse_motion(int x, int y, t_state *state);

/*
** fractals/
*/

int					mandelbrot(t_state *state, t_complex z);
int					julia(t_state *state, t_complex z);
int					tricorn(t_state *state, t_complex z);
int					burningship(t_state *state, t_complex z);

/*
** helper.c
*/

void				h_zoom_in(t_state *state);
void				h_zoom_out(t_state *state);

/*
** color.c
*/

t_color_hsl			color_rgb_to_hsl(t_color color_rgb);
t_color				color_hsl_to_rgb(t_color_hsl color_hsl);


#endif
