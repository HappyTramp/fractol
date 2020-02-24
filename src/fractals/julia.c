/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:17:38 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/24 15:36:04 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define JULIA_MAX_ITERATION 20
#define JULIA_ESCAPE_RADIUS_SQUARED 100

int	julia(t_state *state, t_complex z)
{
	int		n;
	double	zr;
	double	zi;
	double	zr_square;
	double	zi_square;
	
	zr = z.r;
	zi = z.i;
	n = -1;
	while (++n < JULIA_MAX_ITERATION)
	{
		zi_square = zi * zi;
		zr_square = zr * zr;
		if (zr_square + zi_square > JULIA_ESCAPE_RADIUS_SQUARED)
			break;
		zi = 2.0 * zr * zi;
		zr = zr_square - zi_square;
		zi += state->julia_const.i;
		zr += state->julia_const.r;
	}
	return (n);
}
