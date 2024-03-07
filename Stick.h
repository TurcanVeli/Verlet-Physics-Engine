#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "myvector.h"
#include "Circle.h"


class Stick
{

private:

	bool					_isSpring;
	std::vector<Circle*>	_linkedCircles;
	float					_thickness;
	float                   lenght;


public:
	Stick() = default;
	Stick(Circle& circleA, Circle& circleB, float thickness, bool isSpring);
	~Stick();


	void					uptade(sf::Event& event, const sf::Vector2f& Gravity, float dt);
	void					render(sf::RenderWindow* window);

	float                   getLength() const;
	float                   getFlexibility() const;
	bool					getIsSpring() const;
	std::vector<Circle*>	getLinkedCircles() const;
};