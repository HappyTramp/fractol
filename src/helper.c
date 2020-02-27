/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:54:57 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/27 14:46:51 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	h_zoom_in(t_state *state)
{
	state->plane.r /= ZOOM_SPEED;
	state->plane.i /= ZOOM_SPEED;
	/* state->iterations += 3; */
	/* state_update_palette(state); */
}

void	h_zoom_out(t_state *state)
{
	state->plane.r *= ZOOM_SPEED;
	state->plane.i *= ZOOM_SPEED;
	/* state->iterations -= 3; */
	/* state_update_palette(state); */
}
