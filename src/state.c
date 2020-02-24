/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:58:01 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/24 10:43:08 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void st_state_init_palette(t_state *state)
{


}

int	state_init(t_state *state, char *fractal_name)
{
	(void)fractal_name;

	if ((state->mlx_ptr = mlx_init()) == NULL)
		return (-1);
	if ((state->window_ptr = mlx_new_window(state->mlx_ptr, 640, 480, WINDOW_TITLE)) == NULL)
		return (state_destroy(state));
	state->window.width = WINDOW_WIDTH;
	state->window.height = WINDOW_HEIGHT;
	if ((state->window.id = mlx_new_image(state->mlx_ptr, state->window.width, state->window.height)) == NULL)
		return (state_destroy(state));
	state->window.data = mlx_get_data_addr(state->window.id, &state->window.depth,
								&state->window.size_line, &state->window.endian);
	state->running = true;
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
