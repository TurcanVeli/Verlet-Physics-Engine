#include "Circle.h"




Circle::Circle(float radius, Vector2f position, sf::Color color, bool Isimmutable)
{
	this->Isimmutable = Isimmutable;
	this->bounce = 0.5f;
	this->friction = 0.999f;
	this->radius = radius;


	this->entity.setPosition(position);
	this->entity.setRadius(this->radius);
	this->entity.setOrigin(this->radius, this->radius);
	if(Isimmutable)
	{
		this->entity.setFillColor(sf::Color::Red);
	
	}else
	{
		this->entity.setFillColor(color);
	
	}

	this->_newPos = this->getPosition();
	this->_oldPos = this->_newPos;
	this->_velocity = this->_newPos - this->_oldPos;
}

Circle::~Circle()
{
}




sf::Vector2f Circle::getPosition() const
{
	return this->entity.getPosition();
}


float Circle::getRadius() const
{
	return this->entity.getRadius();
}




sf::Vector2f Circle::getVelocity() const
{
	return this->_velocity;
}


void Circle::solveNewPosition(const sf::Vector2f& Gravity, float dt)
{
	if (!this->Isimmutable)
	{
		
		this->_velocity = this->_newPos - this->_oldPos;
		this->_velocity *= this->friction;
		this->_oldPos = this->_newPos;
		this->_newPos += this->_velocity + Gravity * (dt * dt);


		this->entity.setPosition(this->_newPos);

	}

}

void Circle::setNewPos(sf::Vector2f newPos)
{
	this->_newPos = newPos;
}

void Circle::setOldPos(sf::Vector2f oldPos)
{
	this->_oldPos = oldPos;
}

sf::Vector2f Circle::getOldPos() const
{
	return this->_oldPos;
}

sf::Vector2f Circle::getNewPos() const
{
	if (this->Isimmutable)
	{
		return this->getPosition();
	}
	return this->_newPos;
}

void Circle::solveConstrains(bool isXaxis, const int& constraint)
{
	if (!this->Isimmutable)
	{
		float* value = new float(0);

		if (constraint == 0)
		{
			*value = constraint + this->getRadius();
		}
		else
		{
			*value = constraint - this->getRadius();
		}


		if (isXaxis)
		{
			this->_newPos.x = *value;
			this->_oldPos.x = this->_newPos.x + this->getVelocity().x * this->bounce;

		}
		else
		{
			this->_newPos.y = *value;
			this->_oldPos.y = this->_newPos.y + this->getVelocity().y * this->bounce;
		}

		delete value;
		value = { nullptr };

	}
}




void Circle::uptade(sf::Event& event, const sf::Vector2f& Gravity, float dt)
{
	this->solveNewPosition(Gravity, dt);

}


void Circle::render(sf::RenderWindow* window) const
{
	window->draw(this->entity);
}


