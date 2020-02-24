/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:52:35 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/24 14:08:20 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define MOVE_SPEED 0.2
#define ZOOM_SPEED 1.1

int	event_quit(t_state *state)
{
	state->running = false;
	return (0);
}

int	event_keydown(int key, t_state *state)
{
	printf("%d\n", key);
	if (key == MLXK_ESC)
		state->running = false;
	else if (key == MLXK_UP)
		state->center.i -= state->plane.i * MOVE_SPEED;
	else if (key == MLXK_DOWN)
		state->center.i += state->plane.i * MOVE_SPEED;
	else if (key == MLXK_LEFT)
		state->center.r -= state->plane.r * MOVE_SPEED;
	else if (key == MLXK_RIGHT)
		state->center.r += state->plane.r * MOVE_SPEED;
	else
		return (0);
	render_update_window_complex(state);
	return (0);
}

int	event_mouse(int button, int x, int y, t_state *state)
{
	(void)x;
	(void)y;

	/* printf("%d\n", button); */
	/* printf("%d\n", x); */
	/* printf("%d\n", y); */
	if (button == MLX_MOUSE_SCROLL_UP)
	{
		state->plane.r /= ZOOM_SPEED;
		state->plane.i /= ZOOM_SPEED;
	}
	else if (button == MLX_MOUSE_SCROLL_DOWN)
	{
		state->plane.r *= ZOOM_SPEED;
		state->plane.i *= ZOOM_SPEED;
	}
	else
		return (0);
	render_update_window_complex(state);
	return (0);
}
