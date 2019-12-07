/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:39:53 by trobicho          #+#    #+#             */
/*   Updated: 2019/12/07 21:18:48 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"
#include "Renderer.h"
#include "my_lib.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



static void	generate_attractor_on_img(const char *img_file
				, s_space_col_info &sc_inf, int n)
{
	int			nb_att = 0;
	glm::vec2	v;
	stbi_uc*	img_buffer;
	int			w, h, channels;
	double		d;

	img_buffer = stbi_load(img_file, &w, &h
					, &channels, 0);
	std::cout << "load: " << img_file << " (" << w << ", " << h
				<< ") " << channels << std::endl;
	while (nb_att < n)
	{
		v.x = trl::rand_uniform_double(0.0, 1.0);
		v.y = trl::rand_uniform_double(0.0, 1.0);
		d = trl::rand_uniform_double(0.0, 1.0);
		if (d > img_buffer[((int)(v.y * h) * w + (int)(v.x * w)) * channels] / 255.0)
		{
			continue;
		}
		v.y = 1.0f - v.y;
		sc_inf.attractor.push_back(v);
		nb_att++;
	}
	stbi_image_free(img_buffer);

}
static void	generate_attractor(s_space_col_info &sc_inf, int n
				, glm::vec2 center, double r)
{
	int			nb_att = 0;
	glm::vec2	v;

	while (nb_att < n)
	{
		v.x = trl::rand_uniform_double(-r, r);
		v.y = trl::rand_uniform_double(-r, r);
		if (length(v) > r)
			continue;
		v += center;
		sc_inf.attractor.push_back(v);
		nb_att++;
	}
}

int			main()
{
	s_space_col_info	info;

	info.attractor.reserve(2000);
	info.branch.reserve(2000);
	/*
	info.branch.push_back(Branch(glm::vec2(0.5, 0.0)));
	info.branch.push_back(Branch(glm::vec2(0.5, 0.2), 0));
	info.branch.push_back(Branch(glm::vec2(0.5, 0.25), 1));
	info.branch.push_back(Branch(glm::vec2(0.5, 0.3), 2));
	*/
	info.branch.push_back(Branch(glm::vec2(0.5, 0.1)));
	info.di = 0.020;
	info.dk = 0.008;
	/*
	generate_attractor(info, 40, glm::vec2(0.5, 0.5), 0.35);
	generate_attractor(info, 50, glm::vec2(0.8, 0.8), 0.10);
	*/
	generate_attractor_on_img("./sp_test.png", info, 3000);
	Space_colonisation	space_col(info);
	Renderer			renderer(space_col, 1000, 1000);
	renderer.render_loop();
	return (0);
}
