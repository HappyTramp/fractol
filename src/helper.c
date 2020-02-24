/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:54:57 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/24 12:17:08 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	h_offset_to_complex(t_state *state, t_complex *z, int offset)
{
	int y;  // unoptimized
	int x;

	y = offset / state->window.width;
	x = offset % state->window.width;
	z->a = y / state->window.height * state->plane.a;
	z->b = x / state->window.width * state->plane.b;
}
