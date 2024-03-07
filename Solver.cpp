#include "Solver.h"




physics::Solver::~Solver()
{
}



void physics::Solver::CollisionSolver(Circle& circleA, Circle& circleB)
{
	const float        response_coef = 0.75f;
	const sf::Vector2f v             = circleA.getNewPos() - circleB.getNewPos();
	const float        dist2         = v.x * v.x + v.y * v.y;
	const float        min_dist      = circleA.getRadius() + circleB.getRadius();
	if (dist2 < min_dist * min_dist)
	{
		const float        dist         = sqrt(dist2);
		const sf::Vector2f n            = v / dist;
		const float        mass_ratio_a = circleA.getRadius() / (circleA.getRadius() + circleB.getRadius());
		const float        mass_ratio_b = circleB.getRadius() / (circleA.getRadius() + circleB.getRadius());
		const float        delta        = 0.5f * response_coef * (dist - min_dist);

		circleA.setNewPos(circleA.getNewPos() - (mass_ratio_b * delta) * n);
		circleB.setNewPos(circleB.getNewPos() + (mass_ratio_a * delta) * n);

	}

}

void physics::Solver::ConstrainSolver(Circle& circle, float const& height, float const& width)
{
	Vector2f pos = circle.getPosition();
	float radius = circle.getRadius();


	if (pos.x + radius >= width)
	{
		circle.solveConstrains(true, width);

	}
	if (pos.x - radius <= 0)
	{
		circle.solveConstrains(true, 0);
	}

	if (pos.y + radius >= height)
	{
		circle.solveConstrains(false, height);

	}
	if (pos.y - radius <= 0)
	{
		circle.solveConstrains(false, 0);
	}


}

void physics::Solver::RigitBodySolver(Stick& stick)
{

	Circle* circleA = stick.getLinkedCircles().at(0);
	Circle* circleB = stick.getLinkedCircles().at(1);
	sf::Vector2f V_distance = MyVectorMath::distance(circleB->getNewPos(), circleA->getNewPos());
	float Scalar_distance = MyVectorMath::magnetute(V_distance);

	float const target = stick.getLength();

	sf::Vector2f n = MyVectorMath::normalize(V_distance);
	float delta = Scalar_distance - target;

	circleB->setNewPos(circleB->getNewPos() - (0.5f * delta * n));
	circleA->setNewPos(circleA->getNewPos() + (0.5f * delta * n));


}