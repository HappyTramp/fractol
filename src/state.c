/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:58:01 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/25 08:42:51 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define PALETTE_START 0x000022
#define PALETTE_END 0xd62f2f
/* #define PALETTE_START 0x000000 */
/* #define PALETTE_END 0xffffff */

static void st_state_init_palette(t_state *state)
{
	t_color	tmp;
	int		step_r;
	int		step_g;
	int		step_b;
	int		i;
	t_color colors[5];

	colors[0].hexcode = 0x0;
	colors[1].hexcode = 0xffdf00;
	/* colors[2].hexcode = 0xffffff; */
	/* colors[3].hexcode = 0x0000ff; */
	/* colors[4].hexcode = 0x000088; */

	int	c1 = 0;
	int	c2 = 1;
	int block_size = PALETTE_SIZE / 2;
	i = -1;
	double colorDelta = 1.0 / (2 - 1);
	while (++i < PALETTE_SIZE)
	{
		double globalRel = (double)i / (PALETTE_SIZE - 1);
		double localRel = (globalRel - c1 * colorDelta) / colorDelta;
		if (i % block_size)
		{
			c1++;
			c2++;
		}
		int dr = colors[c1].rgb.r - colors[c2].rgb.r;
		int dg = colors[c1].rgb.g - colors[c2].rgb.g;
		int db = colors[c1].rgb.b - colors[c2].rgb.b;

		state->palette[i].rgb.r = (int)(colors[c1].rgb.r + localRel * dr);
		state->palette[i].rgb.g = (int)(colors[c1].rgb.g + localRel * dg);
		state->palette[i].rgb.b = (int)(colors[c1].rgb.b + localRel * db);
	}







	/* tmp.hexcode = PALETTE_START; */
	/* step_r = ft_abs((PALETTE_END >> 16)         - (PALETTE_START >> 16)        ) / PALETTE_SIZE; */
	/* step_g = ft_abs(((PALETTE_END >> 8) & 0xff) - ((PALETTE_START >> 8) & 0xff)) / PALETTE_SIZE; */
	/* step_b = ft_abs((PALETTE_END & 0xff)        - (PALETTE_START & 0xff)       ) / PALETTE_SIZE; */
	/* i = -1; */
	/* while (++i < PALETTE_SIZE) */
	/* { */
	/* 	#<{(| tmp.rgb.r = (int)sqrt((double)i / PALETTE_SIZE);//tmp; |)}># */
	/* 	state->palette[i] = tmp; */
	/* 	tmp.rgb.r += step_r; */
	/* 	tmp.rgb.g += step_g; */
	/* 	tmp.rgb.b += step_b; */
	/* } */
}

static int	st_state_dispatch_func(t_state *state, char *fractal_name)
{
	if (ft_strcmp(fractal_name, "mandelbrot") == 0)
		state->func = &mandelbrot;
	else if (ft_strcmp(fractal_name, "julia") == 0)
	{
		state->func = &julia;
		state->c.r = 0.0;
		state->c.i = 0.0;
		return (0);
	}
	else if (ft_strcmp(fractal_name, "tricorn") == 0)
		state->func = &tricorn;
	else if (ft_strcmp(fractal_name, "burningship") == 0)
		state->func = &burningship;
	else
		return (-1);
	state->c.r = NAN;
	state->c.i = NAN;
	return (0);
}

int	state_init(t_state *state, char *fractal_name)
{
	if (st_state_dispatch_func(state, fractal_name) < 0)
		return (-1);
	if ((state->mlx_ptr = mlx_init()) == NULL)
		return (-1);
	if ((state->window_ptr = mlx_new_window(state->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)) == NULL)
		return (state_destroy(state));
	state->window.width = WINDOW_WIDTH;
	state->window.height = WINDOW_HEIGHT;
	if ((state->window.id = mlx_new_image(state->mlx_ptr, state->window.width, state->window.height)) == NULL)
		return (state_destroy(state));
	state->window.data = mlx_get_data_addr(state->window.id, &state->window.depth,
								&state->window.size_line, &state->window.endian);
	state->running = true;
	state->center.r = 0.0;
	state->center.i = 0.0;
	state->plane.r = 4.0;
	state->plane.i = 4.0;
	state->iterations = 20;
	st_state_init_palette(state);
	state->updated = false;
	return (0);
}

int	state_destroy(t_state *state)
{
	if (state == NULL)
		return (-1);
	if (state->mlx_ptr != NULL && state->window.id != NULL)
			mlx_destroy_image(state->mlx_ptr, state->window.id);
	if (state->mlx_ptr != NULL && state->window_ptr != NULL)
			mlx_destroy_window(state->mlx_ptr, state->window_ptr);
	return (-1);	
}
