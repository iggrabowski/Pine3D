#include "Runtime/Components/InputListener.h"
#include "Core/Application.h"

namespace Pine {
	InputListener::InputListener()
	{
		inputHandler->AddListener(this);
	}
	InputListener::~InputListener()
	{
		inputHandler->RemoveListener(this);
	}
}
