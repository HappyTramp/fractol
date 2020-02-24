/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:07:41 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/24 15:25:17 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define MANDEL_MAX_ITERATION 20
#define MANDEL_ESCAPE_RADIUS_SQUARED 100

int	mandelbrot(t_state *state, t_complex z)
{
	int		n;
	double	zr;
	double	zi;
	double	zr_square;
	double	zi_square;
	
	(void)state;
	zr = z.r;
	zi = z.i;
	n = -1;
	while (++n < MANDEL_MAX_ITERATION)
	{
		zi_square = zi * zi;
		zr_square = zr * zr;
		if (zr_square + zi_square > MANDEL_ESCAPE_RADIUS_SQUARED)
			break;
		zi = 2.0 * zr * zi;
		zr = zr_square - zi_square;
		zi += z.i;
		zr += z.r;
	}
	return (n);
}
