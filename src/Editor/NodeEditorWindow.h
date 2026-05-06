#pragma once
#include "Platform/imnodes/NodeEditor.h"

enum
{
	DEFAULT_WIDTH = 600
};

namespace pine {
	class NodeEditorWindow
	{
	public:
		NodeEditorWindow() ;
        void Show(bool p_open, int height);
		void Init();
		NodeEditor& GetNodeEditor() { return _nodeEditor; }
	private:
		NodeEditor _nodeEditor;
		int _width = DEFAULT_WIDTH;	
	};
}

