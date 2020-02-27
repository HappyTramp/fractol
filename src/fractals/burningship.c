/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:15:49 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/27 12:25:24 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define BURNING_SHIP_ESCAPE_RADIUS_SQUARED 4.0

int	burningship(t_state *state, t_complex c)
{
	int			n;
	t_complex	z;
	t_complex	z_square;
	double		tmp;
	
	(void)state;
	z = c;
	n = -1;
	while (++n < state->iterations)
	{
		z_square.i = z.i * z.i;
		z_square.r = z.r * z.r;
		if (z_square.r + z_square.i > BURNING_SHIP_ESCAPE_RADIUS_SQUARED)
			break;
		tmp = z_square.r - z_square.i + z.r;
		z.i = fabs(2.0 * z.r * z.i + c.i);
		z.r = fabs(tmp);
	}
	return (n);
}
