// Created by pine on 2023/10/12.

#include "Input/InputHandler.h"
#include "Core/Application.h"
//#include <stdio.h>

namespace pine {

    //void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //    //--------------CONTROLS--------------//
    //    //std::cout << "Button " << key << " pressed" << std::endl;
    //    for (const auto& i : inputHandler->GetListeners()) {
    //        if (action == GLFW_RELEASE) {
    //            i->OnInputAction(InputType::KEYBOARD, (KeyCode)key, KeyAction::KEY_RELEASE);
    //        }
    //        else if (action == GLFW_PRESS)
    //            i->OnInputAction(InputType::KEYBOARD, (KeyCode)key, KeyAction::KEY_PRESS);
    //        //else if (GLFW_REPEAT)
    //        //    i->first->OnInput(i->second, KeyAction::KEY_REPEAT);
    //    }
    //}

    //void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    //    //--------------CONTROLS--------------//
    //    //std::cout << "Button " << key << " pressed" << std::endl;
    //    for (const auto& i : inputHandler->GetListeners()) {
    //        if (action == GLFW_RELEASE) {
    //            i->OnInputAction(InputType::MOUSE, (MouseButtons)button, KeyAction::KEY_RELEASE);
    //        }
    //        else if (action == GLFW_PRESS)
    //            i->OnInputAction(InputType::MOUSE, (MouseButtons)button, KeyAction::KEY_PRESS);
    //        //else if (GLFW_REPEAT)
    //        //    i->first->OnInput(i->second, KeyAction::KEY_REPEAT);
    //    }
    //}

    InputHandler::InputHandler()
    {
        //this->alreadyScrolled = false;
        _zoomPerScroll = 0.2f;
        _moveSpeed = 0.2f;
        _directionSpeedX = 0.1f;
        _directionSpeedY = 0.1f;
    }

    InputHandler::~InputHandler()
    = default;

    UniquePtr<InputHandler> InputHandler::Init()
	{
        return MakeUnique<InputHandler>();
	}

    void InputHandler::OnUpdate()
    {
        /*if (!_initialized) {
            glfwSetKeyCallback(window->GetWindow(), KeyCallback);
            glfwSetMouseButtonCallback(window->GetWindow(), MouseButtonCallback);
            _initialized = true;
        }*/
        //glfwPollEvents();
        ProcessInput();
    }

    void InputHandler::Zoom(const int delta) const
    {
        Camera& camera = Application::renderer->GetRenderCamera();
        glm::vec3 pos = camera.GetPos();
        glm::vec3 dir = camera.GetDirection();

        //move in camera direction
        camera.SetPos(static_cast<float>(delta) * (dir * _zoomPerScroll) + pos);
    }

    void InputHandler::ChangeDirection(int xpos, int yPosition)
    {
        //Camera& camera = renderer->GetRenderCamera();
        //glm::vec3 dir = camera.GetDirection();
        //glm::vec2 deltaDir(x * m_directionSpeedX, y * m_directionSpeedY);
        //glm::vec3 vec3(dir.x, dir.y, dir.z);

        //vec3 = Rotate<glm::vec3>(vec3, deltaDir.x, camera.up);
        ////@bug when trying to rotate more than up or down camera flickers
        //vec3 = Rotate<glm::vec3>(vec3, deltaDir.y, Cross(dir, camera.up));
        //        
        //camera.SetDirection(vec3);
    }

    void InputHandler::AddListener(InputListener* listener)
    {
        auto i = std::find(_listeners.begin(), _listeners.end(), listener);
        if (i == _listeners.end())
            _listeners.push_back(listener);
        else {};
            // Listener already registered
    }

    void InputHandler::RemoveListener(const InputListener* listener)
    {
        auto i = std::ranges::find(_listeners, listener);
        if (i != _listeners.end())
            _listeners.erase(i);
    }

    void InputHandler::AddActionCallback(const std::string& actionName, const ActionCallback& callback)
    {
        _actionCallbacks[actionName].emplace_back(callback);
    }

    void InputHandler::RemoveActionCallback(const std::string& actionName, const std::string& callbackRef)
    {      
        std::erase_if(_actionCallbacks[actionName], [callbackRef](const ActionCallback& callback) {
            return callback.ref == callbackRef;
        });
    }

    void InputHandler::MapInputToAction(const KeyCode key, const std::string& action)
    {
		_inputActionMapping[key].emplace(action);
	}

    void InputHandler::UnmapInputFromAction(const KeyCode key, const std::string& action)
    {
		_inputActionMapping[key].erase(action);
    }

    void InputHandler::ProcessInput()
    {
			std::vector<ActionEvent> action_events;
	    for (auto& input_device : _inputDevices)
        {
			// get the current state of the input device
            auto new_state = input_device->state_func();
            
			// compare old and new state
			for (const auto& [first, second] : new_state)
			{
                if (constexpr float epsilon = 1e-5f; glm::abs(input_device->states[first].value - second.value < epsilon))
                {
                    for (const auto& action_event : GenerateActionEvent(input_device->index, first, input_device->states[first].value))
                    {
                        action_events.emplace_back(action_event);
                        input_device->states[first].value = second.value;
                    }
                }
            }
        }

		// propagate action events to listeners
		for (const auto& action_event : action_events)
		{
            PropagateActionEvent(action_event);
		}
    }

	// TODO: implement this function
    void InputHandler::PropagateActionEvent(const ActionEvent& actionEvent)
	{
       for (size_t i = _actionCallbacks[actionEvent.action_name].size() - 1; i >=0; i--)
       {
		   auto& callback = _actionCallbacks[actionEvent.action_name][i];
           if (callback.func(actionEvent.device_index, actionEvent.new_value)) break;
       }
	}

    void InputHandler::RegisterDevice(const std::shared_ptr<InputDevice>& device)
    {
        // TODO ERROR INPUT HANDLER NOT INITIALIZED YET
        _inputDevices.emplace_back(device);
    }

    void InputHandler::UnregisterDevice(int deviceIndex, InputDeviceType type)
    {
		erase_if(_inputDevices, [type, deviceIndex](const std::shared_ptr<InputDevice>& device) {
			return device->type == type && device->index == deviceIndex;
		});
    }

    // deprecated
    bool InputHandler::IsKeyPressed(const KeyCode keyCode)
    {
	    if (const int state = glfwGetKey(Application::window->GetWindow(), keyCode); state == GLFW_PRESS) {
            return true;
        }
        return false;
    }

    std::vector<InputHandler::ActionEvent> InputHandler::GenerateActionEvent(const int deviceIndex, const KeyCode keyCode, const float newVal)
    {
		std::vector<ActionEvent> action_events;

		const auto& actions = _inputActionMapping[keyCode];

        for (const auto& action : actions) {
            action_events.emplace_back(ActionEvent {
                .device_index = deviceIndex,
                .new_value = newVal,
                .action_name = action
                });
        }
        return action_events;
    }

	// deprecated
    bool InputHandler::IsMouseButtonPressed(MouseButtons mouseCode)
    {
        if (glfwGetMouseButton(Application::window->GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            return true;
        }
        return false;
    }

}