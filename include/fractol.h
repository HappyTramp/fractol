/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:28:16 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/24 15:29:50 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "libft_math.h"

# define WINDOW_TITLE "fractol"
# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
# define WINDOW_WIDTH_DOUBLE 640.0
# define WINDOW_HEIGHT_DOUBLE 480.0

# define MLXK_ESC 53
# define MLXK_UP 126
# define MLXK_DOWN 125
# define MLXK_LEFT 123
# define MLXK_RIGHT 124

# define MLX_MOUSE_SCROLL_UP 5
# define MLX_MOUSE_SCROLL_DOWN 4

# define MLX_LITTLE_ENDIAN 0
# define MLX_BIG_ENDIAN 1

# define PALETTE_SIZE 21

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
	t_color			palette[PALETTE_SIZE];
	t_func_fractal	func;
	t_complex		center;
	t_complex		plane;
	t_complex		julia_const;
}					t_state;

/*
** state.c
*/

int					state_init(t_state *state, char *fractal_name);
int					state_destroy(t_state *state);

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

/*
** helper.c
*/

void				h_offset_to_complex(t_state *state, t_complex *z, int offset);

#endif
