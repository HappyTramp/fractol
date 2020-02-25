/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:15:49 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/25 07:33:53 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define BURNING_SHIP_MAX_ITERATION 20
#define BURNING_SHIP_ESCAPE_RADIUS_SQUARED 100

int	burningship(t_state *state, t_complex z)
{
	int		n;
	double	zr;
	double	zi;
	double	zr_square;
	double	zi_square;
	double	tmp;
	
	(void)state;
	zr = z.r;
	zi = z.i;
	n = -1;
	while (++n < state->iterations)
	{
		zi_square = zi * zi;
		zr_square = zr * zr;
		if (zr_square + zi_square > BURNING_SHIP_ESCAPE_RADIUS_SQUARED)
			break;
		tmp = zr_square - zi_square + z.r;
		zi = fabs(2.0 * zr * zi + z.i);
		zr = fabs(tmp);
	}
	return (n);
}
