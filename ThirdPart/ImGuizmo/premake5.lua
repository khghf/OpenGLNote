project "ImGuizmo"
    kind "StaticLib"         
   
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
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        runtime "Release"
        optimize "On"