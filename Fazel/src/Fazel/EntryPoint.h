#pragma once

#ifdef FZ_PLATFORM_WINDOWS

extern Fazel::Application* Fazel::CreateApplication();

int main(int argc, char** argv)
{
	printf("Fazel Engine");
	auto app = Fazel::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Fazel only supports Windows!
#endif