/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:58:01 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/27 14:43:39 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		state_update_palette(t_state *state)
{
	int			i;
	t_color_hsl	hsl;

	free(state->palette);
	if ((state->palette = malloc(
			sizeof(t_color) * (state->iterations + 1))) == NULL)
	{
		state->running = false;
		return ;
	}
	i = -1;
	while (++i < state->iterations)
	{
		hsl.h = (int)(255.0 * ((double)i / (double)state->iterations));
		hsl.s = 150;
		hsl.l = 127;
		state->palette[i] = color_hsl_to_rgb(hsl);
	}
	state->palette[i].hexcode = 0x111111;
}

void		state_shift_palette(t_state *state)
{
	int			i;
	t_color_hsl	hsl;
	int			shift_size;

	i = -1;
	shift_size = 255 / state->iterations;
	while (++i < state->iterations)
	{
		hsl = color_rgb_to_hsl(state->palette[i]);
		hsl.h += shift_size;
		hsl.h %= 256;
		state->palette[i] = color_hsl_to_rgb(hsl);
	}
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

int			state_init(t_state *state, char *fractal_name)
{
	if (st_state_dispatch_func(state, fractal_name) < 0)
		return (-1);
	if ((state->mlx_ptr = mlx_init()) == NULL)
		return (-1);
	if ((state->window_ptr = mlx_new_window(state->mlx_ptr,
				WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)) == NULL)
		return (state_destroy(state));
	state->window.width = WINDOW_WIDTH;
	state->window.height = WINDOW_HEIGHT;
	if ((state->window.id = mlx_new_image(state->mlx_ptr,
				state->window.width, state->window.height)) == NULL)
		return (state_destroy(state));
	state->window.data = (t_color*)mlx_get_data_addr(state->window.id,
		&state->window.depth, &state->window.size_line, &state->window.endian);
	state->running = true;
	state->center.r = 0.0;
	state->center.i = 0.0;
	state->plane.r = 4.0;
	state->plane.i = 4.0;
	state->iterations = 30;
	state->palette = NULL;
	state->samples = 1.0;
	state_update_palette(state);
	state->updated = false;
	return (0);
}

int			state_destroy(t_state *state)
{
	if (state == NULL)
		return (-1);
	if (state->mlx_ptr != NULL && state->window.id != NULL)
		mlx_destroy_image(state->mlx_ptr, state->window.id);
	if (state->mlx_ptr != NULL && state->window_ptr != NULL)
		mlx_destroy_window(state->mlx_ptr, state->window_ptr);
	return (-1);
}
