#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>

#include "myvector.h"

using namespace sf;
using namespace std;
using namespace std::chrono;



class Circle
{

private:


	sf::Vector2f  _velocity;
	float         _Acceleration;
	sf::Vector2f  _oldPos;
	sf::Vector2f  _newPos;
	float         bounce;
	float         friction;
	bool          Isimmutable;
	CircleShape   entity;
	float         radius;

public:

	Circle(float radius, Vector2f position, sf::Color color, bool Isimmutable);
	~Circle();

	void uptade(sf::Event& event, const sf::Vector2f& Gravity, float dt);
	void render(sf::RenderWindow* window) const;
	void solveNewPosition(const sf::Vector2f& Gravity, float dt);
	void setNewPos(sf::Vector2f newPos);
	void setOldPos(sf::Vector2f oldPos);
	void solveConstrains(bool isXaxis, const int& constraint);

	float        getRadius()   const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	sf::Vector2f getOldPos()   const;
	sf::Vector2f getNewPos()   const;
};