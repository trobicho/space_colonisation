/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space_colonisation.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:42:49 by trobicho          #+#    #+#             */
/*   Updated: 2019/12/06 04:32:45 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Space_colonisation.h"
#include <iostream>

Space_colonisation::Space_colonisation(s_space_col_info &info):
	m_node(info.node), m_attractor(info.attractor)
	, m_di(info.di), m_dk(info.dk)
{
}

void	Space_colonisation::step()
{
	int		size_node = m_node.size();

	for (int n = 0; n < size_node; ++n)
	{
		col_one_node(n);
	}

	for (int n = (m_first ? 0 : size_node); n < m_node.size(); ++n)
	{
		int a = 0;
		while (a < m_attractor.size())
		{
			if (glm::length(m_attractor[a] - m_node[n].pos) <= m_dk)
			{
				m_attractor.erase(m_attractor.begin() + a);
				continue;
			}
			a++;
		}
		m_first = false;
	}
}

void	Space_colonisation::col_one_node(size_t n)
{
	std::vector<glm::vec2>	influance;
	float					d = 0.05;

	for (auto const &a : m_attractor)
	{
		if (glm::length(a - m_node[n].pos) <= m_di)
		{
			influance.push_back(a);
		}
	}
	if (influance.size() > 0)
	{
		glm::vec2	vec(0, 0);
		s_node		new_node;

		for (auto const &i : influance)
		{
			vec += glm::normalize(i - m_node[n].pos);
		}
		vec = glm::normalize(vec);
		new_node.link = n;
		new_node.pos = m_node[n].pos + vec * d;
		m_node.push_back(new_node);
	}
}
