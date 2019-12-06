/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:45:13 by trobicho          #+#    #+#             */
/*   Updated: 2019/12/06 04:44:51 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Renderer.h"

Renderer::Renderer(Space_colonisation &space_col, int w, int h):
	m_space_col(space_col), m_width(w), m_height(h)
{
	m_win = SDL_CreateWindow("Space colonisation 2D"
		, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
		, m_width, m_height, SDL_WINDOW_OPENGL);
	std::cout << m_width << " " << m_height << std::endl;
	if (m_win == NULL)
		throw "Unable to create win";
	m_renderer = SDL_CreateRenderer(m_win, -1, SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == NULL)
		throw "Unable to create renderer";
	m_texture = SDL_CreateTexture(m_renderer
		, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING
		, m_width, m_height);
	if (m_texture == NULL)
		throw "Unable to create texture";
	if ((m_pixels_buffer
		= (Uint32*)malloc(sizeof(Uint32) * m_width * m_height)) == NULL)
		throw "Unable to create pixels buffer";
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);
}

Renderer::~Renderer()
{
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_win);
	SDL_Quit();
	free(m_pixels_buffer);
}

void	Renderer::space_col_render()
{
	std::vector<s_node>		&node = m_space_col.get_node();
	std::vector<glm::vec2>	&attractor = m_space_col.get_attractor();
	glm::vec2				len_att = glm::vec2(pix_size() * 4, pix_size() * 4);
	glm::vec2				len = glm::vec2(pix_size() * 2, pix_size() * 2);

	for (auto const &n : node)
	{
		draw_rect(n.pos, len, NODE_COLOR);
		draw_line(n.pos, node[n.link].pos, NODE_COLOR, 2);
	}

	for (auto const &a : attractor)
	{
		draw_rect(a, len_att, ATTRACTOR_COLOR);
	}
}

void	Renderer::render_loop()
{
	while (!m_quit)
	{
		reset_pixels_buffer();
		space_col_render();
		refresh();
		check_event();
	}
}

void	Renderer::check_event()
{
	SDL_Event	event;

	SDL_WaitEvent(&event);
	if (event.type == SDL_QUIT)
		m_quit = 1;
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE
				&& event.key.repeat == 0)
			m_quit = 1;
		if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
		{
			m_space_col.step();
		}
	}
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			m_quit = 1;
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				m_quit = 1;
		}
	}
}

void	Renderer::refresh()
{
	SDL_UpdateTexture(m_texture, NULL
			, m_pixels_buffer, m_width * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

void	Renderer::reset_pixels_buffer(Uint32 color)
{
	for (int p = 0; p < m_width * m_height; p++)
	{
		m_pixels_buffer[p] = color;
	}
}

double	Renderer::pix_size()
{
	return (m_width > m_height) ? 1.0 / m_width : 1.0 / m_height;
}

void	Renderer::draw_rect(glm::vec2 pos, glm::vec2 l, Uint32 color)
{
	int	w = l.x * m_width;
	int	h = l.y * m_height;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			put_pixel(x + pos.x * m_width, y + pos.y * m_height, color);
		}
	}
}

void	Renderer::draw_line(glm::vec2 p1, glm::vec2 p2, Uint32 color
			, int thickness)
{
	glm::vec2	thick;
	double		xs = (p2.x - p1.x) < -0.0 ? -1.0 : 1.0;
	double		ys = (p2.y - p1.y) < -0.0 ? -1.0 : 1.0;
	double		len_max = (fabs(p2.x - p1.x) < fabs(p2.y - p1.y))
		? fabs(p1.y - p2.y) : fabs(p1.x - p2.x);

	thick.x = thickness * pix_size();
	thick.y = thickness * pix_size();
	if (len_max > 0.0)
	{
		xs *= fabs(p2.x - p1.x) / len_max;
		ys *= fabs(p2.y - p1.y) / len_max;
		double len = 0.0;
		while (len < len_max)
		{
			draw_rect(p1, thick, color);
			p1.x += xs * pix_size();
			p1.y += ys * pix_size();
			len += pix_size();
		}
	}
}

void	Renderer::put_pixel(int x, int y, Uint32 color)
{
	if (x >= 0 && y >= 0 && x < m_width && y < m_height)
	{
		y = m_height - (y + 1);
		m_pixels_buffer[x + y * m_height] = color;
	}
}
