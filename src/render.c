/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:54:59 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/25 16:13:40 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	*st_render_routine(void *void_arg)
{
	int						j;
	t_complex				z;
	t_state					*state;
	int						offset;
	t_render_routine_arg	*arg;

	arg = void_arg;
	state = arg->state;
	z = arg->z;
	offset = arg->offset;
	j = -1;
	while (++j < WINDOW_WIDTH)
	{
		z.r = ((double)j / (double)WINDOW_WIDTH)  * state->plane.r - (state->plane.r / 2.0) + state->center.r;
		((t_color*)state->window.data)[offset] = state->palette[state->func(state, z)];
		offset++;
	}
	return (NULL);
}

static void	st_render_fractal(t_state *state)
{
	int						i;
	pthread_t				threads[WINDOW_HEIGHT];
	t_render_routine_arg	routine_args[WINDOW_HEIGHT];

	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		routine_args[i].state = state;
		routine_args[i].offset = i * WINDOW_WIDTH;
		routine_args[i].z.i = ((double)i / (double)WINDOW_HEIGHT) * state->plane.i - (state->plane.i / 2.0) + state->center.i;
		if (pthread_create(threads + i, NULL, st_render_routine, routine_args + i) < 0)
		{
			state->running = false;
			break;
		}
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
