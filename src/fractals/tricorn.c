/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:00:46 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/24 16:12:16 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define TRICORN_MAX_ITERATION 20
#define TRICORN_ESCAPE_RADIUS_SQUARED 100

int	tricorn(t_state *state, t_complex z)
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
	while (++n < TRICORN_MAX_ITERATION)
	{
		zi_square = zi * zi;
		zr_square = zr * zr;
		if (zr_square + zi_square > TRICORN_ESCAPE_RADIUS_SQUARED)
			break;
		tmp = zr_square - zi_square + z.r;
		zi = -2.0 * zr * zi + z.i;
		zr = tmp;
	}
	return (n);
}
