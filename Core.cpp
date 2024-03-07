#include "Core.h"
#include "Solver.h";


Core::Core()
{
	this->initVariables();
	this->initWindow();

}

Core::~Core()
{
	delete this->window;

	this->window = { nullptr };
}

void Core::initWindow()
{
	this->window = new RenderWindow(this->videoMode, "Verlet Engine");
	ImGui::SFML::Init(*this->window);
	this->window->setFramerateLimit(60);
}


void Core::initVariables()
{
	this->height = 800;
	this->width = 1024;
	this->videoMode = VideoMode(this->width,this->height );
	this->window = { nullptr };

	this->Entity_State = state::EMPTY;
	this->Sim_State = state::PLAY;
	this->Stick_State = state::NOTSTARTED;
	this->Mouse_State = state::PRESSED;
	this->Button_State = state::LEFT;
	this->isSpring = false;
	this->isImmutable = false;
	this->isPLaying = false;

	this->CircleRadius = 5.f;
	this->Gforce_M = 1000.f;
	this->GForce_V = { 0.f, this->Gforce_M };


	this->m_time = 0.0f;
	this->m_frame_dt = 1.0f / static_cast<float>(60);
	this->m_sub_steps = 8;

}



float Core::getElapsedTime()
{
	return this->clock.restart().asSeconds();
}

void Core::Gui()
{
	ImGui::Begin("Play Around");
	ImGui::Text("Simple Simulation");
	if (this->Sim_State == state::STOP)
	{
		if (ImGui::Button("Play", ImVec2(100, 25)))
		{
			this->Sim_State = state::PLAY;

		}

	}
	else if (this->Sim_State == state::PLAY)
	{
		if (ImGui::Button("Stop", ImVec2(100, 25)))
		{
			this->Sim_State = state::STOP;

		}
	}

	if (ImGui::Button("Add Circle", ImVec2(100, 25)))
	{
		this->Entity_State = state::CIRCLE;

	}

	ImGui::Checkbox("Immutable", &this->isImmutable);
	if (ImGui::Button("Add Stick", ImVec2(100, 25)))
	{
		this->Entity_State = state::STICK;
	}
	ImGui::SliderFloat("Radius", &this->CircleRadius, 0001.f, 100.f);
	if (ImGui::Button("Clear", ImVec2(100, 25)))
	{
		this->Entity_State = state::EMPTY;
		this->Sim_State = state::STOP;
		this->deleteAllCircles();
		this->deleteAllStick();
	}

	ImGui::SliderFloat("Gravity", &this->Gforce_M, 100.f, 5000.f);

	ImGui::End();

}



void Core::addEntity()
{
	if (this->Entity_State == state::EMPTY)
	{
		return;

	}
	else if (this->Entity_State == state::CIRCLE)
	{
		this->addCircle();
	}
	else if (this->Entity_State == state::STICK)
	{
		this->addStick();
	}
}

void Core::addCircle()
{
	Circle* newCircle = new Circle(this->CircleRadius, this->mousePosView, sf::Color::White, this->isImmutable);
	this->Circles.push_back(newCircle);

}

void Core::addStick()
{

	for (Circle* circle : this->Circles)
	{
		if (circle->getRadius() >= MyVectorMath::magnetute(this->mousePosView - circle->getNewPos()))
		{
			this->Stick_State = state::CONTINUE;
			this->Sticks_Circles.push_back(circle);

			if (this->Sticks_Circles.size() == 2)
			{
				this->Stick_State = state::DONE;
				Stick* stick = new Stick(*this->Sticks_Circles.at(0), *this->Sticks_Circles.at(1), 1, this->isSpring);
				this->Sticks.push_back(stick);
				this->Stick_State = state::DONE;
				this->Sticks_Circles.clear();
			}
			return;

		}

	}
	this->Stick_State = state::CIRCLENOTFOUND;
}

void Core::deleteAllCircles()
{
	for (int i = 0; i < this->Circles.size(); i++)
	{
		delete this->Circles.at(i);
		this->Circles.at(i) = { nullptr };
	}
	this->Circles.clear();
}

void Core::deleteAllStick()
{
	for (auto stick : this->Sticks)
	{
		delete stick;
		stick = { nullptr };

	}
	this->Sticks.clear();

}


void Core::updateMousePos()
{
	this->MousePos = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->MousePos);
}



void Core::update()
{

	//this->clock.restart();
	this->m_time += this->m_frame_dt;
	const float step_dt = getStepDt();

	for (uint32_t i(this->m_sub_steps); i--;)
	{
		for (int j = 0; j < this->Circles.size(); j++)
		{
			this->GForce_V.y = this->Gforce_M;

			this->Circles.at(j)->uptade(this->event, this->GForce_V, step_dt);
			for (int i = j + 1; i < this->Circles.size(); i++)
			{
				physics::Solver::CollisionSolver(*this->Circles.at(j), *this->Circles.at(i));
			}
			physics::Solver::ConstrainSolver(*this->Circles.at(j), this->height, this->width);

		}
		for (int i = 0; i < this->Sticks.size(); i++)
		{
			this->Sticks.at(i)->uptade(this->event, this->GForce_V, step_dt);

			
			physics::Solver::RigitBodySolver(*this->Sticks.at(i));
		}

	}

}


void Core::render()
{
	this->window->clear(sf::Color::Black);


	for (int i = 0; i < this->Circles.size(); i++)
	{
		this->Circles.at(i)->render(this->window);

	}
	for (int i = 0; i < this->Sticks.size(); i++)
	{
		this->Sticks.at(i)->render(this->window);

	}
	
	ImGui::SFML::Render(*this->window);
	this->window->display();
}


void Core::pollEvent()
{
	while (this->window->pollEvent(this->event)) {

		ImGui::SFML::ProcessEvent(this->event);
		switch (this->event.type)
		{
		case(Event::Closed()):
			this->window->close();
			break;

		case(sf::Event::MouseButtonReleased):

			this->Mouse_State = state::RELEASED;
			if (this->Mouse_State == state::RELEASED)
			{
				if(this->Button_State == state::RIGHT)
				{
					this->deleteCircle();
				
				}


				if (this->Entity_State == state::STICK && this->Button_State == state::LEFT)
				{
					this->addStick();

				}

				if (this->Stick_State == state::CIRCLENOTFOUND && this->Button_State == state::LEFT)
				{
					if (this->Sticks_Circles.size() >= 1)
					{
						this->Sticks_Circles.clear();
					}
				}
			}


		case(sf::Event::MouseButtonPressed):
		{
			if (this->Mouse_State == state::PRESSED)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{

					this->Button_State = state::LEFT;
					this->addEntity();
					if (this->Stick_State == state::CIRCLENOTFOUND)
					{
						this->Sticks_Circles.clear();
					}
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					this->Button_State = state::RIGHT;
					//TODO 
				}
			}
			this->Mouse_State = state::PRESSED;
		}

		default:
			break;

		}
	}


}

void Core::deleteCircle()
{
	for (int i = 0;i<this->Circles.size(); i++)
	{
		if (this->Circles.at(i)->getRadius() >= MyVectorMath::magnetute(this->mousePosView - this->Circles.at(i)->getNewPos()))
		{
			delete this->Circles.at(i);
			this->Circles.at(i) = { nullptr };
			std::cout << "Deleted" << std::endl;
			this->Circles.erase(this->Circles.begin() + i);
			for(int j = 0; j < this->Sticks.size(); j++)
			{
				if(this->Sticks.at(j)->getLinkedCircles().at(0) == this->Circles.at(i))
				{
					this->Sticks.at(j)->getLinkedCircles().erase(this->Sticks.at(j)->getLinkedCircles().begin());
				}else if(this->Sticks.at(j)->getLinkedCircles().at(1) == this->Circles.at(i))
				{
					this->Sticks.at(j)->getLinkedCircles().erase(std::next(this->Sticks.at(j)->getLinkedCircles().begin()));
				}
			}
		}
	}
}



bool Core::isRunning() const
{
	return this->window->isOpen();
}