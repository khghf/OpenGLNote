project "yaml_cpp"
    kind "StaticLib"         
    language "C++"
    cppdialect "C++17"        
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    defines {
        "YAML_CPP_STATIC_DEFINE",  -- 关键！yaml-cpp 静态库必需宏
        "_SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING",  -- 屏蔽 VS 警告
        "_CRT_SECURE_NO_WARNINGS"  -- 屏蔽 CRT 安全函数警告（可选）
    }
    files {
        "yaml_cpp/include/**.h",
        "yaml_cpp/src/**.h",
        "yaml_cpp/src/**.cpp"
    }
    removefiles {
        "yaml_cpp/src/test/**.*",
        "yaml_cpp/src/tools/**.*"
    }

    -- 包含目录
    includedirs {
        "yaml_cpp/include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "on"  -- 静态运行时（/MTd 或 /MT），与引擎统一
        buildoptions {
            "/wd4251",  -- 屏蔽 STL 类型未导出 DLL 接口警告
            "/wd4273",  -- 屏蔽 DLL 链接不一致警告
            "/wd4275"   -- 屏蔽非 DLL 接口类作为基类警告
        }

    -- Debug 配置
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "DEBUG", "_DEBUG" }

    -- Release 配置
    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        defines { "NDEBUG" }