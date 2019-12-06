/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space_colonisation.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 01:42:47 by trobicho          #+#    #+#             */
/*   Updated: 2019/12/06 04:07:30 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct	s_node
{
	s_node(){};
	s_node(glm::vec2 _pos, int _link = 0): pos(_pos), link(_link){}
	glm::vec2	pos;
	size_t		link;
};

struct	s_space_col_info
{
	double					di;
	double					dk;
	std::vector<glm::vec2>	attractor;
	std::vector<s_node>		node;
};

class	Space_colonisation
{
	public:
		Space_colonisation(s_space_col_info &info);
		~Space_colonisation(){};

		void					step();
		std::vector<s_node>		&get_node(){return (m_node);}
		std::vector<glm::vec2>  &get_attractor(){return (m_attractor);}

	private:
		void					col_one_node(size_t n);

		std::vector<s_node>		&m_node;
		std::vector<glm::vec2>	&m_attractor;
		double					m_di;
		double					m_dk;
		bool					m_first = true;
};
