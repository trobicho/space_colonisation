/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:39:53 by trobicho          #+#    #+#             */
/*   Updated: 2019/12/07 00:52:31 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.h"
#include "my_lib.h"

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
	info.branch.push_back(Branch(glm::vec2(0.5, 0.5)));
	info.di = 0.05;
	info.dk = 0.02;
	generate_attractor(info, 10000, glm::vec2(0.5, 0.5), 0.5);
	Space_colonisation	space_col(info);
	Renderer			renderer(space_col, 1000, 1000);
	renderer.render_loop();
	return (0);
}
