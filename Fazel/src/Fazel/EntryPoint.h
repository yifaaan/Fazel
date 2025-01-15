#pragma once

#ifdef FZ_PLATFORM_WINDOWS

extern Fazel::Application* Fazel::CreateApplication();

int main(int argc, char** argv)
{
	Fazel::Log::Init();
	FZ_CORE_WARN("Initialized log!");
	int a = 1;
	FZ_INFO("Initialized log! a = {}", a);
	
	auto app = Fazel::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Fazel only supports Windows!
#endif