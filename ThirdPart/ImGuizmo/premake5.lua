project "ImGuizmo"
    kind "StaticLib"         
    language "C++"
    cppdialect "C++17"        
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files {
        "ImGuizmo/ImGuizmo.h",
        "ImGuizmo/ImGuizmo.cpp",
    }
    -- 包含目录
    includedirs {
        "ImGuizmo/example"
    }
    filter "system:windows"
        systemversion "latest"
        staticruntime "on"  -- 静态运行时（/MTd 或 /MT），与引擎统一
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        runtime "Release"
        optimize "On"