/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:54:59 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/25 15:30:07 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* static void	*st_render_routine(t_state *state) */
/* { */
/* 	return (NULL); */
/* } */

static void	st_render_fractal(t_state *state)
{
	int	offset;
	int	i;
	int	j;
	t_color	color;
	t_complex	z;
	/* pthread_t	threads[WINDOW_HEIGHT */
	int tmp;

	color.hexcode = 0xffffff;
	offset = 0;
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		j = -1;
		while (++j < WINDOW_WIDTH)
		{
			z.r = ((double)j / (double)WINDOW_WIDTH)  * state->plane.r - (state->plane.r / 2.0) + state->center.r;
			z.i = ((double)i / (double)WINDOW_HEIGHT) * state->plane.i - (state->plane.i / 2.0) + state->center.i;
			tmp = state->func(state, z);
			/* if (tmp > state->iterations) */
			/* 	((t_color*)state->window.data)[offset].hexcode = 0x000000; */
			/* else */
	/* for (int i = 0; i < state->iterations; i++) */
		/* printf("%d %d %d\n", state->palette[tmp].rgb.r, state->palette[tmp].rgb.g, state->palette[tmp].rgb.b); */
				((t_color*)state->window.data)[offset] = state->palette[tmp];
			offset++;
		}
	}
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
