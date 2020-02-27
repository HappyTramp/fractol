/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:07:41 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/27 14:18:16 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define MANDEL_ESCAPE_RADIUS_SQUARED 4.0

int	mandelbrot(t_state *state, t_complex c)
{
	int			n;
	t_complex	z;
	t_complex	z_square;
	
	(void)state;
	z = c;
	n = -1;
	z_square.r = 0.0;
	z_square.i = 0.0;
	while (z_square.r + z_square.i <= MANDEL_ESCAPE_RADIUS_SQUARED && ++n < state->iterations)
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
