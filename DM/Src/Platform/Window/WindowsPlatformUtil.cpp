#include "DMPCH.h"
#ifdef DM_PLATFORM_WINDOWS
#include<commdlg.h>
#include <Tool/Util/PlatformUtils.h>
#include <Tool/Util/Util.h>
#include<glfw/glfw3native.h>
#include <string.h>
namespace DM
{
	std::string FileDialog::OpenFile(const char* filter)
	{
		OPENFILENAME ofn = { 0 };
		WCHAR szFile[MAX_PATH] = { 0 };  // 存储选中的文件路径（MAX_PATH 对应 Windows 最大路径长度）

		// 2. 配置 OPENFILENAME 结构体参数
		ofn.lStructSize = sizeof(OPENFILENAME);  // 结构体大小（必须设置，否则函数调用失败）
		ofn.hwndOwner = NULL;  // 父窗口句柄（NULL 表示无父窗口，对话框居中显示）
		ofn.lpstrFile = szFile;  // 接收文件路径的缓冲区
		ofn.nMaxFile = sizeof(szFile) / sizeof(WCHAR);  // 缓冲区最大长度（以宽字符为单位）
		std::wstring wfilter = Util::StringToWString_U8(filter);
		ofn.lpstrFilter = wfilter.c_str();  // 文件筛选器（格式见下方说明）
		ofn.nFilterIndex = 1;  // 默认选中的筛选器索引（从 1 开始）
		ofn.lpstrTitle = L"选择文件";  // 对话框标题
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_NOCHANGEDIR;
		// 标志说明：
		// - OFN_PATHMUSTEXIST：必须选择存在的路径（禁止输入无效路径）
		// - OFN_FILEMUSTEXIST：必须选择存在的文件（禁止输入不存在的文件名）
		// - OFN_HIDEREADONLY：隐藏「只读」复选框

		// 3. 调用 GetOpenFileName 显示文件对话框
		if (GetOpenFileName(&ofn))
		{
			// 对话框确认选择，返回选中的文件路径（宽字符串）
			return Util::WStringToString_U8(ofn.lpstrFile);
		}
		else
		{
			// 取消选择或调用失败，返回空字符串
			DWORD error = CommDlgExtendedError();  // 获取详细错误码（可选，用于调试）
			if (error != 0)
			{
				std::wcerr << L"文件对话框调用失败，错误码：" << error << std::endl;
			}
			return {};
		}
		return {};
	}
	std::string FileDialog::SaveFile(const char* filter )
	{
		OPENFILENAME ofn = { 0 };
		WCHAR szFile[MAX_PATH] = { 0 };  // 存储选中的文件路径（MAX_PATH 对应 Windows 最大路径长度）

		// 2. 配置 OPENFILENAME 结构体参数
		ofn.lStructSize = sizeof(OPENFILENAME);  // 结构体大小（必须设置，否则函数调用失败）
		ofn.hwndOwner = NULL;  // 父窗口句柄（NULL 表示无父窗口，对话框居中显示）
		ofn.lpstrFile = szFile;  // 接收文件路径的缓冲区
		ofn.nMaxFile = sizeof(szFile) / sizeof(WCHAR);  // 缓冲区最大长度（以宽字符为单位）
		std::wstring wfilter = Util::StringToWString_U8(filter);
		ofn.lpstrFilter = wfilter.c_str();  // 文件筛选器（格式见下方说明）
		ofn.nFilterIndex = 1;  // 默认选中的筛选器索引（从 1 开始）
		ofn.lpstrTitle = L"选择文件";  // 对话框标题
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		// 标志说明：
		// - OFN_PATHMUSTEXIST：必须选择存在的路径（禁止输入无效路径）
		// - OFN_FILEMUSTEXIST：必须选择存在的文件（禁止输入不存在的文件名）
		// - OFN_HIDEREADONLY：隐藏「只读」复选框

		// 3. 调用 GetOpenFileName 显示文件对话框
		if (GetSaveFileName(&ofn))
		{
			// 对话框确认选择，返回选中的文件路径（宽字符串）
			return Util::WStringToString_U8(ofn.lpstrFile);
		}
		else
		{
			// 取消选择或调用失败，返回空字符串
			DWORD error = CommDlgExtendedError();  // 获取详细错误码（可选，用于调试）
			if (error != 0)
			{
				std::wcerr << L"文件对话框调用失败，错误码：" << error << std::endl;
			}
			return {};
		}
		return {};
	}
}
#endif // DM_PLATFORM_WINDOWS

