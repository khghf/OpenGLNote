#pragma once
#include "GObject.h"
#include<GInfo.gen.h>
namespace DM
{
	class CLASS() GInfo :public GObject
	{
		REFLECT_BODY()
	};
}


