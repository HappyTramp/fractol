/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:36:12 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/27 14:46:32 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color_hsl	color_rgb_to_hsl(t_color color_rgb)
{
	t_color_hsl	color_hsl;
	double	h;
	double	s;
	double	l;
	double	r;
	double	g;
	double	b;

	r = color_rgb.rgb.r / 256.0;
	g = color_rgb.rgb.g / 256.0;
	b = color_rgb.rgb.b / 256.0;

	double maxColor = ft_fmax(r, ft_fmax(g, b));
	double minColor = ft_fmin(r, ft_fmin(g, b));
	if (maxColor == minColor) // grey
	{
		h = 0.0;
		s = 0.0;
		l = minColor;
	}
	else
	{
		l = (maxColor + minColor) / 2.0;

		if (l < 0.5)
			s = (maxColor - minColor) / (maxColor + minColor);
		else
			s = (maxColor - minColor) / (2.0 - maxColor - minColor);

		if (r == maxColor)
			h = (g - b) / (maxColor - minColor);
		else if (g == maxColor)
			h = 2.0 + (b - r) / (maxColor - minColor);
		else
			h = 4.0 + (r - g) / (maxColor - minColor);

		h /= 6; //to bring it to a number between 0 and 1
		if (h < 0)
			h++;
	}
	color_hsl.h = (int)(h * 256.0);
	color_hsl.s = (int)(s * 256.0);
	color_hsl.l = (int)(l * 256.0);
	return (color_hsl);
}

t_color		color_hsl_to_rgb(t_color_hsl color_hsl)
{
	t_color	color_rgb;
	double	h;
	double	s;
	double	l;
	double	r;
	double	g;
	double	b;
	double temp1, temp2, tempr, tempg, tempb;

	h = color_hsl.h / 256.0;
	s = color_hsl.s / 256.0;
	l = color_hsl.l / 256.0;
	if(s == 0)
	{
		r = l;
		g = l;
		b = l;
	}
	else
	{
		if (l < 0.5) temp2 = l * (1 + s);
		else temp2 = (l + s) - (l * s);
		temp1 = 2 * l - temp2;
		tempr = h + 1.0 / 3.0;
		if (tempr > 1) tempr--;
		tempg = h;
		tempb = h - 1.0 / 3.0;
		if (tempb < 0) tempb++;

		if (tempr < 1.0 / 6.0) r = temp1 + (temp2 - temp1) * 6.0 * tempr;
		else if (tempr < 0.5) r = temp2;
		else if (tempr < 2.0 / 3.0) r = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempr) * 6.0;
		else r = temp1;

		if (tempg < 1.0 / 6.0) g = temp1 + (temp2 - temp1) * 6.0 * tempg;
		else if (tempg < 0.5) g = temp2;
		else if (tempg < 2.0 / 3.0) g = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempg) * 6.0;
		else g = temp1;

		if(tempb < 1.0 / 6.0) b = temp1 + (temp2 - temp1) * 6.0 * tempb;
		else if(tempb < 0.5) b = temp2;
		else if(tempb < 2.0 / 3.0) b = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempb) * 6.0;
		else b = temp1;
	}
	color_rgb.hexcode = 0x0;
	color_rgb.rgb.r = (int)(r * 256.0);
	color_rgb.rgb.g = (int)(g * 256.0);
	color_rgb.rgb.b = (int)(b * 256.0);
	return (color_rgb);
}
