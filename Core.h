#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>

#include "myvector.h"
#include "Circle.h"
#include "Stick.h";

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"




using namespace std;
using namespace sf;

namespace state
{
	enum      SIMULATION_STATE { PLAY = 0, STOP };
	enum      ENTITY_STATE { EMPTY = 0, CIRCLE, STICK };
	enum      STICK_STATE { NOTSTARTED, CONTINUE, CIRCLENOTFOUND, ERROR, DONE };
	enum      MOUSE_STATE { PRESSED, RELEASED };
	enum      BUTTON_STATE { LEFT, RIGHT };

}

class Core
{
private:
	void initWindow();
	void initVariables();
	float getElapsedTime();
	float CircleCount;
	bool isPLaying;



public:
	Core();
	~Core();

	RenderWindow* window;
	VideoMode					videoMode;
	Event						event;
	int							width;
	sf::Clock					clock;
	int							height;
	state::SIMULATION_STATE		Sim_State;
	state::ENTITY_STATE			Entity_State;
	state::STICK_STATE			Stick_State;
	state::MOUSE_STATE			Mouse_State;
	state::BUTTON_STATE         Button_State;
	Vector2i					MousePos;
	Vector2f					mousePosView;
	vector<Circle*>				Circles;
	bool						isImmutable;
	bool						isSpring;
	float						CircleRadius;
	vector<Stick*>				Sticks;
	vector<Circle*>				Sticks_Circles;
	MyVectorMath				vector;

	sf::Vector2f                GForce_V;
	float                       Gforce_M;


	float						m_time;
	float						m_frame_dt;
	uint32_t					m_sub_steps;


	void Gui();
	void addEntity();
	void addCircle();

	void addStick();
	void deleteAllCircles();
	void deleteAllStick();
	void updateMousePos();
	void update();
	void render();
	void pollEvent();
	void deleteCircle();
	void deleteStick();
	bool isRunning() const;



	[[nodiscard]]
	float getTime() const
	{
		return this->m_time;
	}

	[[nodiscard]]
	float getStepDt() const
	{
		return this->m_frame_dt / static_cast<float>(this->m_sub_steps);
	}
	
	void setSimulationUpdateRate(uint32_t rate)
	{
		this->m_frame_dt = 1.0f / static_cast<float>(rate);
	}
	
	



};