#pragma once
#include<ISingletion.h>
#include<assert.h>
#include<Core/Math/Vector.h>
namespace DM
{
	class DM_API Input
	{
	public:
		inline static bool IsKeyPressed(int KeyCode) { return s_Inst->IsKeyPressedImpl(KeyCode); }
		inline static bool IsMouseButtonPressed(int Button) { return s_Inst->IsKeyPressedImpl(Button); }
		inline static Vector2 GetMousePos() { return s_Inst->GetMousePosImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int KeyCode)const = 0;
		virtual bool IsMouseButtonPressedImpl(int Button)const = 0;
		virtual Vector2 GetMousePosImpl()const = 0;
	private:
		static Input* s_Inst;
	};
}