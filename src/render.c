/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:54:59 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/24 10:44:32 by cacharle         ###   ########.fr       */
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
				state->palette[
					state->func(state->window_complex[offset])
				];
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
	/* st_render_fractal(state); */
	mlx_put_image_to_window(state->mlx_ptr, state->window_ptr, state->window.id, 0, 0);
	return (0);
}

