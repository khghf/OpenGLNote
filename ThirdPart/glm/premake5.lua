--[[
project"GLM"
    kind "HeaderOnly"       -- 声明为仅头文件库（无编译目标）
    language "C++"
    files {
        "glm/**.h",
        "glm/**.hpp"
    }
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")
    -- 编译配置优化（Debug/Release 区分）
    filter "configurations:Debug"
        symbols "On"
    filter "configurations:Release"
        optimize "On"
]]--
