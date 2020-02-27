/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:52:35 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/27 14:47:00 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define MOVE_SPEED 0.1

int	event_quit(t_state *state)
{
	state->running = false;
	return (0);
}

int	event_keydown(int key, t_state *state)
{
	/* printf("%d\n", key); */
	if (key == MLXK_ESC)
		state->running = false;
	else if (key == MLXK_UP || key == MLXK_K)
		state->center.i -= state->plane.i * MOVE_SPEED;
	else if (key == MLXK_DOWN || key == MLXK_J)
		state->center.i += state->plane.i * MOVE_SPEED;
	else if (key == MLXK_LEFT || key == MLXK_H)
		state->center.r -= state->plane.r * MOVE_SPEED;
	else if (key == MLXK_RIGHT || key == MLXK_L)
		state->center.r += state->plane.r * MOVE_SPEED;
	else if (key == MLXK_PLUS)
	{
		state->iterations += 5;
		state_update_palette(state);
	}
	else if (key == MLXK_MINUS)
	{
		state->iterations -= 5;
		if (state->iterations < 1)
			state->iterations = 1;
		state_update_palette(state);
	}
	else if (key == MLXK_F)
		h_zoom_in(state);
	else if (key == MLXK_D)
		h_zoom_out(state);
	else if (key == MLXK_S)
		state_shift_palette(state);
	else if (key == MLXK_R)
		state->samples += 1.0;
	else if (key == MLXK_E)
	{
		state->samples -= 1.0;
		if (state->samples < 1.0)
			state->samples = 1.0;
	}
	else if (key == MLXK_C)
		capture(state, "test.bmp");
	else
		return (0);
	state->updated = false;
	return (0);
}

int	event_mouse(int button, int x, int y, t_state *state)
{
	(void)x;
	(void)y;

	if (button == MLX_MOUSE_SCROLL_UP)
	{
		h_zoom_in(state);
		/* state->center.r += MOVE_SPEED * (double)(x - WINDOW_WIDTH / 2) / WINDOW_WIDTH; */
		/* state->center.i += MOVE_SPEED * (double)(y - WINDOW_HEIGHT / 2) / WINDOW_HEIGHT; */

	}
	else if (button == MLX_MOUSE_SCROLL_DOWN)
	{
		h_zoom_out(state);
		/* state->center.r -= MOVE_SPEED * (double)(x - WINDOW_WIDTH / 2) / WINDOW_WIDTH; */
		/* state->center.i -= MOVE_SPEED * (double)(y - WINDOW_HEIGHT / 2) / WINDOW_HEIGHT; */
	}
	else
		return (0);
	state->updated = false;
	return (0);
}

int	event_mouse_motion(int x, int y, t_state *state)
{
	if (state->c.r == NAN)
		return (0);
	if (x < 0)
		x = 0;
	if (x > WINDOW_WIDTH - 1)
		x = WINDOW_WIDTH - 1;
	if (y < 0)
		y = 0;
	if (y > WINDOW_HEIGHT - 1)
		y = WINDOW_HEIGHT - 1;
	state->c.r = ((double)x / (double)WINDOW_WIDTH)  * 4.0 - 2.0;
	state->c.i = ((double)y / (double)WINDOW_HEIGHT) * 4.0 - 2.0;
	state->updated = false;
	return (0);
}
