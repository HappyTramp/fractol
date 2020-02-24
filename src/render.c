/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:54:59 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/24 13:46:44 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	st_render_fractal(t_state *state)
{
	int	offset;
	int	i;
	int	j;
	t_color	color;

	color.hexcode = 0xffffff;
	offset = 0;
	i = -1;
	while (++i < state->window.height)
	{
		j = -1;
		while (++j < state->window.width)
		{
			((t_color*)state->window.data)[offset] =
				state->palette[state->func(state->window_complex[offset])];
			/* printf("%06x\n", ((t_color*)state->window.data)[offset].hexcode); */
			/* printf("%d\n", state->func(state->window_complex[offset])); */
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
	st_render_fractal(state);
	mlx_put_image_to_window(state->mlx_ptr, state->window_ptr, state->window.id, 0, 0);
	return (0);
}

void		render_update_window_complex(t_state *state)
{
	int	i;
	int	j;
	int	offset;

	i = -1;
	offset = 0;
	while (++i < WINDOW_HEIGHT)
	{
		j = -1;
		while (++j < WINDOW_WIDTH)
		{
			state->window_complex[offset].r =
				((double)j / (double)WINDOW_WIDTH)  * state->plane.r - (state->plane.r / 2.0);
			state->window_complex[offset].i =
				((double)i / (double)WINDOW_HEIGHT) * state->plane.i - (state->plane.i / 2.0);
			offset++;
			/* printf("%f %f\n", state->window_complex[i * WINDOW_WIDTH + j].a, state->window_complex[i * WINDOW_WIDTH + j].b); */
				/* ((double)i / (double)WINDOW_HEIGHT) * state->plane.b - (state->plane.b / 2.0); */
			/* printf("%f\n", (double)i / (double)WINDOW_HEIGHT * state->plane.b- (state->plane.b / 2.0)); */
			/* h_offset_to_complex(state, state->window_complex + i, i);  // helper bloat? */
		}
	}
}
