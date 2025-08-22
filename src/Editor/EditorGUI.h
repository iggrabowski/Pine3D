#pragma once
#include "Utils/Utils.h"

namespace pine {

	class EditorGUI {

	public:
		virtual void Startup() = 0;
		//static std::unique_ptr<EditorGUI> Init();
	};

}
