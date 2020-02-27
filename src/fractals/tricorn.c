/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:00:46 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/27 12:24:35 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define TRICORN_ESCAPE_RADIUS_SQUARED 4.0

int	tricorn(t_state *state, t_complex c)
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
		if (z_square.r + z_square.i > TRICORN_ESCAPE_RADIUS_SQUARED)
			break;
		tmp = z_square.r - z_square.i + z.r;
		z.i = -2.0 * z.r * z.i + c.i;
		z.r = tmp;
	}
	return (n);
}
