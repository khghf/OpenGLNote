project"DM"
	kind"ConsoleApp"
	targetdir("../bin/"..outputdir.."/%{prj.name}")
	objdir("../bin-int/"..outputdir.."/%{prj.name}")
	pchheader"DMPCH.h"	
	pchsource"%{prj.basedir}/Src/DMPCH.cpp"
	files{
		"Src/**.h",
		"Src/**.cpp",
		ThirdPartBaseDir.."stb_image/**.h",
		ThirdPartBaseDir.."stb_image/**.cpp",
		ThirdPartBaseDir.."json/**.hpp",
		ThirdPartBaseDir.."json/**.cpp",
		ThirdPartBaseDir.."entt/include/**.hpp",
		"%{ThirdPartIncludeDir.GeneratedCode}/**.cpp",
	}
	
	includedirs{
		"%{ThirdPartIncludeDir.spdlog}",
		"%{ThirdPartIncludeDir.GLFW}",
		"%{ThirdPartIncludeDir.GLAD}",
		"%{ThirdPartIncludeDir.IMGUI}",
		"%{ThirdPartIncludeDir.GLM}",
		"%{ThirdPartIncludeDir.stb_image}",
		"%{ThirdPartIncludeDir.rapidjson}",
		"%{ThirdPartIncludeDir.json}",
		"%{ThirdPartIncludeDir.entt}",
		"%{ThirdPartIncludeDir.yaml_cpp}",
		"%{ThirdPartIncludeDir.ImGuizmo}",
		"%{ThirdPartIncludeDir.GeneratedCode}",
		-- "%{ThirdPartIncludeDir.VulkanSDK}",
		"%{ThirdPartIncludeDir.shaderc}",
		"%{ThirdPartIncludeDir.SPIRV_Cross}",
		"./Src",
	}
	
	links{
		"GLFW",
		"GLAD",
		"ImGui",
		"yaml_cpp",
		"ImGuizmo",
		"opengl32.lib",
		-- "Reflect",
		-- "shaderc",
		"SPIRV-Cross",
		-- "GeneratedCode",
		-- "Editor",
	}
	
	filter"files:../Intermediate/**.cpp"
		enablepch"Off"
	filter"system:windows"
		systemversion"latest"
		defines{
			"YAML_CPP_STATIC_DEFINE",--yaml静态库宏
			"DM_PLATFORM_WINDOWS",
			--"DM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		-- postbuildcommands{
		-- 	("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Game")
		-- }
	filter"configurations:Debug"
		defines"DM_DEBUG"
		runtime"Debug"
		symbols"on"
		links
		{
			"%{Library.ShaderC_Debug}",
		}
	filter"configurations:Release"
		defines"DM_RELEASE"
		runtime"Release"
		optimize"on"
		links
		{
			"%{Library.ShaderC_Release}",
		}