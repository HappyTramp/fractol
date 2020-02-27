/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:17:38 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/27 13:44:21 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define JULIA_ESCAPE_RADIUS_SQUARED 4.0

int	julia(t_state *state, t_complex origin_c)
{
	int			n;
	t_complex	z;
	t_complex	z_square;
	t_complex	c;
	
	z = origin_c;
	c = state->c;
	z_square.r = 0.0;
	z_square.i = 0.0;
	n = -1;
	while (z_square.r + z_square.i <= JULIA_ESCAPE_RADIUS_SQUARED && ++n < state->iterations)
	{
		z_square.i = z.i * z.i;
		z_square.r = z.r * z.r;
		z.i = 2.0 * z.r * z.i;
		z.r = z_square.r - z_square.i;
		z.i += c.i;
		z.r += c.r;
	}
	return (n);
}
