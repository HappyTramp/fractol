/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:52:35 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/24 10:10:29 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	event_quit(t_state *state)
{
	state->running = false;
	return (0);
}

int	event_keydown(int key, t_state *state)
{
	if (key == MLXK_ESC)
		state->running = false;
	return (0);
}
