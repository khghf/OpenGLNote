project "GLAD"
    kind "StaticLib"  -- 保持静态库（若要动态库改为 SharedLib，需同步修改宏）
    language "C"
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    -- 关键 1：包含 GLFW 最新版所有核心文件（按源码原生结构，不遗漏）
    files {
       "glad/include/GLAD/glad.h",
       "glad/include/KHR/khrplatform.h",
       "glad/src/glad.c"
    }
    includedirs{
        "glad/include"
    }
    filter "system:windows"
        systemversion "latest"  -- 使用最新 Windows SDK
        staticruntime "On"      -- 静态运行时（与主项目保持一致）
    filter "configurations:Debug"
        symbols "On"
    filter "configurations:Release"
        optimize "On"
    filter{"system:windows","configurations:Release"}
        buildoptions"/MT"
