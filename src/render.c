/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:54:59 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/27 14:40:58 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define SUPERSAMPLE_SIZE 3

static t_color	st_take_sample(t_state *state, t_complex z,
								double step_r, double step_i)
{
	t_complex		epsilon;
	t_complex		sample;
	t_color			color;
	t_color			tmp;
	uint32_t		r;
	uint32_t		g;
	uint32_t		b;
	int				s;

	color.hexcode = 0x0;
	r = 0;
	g = 0;
	b = 0;
	epsilon.i = 0.0;
	while (epsilon.i < state->samples)
	{
		epsilon.r = 0.0;
		while (epsilon.r < state->samples)
		{
			sample.i = z.i + step_i * (epsilon.i / state->samples);
			sample.r = z.r + step_r * (epsilon.r / state->samples);
			tmp = state->palette[state->func(state, sample)];
			r += tmp.rgb.r;
			g += tmp.rgb.g;
			b += tmp.rgb.b;
			epsilon.r += 1.0;
		}
		epsilon.i += 1.0;
	}
	s = (int)(state->samples * state->samples);
	color.rgb.r = r / s;
	color.rgb.g = g / s;
	color.rgb.b = b / s;
	return (color);
}

static void		*st_render_routine(void *arg)
{
	int			j;
	t_complex	z;
	t_state		*state;
	double		step_r;

	state = ((t_render_routine_arg*)arg)->state;
	z.i = ((t_render_routine_arg*)arg)->z_i;
	step_r = state->plane.r / FWINDOW_WIDTH;
	z.r = state->center.r - state->plane.r / 2.0;
	j = -1;
	if (state->samples == 1.0)
		while (++j < WINDOW_WIDTH)
		{
			state->window.data[((t_render_routine_arg*)arg)->offset] =
				state->palette[state->func(state, z)];
			z.r += step_r;
			((t_render_routine_arg*)arg)->offset++;
		}
	else
		while (++j < WINDOW_WIDTH)
		{
			state->window.data[((t_render_routine_arg*)arg)->offset] =
				st_take_sample(state, z, step_r, ((t_render_routine_arg*)arg)->step_i);
			z.r += step_r;
			((t_render_routine_arg*)arg)->offset++;
		}
	return (NULL);
}

static void		st_render_fractal(t_state *state)
{
	int						i;
	pthread_t				threads[WINDOW_HEIGHT];
	t_render_routine_arg	routine_args[WINDOW_HEIGHT];
	double					step_i;
	double					z_i;

	step_i = state->plane.i / FWINDOW_HEIGHT;
	z_i = state->center.i - state->plane.i / 2.0;
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		routine_args[i].state = state;
		routine_args[i].offset = i * WINDOW_WIDTH;
		routine_args[i].z_i = z_i;
		routine_args[i].step_i = step_i;
		if (pthread_create(threads + i, NULL,
						st_render_routine, routine_args + i) < 0)
		{
			state->running = false;
			break ;
		}
		z_i += step_i;
	}
	while (i-- > 0)
		pthread_join(threads[i], NULL);
}

int				render_update(t_state *state)
{
	char	*iterations_str;
	char	*samples_str;

	if (!state->running)
	{
		state_destroy(state);
		exit(EXIT_SUCCESS);
	}
	if (state->updated)
		return (0);
	st_render_fractal(state);
	mlx_put_image_to_window(state->mlx_ptr, state->window_ptr,
							state->window.id, 0, 0);
	iterations_str = ft_itoa(state->iterations);
	samples_str = ft_itoa((int)state->samples * (int)state->samples);
	mlx_string_put(state->mlx_ptr, state->window_ptr, 10, 20,
					0xeeeeee, iterations_str);
	mlx_string_put(state->mlx_ptr, state->window_ptr, 10, 30,
					0xeeeeee, samples_str);
	free(iterations_str);
	free(samples_str);
	state->updated = true;
	return (0);
}
