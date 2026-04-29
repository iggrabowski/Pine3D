#pragma once
#include "Platform/imnodes/NodeEditor.h"

namespace pine {
	class NodeEditorWindow
	{
	public:
		NodeEditorWindow() ;
        void Show(bool p_open, int height);
		void Init();
	};
}

