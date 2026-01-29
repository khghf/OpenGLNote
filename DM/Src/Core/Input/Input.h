#pragma once
#include<Core/Math/Vector.h>
#include<Core/Input/KeyCode.h>
namespace DM
{
	class  Input
	{
	public:
		static bool IsKeyPressed(Key code);
		//static bool IsKeyReleased(Key code);
		static bool IsMouseButtonPressed(Key code);
		static Vector2 GetMousePos();
	};
}
