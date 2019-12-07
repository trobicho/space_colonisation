/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:44:48 by trobicho          #+#    #+#             */
/*   Updated: 2019/12/07 07:16:11 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <thread>
#include <SDL2/SDL.h>
#include "Space_colonisation.h"

#define NODE_COLOR			0x9f111c
#define ATTRACTOR_COLOR		0x527b2d

class	Renderer
{
	public:
		Renderer(Space_colonisation &space_col, int w, int h);
		~Renderer();

		void	render_loop();
		void	check_event();
		void	refresh();
		void	reset_pixels_buffer(Uint32 color = 0x0);

	private:
		void	space_col_render();
		void	draw_rect(glm::vec2 pos, glm::vec2 l, Uint32 color);
		void	draw_line(glm::vec2 p1, glm::vec2 p2, Uint32 color
					, int thickness);
		void	put_pixel(int x, int y, Uint32 color);
		double	pix_size();


		int				m_width;
		int				m_height;
		SDL_Window		*m_win;
		SDL_Renderer	*m_renderer;
		SDL_Texture		*m_texture;
		Uint32			*m_pixels_buffer;

		bool				m_quit = false;
		Space_colonisation	&m_space_col;
};
