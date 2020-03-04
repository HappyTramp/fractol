/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:27:44 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/27 14:47:05 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc != 2 || state_init(&state, argv[1]) < 0)
	{
		ft_putstr("mandelbrot\njulia\ntricorn\nburningship\n");
		return (0);
	}
	mlx_hook(state.window_ptr, 17, 0, event_quit, (void*)&state);
	mlx_key_hook(state.window_ptr, event_keydown, (void*)&state);
	mlx_hook(state.window_ptr, 6, 64, event_mouse_motion, (void*)&state);
	mlx_mouse_hook(state.window_ptr, event_mouse, (void*)&state);
	mlx_loop_hook(state.mlx_ptr, render_update, (void*)&state);
	mlx_loop(state.mlx_ptr);
	return (0);
}
