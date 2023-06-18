#pragma once

// Core components
#include "Ruby/Utility/Pointers.h"
#include "Ruby/Main/Core.h"
#include "Ruby/Main/Logging.h"
#include "Ruby/Main/Time.h"
#include "Ruby/Main/App.h"
#include "Ruby/Main/Window.h"
#include "Ruby/Main/Input.h"


// Rendering
#include "Ruby/Render/Renderer.h"
#include "Ruby/Render/Buffers.h"
#include "Ruby/Render/VertexArray.h"
#include "Ruby/Render/Shader.h"
#include "Ruby/Render/Texture.h"
#include "Ruby/Render/Camera.h"



// For entry/main
#define RUBY_MAIN_FUNCTION_ENTRY(AppClassName, MainDir) int main(int argc, char** argv)\
		{\
			::Ruby::Logger::init();\
			::Ruby::Time::init();\
			AppClassName app(argc, argv, MainDir);\
			app.run();\
		}