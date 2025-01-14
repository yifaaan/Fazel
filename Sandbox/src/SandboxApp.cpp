#include <Fazel.h>

class Sandbox : public Fazel::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Fazel::Application* Fazel::CreateApplication()
{
	return new Sandbox;
}