/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:54:59 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/26 13:29:04 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define SUPERSAMPLE_SIZE 3

static t_color	st_take_sample(t_state *state, t_complex z, double step_r, double step_i)
{
	double						u;
	double						v;
	t_complex				sz;
	t_color					color;
	t_color					tmp;
	int		r;
	int		g;
	int		b;

	color.hexcode = 0x0;
	r = 0;
	g = 0;
	b = 0;
	u = 0.0;
	while (u < state->samples)
	{
		v = 0.0;
		while (v < state->samples)
		{
			sz.i = z.i + step_i * (u / state->samples);
			sz.r = z.r + step_r * (v / state->samples);
			tmp = state->palette[state->func(state, sz)];

			r += tmp.rgb.r;
			g += tmp.rgb.g;
			b += tmp.rgb.b;
			v += 1.0;
		}
		u += 1.0;
	}
	int s = (int)(state->samples * state->samples);
	color.rgb.r = r / s;
	color.rgb.g = g / s;
	color.rgb.b = b / s;

	return (color);
}

static void	*st_render_routine(void *void_arg)
{
	int						j;
	t_complex				z;
	t_state					*state;
	int						offset;
	double					step_r;
	t_render_routine_arg	*arg;

	arg = void_arg;
	state = arg->state;
	z = arg->z;
	offset = arg->offset;
	j = -1;
	step_r = state->plane.r / (double)WINDOW_WIDTH;
	z.r = state->center.r - state->plane.r / 2.0;
	while (++j < WINDOW_WIDTH)
	{
		((t_color*)state->window.data)[offset] = state->samples == 1.0 ?
			state->palette[state->func(state, z)] : st_take_sample(state, z, step_r, arg->step_i);
		offset++;
		z.r += step_r;
	}
	return (NULL);
}

static void	st_render_fractal(t_state *state)
{
	int						i;
	pthread_t				threads[WINDOW_HEIGHT];
	t_render_routine_arg	routine_args[WINDOW_HEIGHT];
	double					step_i;
	double					z_i;

	step_i = state->plane.i / (double)WINDOW_HEIGHT;
	z_i = state->center.i - state->plane.i / 2.0;
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		routine_args[i].state = state;
		routine_args[i].offset = i * WINDOW_WIDTH;
		routine_args[i].z.i = z_i;
		routine_args[i].step_i = step_i;
		if (pthread_create(threads + i, NULL, st_render_routine, routine_args + i) < 0)
		{
			state->running = false;
			break;
		}
		z_i += step_i;
	}
	while (i-- > 0)
		pthread_join(threads[i], NULL);
}

int			render_update(t_state *state)
{
	if (!state->running)
	{
		state_destroy(state);
		exit(EXIT_SUCCESS);
	}
	if (state->updated)
		return (0);
	st_render_fractal(state);
	mlx_put_image_to_window(state->mlx_ptr, state->window_ptr, state->window.id, 0, 0);
	state->updated = true;
	return (0);
}
