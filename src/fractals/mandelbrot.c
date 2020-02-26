/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:07:41 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/26 13:12:55 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define MANDEL_MAX_ITERATION 20
#define MANDEL_ESCAPE_RADIUS_SQUARED 4

int	mandelbrot(t_state *state, t_complex c)
{
	int		n;
	double	zr;
	double	zi;
	double	zr_square;
	double	zi_square;
	
	(void)state;
	zr = c.r;
	zi = c.i;
	n = -1;
	while (++n < state->iterations)
	{
		zi_square = zi * zi;
		zr_square = zr * zr;
		if (zr_square + zi_square > MANDEL_ESCAPE_RADIUS_SQUARED)
			break;
		zi = 2.0 * zr * zi;
		zr = zr_square - zi_square;
		zi += c.i;
		zr += c.r;
	}
	return (n);
}
