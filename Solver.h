
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "myvector.h"
#include "Circle.h"
#include "Stick.h"


using namespace sf;
using namespace std;

namespace physics
{
	static class Solver
	{

	public:
		Solver() = default;
		~Solver();

		static void    CollisionSolver(Circle& circleA, Circle& circleB);
		static void    ConstrainSolver(Circle& circle, float const& height, float const& width);
		static void    RigitBodySolver(Stick& stick);
	};

};