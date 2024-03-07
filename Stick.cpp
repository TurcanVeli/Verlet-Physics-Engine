#pragma once
#include "Stick.h"

Stick::Stick(Circle& circleA, Circle& circleB, float thickness, bool isSpring)
{
	this->_linkedCircles.push_back(&circleA);
	this->_linkedCircles.push_back(&circleB);
	this->_thickness = thickness;
	this->_isSpring = isSpring; //Esnek mi Değil mi?
	this->lenght = MyVectorMath::magnetute(MyVectorMath::distance(circleA.getNewPos(), circleB.getNewPos()));
}

Stick::~Stick()
{
}


void Stick::uptade(sf::Event& event, const sf::Vector2f& Gravity, float dt)
{
	//TODO act like a rope. 

}

void Stick::render(sf::RenderWindow* window)
{

	sf::Vertex line[] = {
		sf::Vertex(this->getLinkedCircles().at(0)->getNewPos()),
		sf::Vertex(this->getLinkedCircles().at(1)->getNewPos())

	};
	line->color = sf::Color::White;
	window->draw(line, 2, sf::Lines);

}


float Stick::getLength() const
{
	return this->lenght;
}



std::vector<Circle*> Stick::getLinkedCircles() const
{
	return this->_linkedCircles;
}