project "GLFW"
    kind "StaticLib"  -- 保持静态库（若要动态库改为 SharedLib，需同步修改宏）
    language "C"
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    -- 关键 1：包含 GLFW 最新版所有核心文件（按源码原生结构，不遗漏）
    files {
        -- 公共头文件（GLFW 对外暴露的头文件）
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
        -- GLFW 内部核心文件（最新版必需，之前漏了！）
        "glfw/src/*.h",          -- 所有内部头文件（internal.h、platform.h 等）
        "glfw/src/*.c",          -- 所有内部核心源码（context.c、init.c 等）
        -- Windows 平台专属文件（最新版原生支持，无需手动筛选）
        "glfw/src/win32/*.h",    -- Windows 内部头文件（win32_platform.h 等）
        "glfw/src/win32/*.c",    -- Windows 平台实现（包含正确的 _glfwSelectPlatform）
    }

    -- 关键 2：正确配置包含目录（让 GLFW 源码能找到自身头文件）
    includedirs {
        "include",              -- 公共头文件目录（供你的主项目调用）
        "glfw/src",             -- GLFW 内部核心头文件目录（src/*.h）
        "glfw/src/win32"        -- Windows 平台内部头文件目录（src/win32/*.h）
    }

    -- 关键 3：Windows 平台编译配置（匹配最新版 GLFW 要求）
    filter "system:windows"
        systemversion "latest"  -- 使用最新 Windows SDK
        staticruntime "On"      -- 静态运行时（与主项目保持一致）
        defines {
            "_GLFW_WIN32=1",            -- 强制启用 Windows 平台（最新版依赖）
            "_CRT_SECURE_NO_WARNINGS",  -- 禁用 CRT 安全警告
            "_WIN32_WINNT=0x0601",      -- 最低支持 Windows 7（GLFW 3.4+ 要求）
            "UNICODE", "_UNICODE",      -- 启用 Unicode（Windows 平台必需）
            "_GLFW_BUILD_STATIC=1"      -- 关键：告诉 GLFW 编译静态库（匹配 kind "StaticLib"）
        }
        -- 最新版 GLFW Windows 必需的系统库（按官方文档）
        links {
            "gdi32",    -- 图形设备接口
            "user32",   -- 窗口管理
            "kernel32", -- 内核功能（线程/内存）
            "shell32",  -- 系统壳功能
            "ole32",    -- COM 组件（剪贴板/IME）
            "advapi32", -- 高级 API（权限/注册表）
            "imm32",    -- 输入法支持
            "hid",      -- 手柄 HID 设备支持
            "winmm"     -- 多媒体定时器（最新版新增依赖）
        }

    -- 关键 4：排除非 Windows 平台文件（避免编译冲突）
    filter "system:not windows"
        removefiles {
            "glfw/src/win32/*",  -- 非 Windows 平台时，排除 Windows 相关文件
        }

    -- 编译配置优化（Debug/Release 区分）
    filter "configurations:Debug"
        symbols "On"
        defines { "GLFW_DEBUG=1" }  -- 启用 GLFW 调试模式（可选，便于排查问题）
    filter "configurations:Release"
        optimize "Full"
        defines { "GLFW_RELEASE=1" }