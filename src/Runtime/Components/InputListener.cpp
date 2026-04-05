#include "Runtime/Components/InputListener.h"
#include "Core/Application.h"

namespace pine {
	InputListener::InputListener()
	{
		Application::inputHandler->AddListener(this);
	}
	InputListener::~InputListener()
	{
		Application::inputHandler->RemoveListener(this);
	}
}
