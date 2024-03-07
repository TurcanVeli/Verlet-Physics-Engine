#pragma once



#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

static struct MyVectorMath
{

	static float magnetute(Vector2f A);

	static Vector2f distance(Vector2f A, Vector2f B);

	static Vector2f normalize(Vector2f A);

	static float dot(Vector2f A, Vector2f B);

	static Vector2f cross(Vector2f A, Vector2f B);

};