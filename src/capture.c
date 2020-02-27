/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:15:11 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/27 14:46:01 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define IMG_DEPTH 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

/*
** bmp file format:
**     header:
**         file_header:
**             2: signature = "BM"
**             4: file size
**             4: reserved
**             4: offset to pixel array
**         info_header:
**	       4: header size
**	       4: image width
**	       4: image height
**	       2: number of color planes
**	       2: bits per pixel
**	       4: compression
**	       4: image size
**	       4: horizontal resolution
**	       4: vertical resolution
**	       4: colors in color table
**	       4: important color count
**     data:
**         pixel in rgb format (without alpha component)
**         padding added at the end of each pixel row
**         so the length of the row is a multiple of 4
*/

static void	bmp_write_pixels(int fd, t_image *image, uint8_t *bmp_data)
{
	int		i;
	int		j;
	uint8_t	padding[3];
	int		padding_size;

	ft_bzero(padding, 3);
	padding_size = (4 - (image->width * IMG_DEPTH) % 4) % 4;
	i = image->height;
	while (--i >= 0)
	{
		j = -1;
		while (++j < image->width)
		{
			bmp_data[3 * j + 0] = image->data[4 * (i * image->width + j)].rgb.r;
			bmp_data[3 * j + 1] = image->data[4 * (i * image->width + j)].rgb.g;
			bmp_data[3 * j + 2] = image->data[4 * (i * image->width + j)].rgb.b;
		}
		write(fd, bmp_data, image->width * 3);
		write(fd, padding, padding_size);
	}
}

static void	bmp_fill_header(
	t_image *image,
	uint8_t file_header[FILE_HEADER_SIZE],
	uint8_t info_header[INFO_HEADER_SIZE])
{
	int	file_size;

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (IMG_DEPTH * image->width
			+ ((4 - (image->width * IMG_DEPTH) % 4) % 4)) * image->height;
	ft_bzero(file_header, FILE_HEADER_SIZE);
	ft_bzero(info_header, INFO_HEADER_SIZE);
	file_header[0] = (uint8_t)('B');
	file_header[1] = (uint8_t)('M');
	file_header[2] = (uint8_t)(file_size);
	file_header[3] = (uint8_t)(file_size >> 8);
	file_header[4] = (uint8_t)(file_size >> 16);
	file_header[5] = (uint8_t)(file_size >> 24);
	file_header[10] = (uint8_t)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	info_header[0] = (uint8_t)(INFO_HEADER_SIZE);
	info_header[4] = (uint8_t)(image->width);
	info_header[5] = (uint8_t)(image->width >> 8);
	info_header[6] = (uint8_t)(image->width >> 16);
	info_header[7] = (uint8_t)(image->width >> 24);
	info_header[8] = (uint8_t)(image->height);
	info_header[9] = (uint8_t)(image->height >> 8);
	info_header[10] = (uint8_t)(image->height >> 16);
	info_header[11] = (uint8_t)(image->height >> 24);
	info_header[12] = (uint8_t)(1);
	info_header[14] = (uint8_t)(IMG_DEPTH * 8);
}

static bool	bmp_write(t_image *image, uint8_t file_header[FILE_HEADER_SIZE],
						uint8_t info_header[INFO_HEADER_SIZE], char *filename)
{
	int		fd;
	uint8_t	*bmp_data;

	if ((fd = open(filename, O_WRONLY | O_CREAT, 0644)) < 0)
		return (false);
	if ((bmp_data = malloc(sizeof(unsigned char) *
			(image->width * IMG_DEPTH))) == NULL)
	{
		close(fd);
		return (false);
	}
	write(fd, file_header, FILE_HEADER_SIZE);
	write(fd, info_header, INFO_HEADER_SIZE);
	bmp_write_pixels(fd, image, bmp_data);
	close(fd);
	return (true);
}

int			capture(t_state *state, char *filename)
{
	uint8_t	file_header[FILE_HEADER_SIZE];
	uint8_t	info_header[INFO_HEADER_SIZE];

	bmp_fill_header(&state->window, file_header, info_header);
	return (bmp_write(&state->window, file_header, info_header, filename));
}
