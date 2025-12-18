#include "DMPCH.h"
#include "Util.h"
namespace Util
{
	template<class T>
	T* GetInst()
	{
		return T:: template GetInst();
	}
}