workspace "DM"--�����������
	architecture"x64"--x64ƽ̨
	configurations{--����ѡ��
		"Debug",
		"Release",
		"Dist"
	}
	startproject"Game"
outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
ThirdPartBaseDir="DM/ThirdPart/"
ThirdPartIncludeDir={}
ThirdPartIncludeDir["spdlog"]=ThirdPartBaseDir.."spdlog/include"
ThirdPartIncludeDir["GLFW"]=ThirdPartBaseDir.."glfw/glfw/include"
ThirdPartIncludeDir["GLAD"]=ThirdPartBaseDir.."glad/glad/include"
ThirdPartIncludeDir["IMGUI"]=ThirdPartBaseDir.."imgui/imgui"
ThirdPartIncludeDir["GLM"]=ThirdPartBaseDir.."glm/glm"
include "DM/ThirdPart/glfw"
include "DM/ThirdPart/glad"
include "DM/ThirdPart/imgui"
--include"ThirdPart/glm"
project"DM"
	location"DM"--��Ŀ���ŵ�λ��(����ڽ������)
	kind"StaticLib"
	language"C++"
	staticruntime"on"
	buildoptions"/utf-8"--c/c++ ������������ѡ��
	targetdir("bin/"..outputdir.."/%{prj.name}")--���Ŀ¼
	objdir("bin-int/"..outputdir.."/%{prj.name}")--obj�ļ����Ŀ¼
	pchheader"DMPCH.h"
	pchsource"DM/Src/DMPCH.cpp"
	files{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}
	includedirs{--���Ӱ���Ŀ¼
		"%{ThirdPartIncludeDir.spdlog}",
		"%{ThirdPartIncludeDir.GLFW}",
		"%{ThirdPartIncludeDir.GLAD}",
		"%{ThirdPartIncludeDir.IMGUI}",
		"%{ThirdPartIncludeDir.GLM}",
		"%{prj.name}/Src",
	}
	links{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}
	filter"system:windows"
		cppdialect"C++17"
		systemversion"latest"
		defines{--Ԥ�������ĺ궨��
		
			"DM_PLATFORM_WINDOWS",
			"DM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		-- postbuildcommands{--�󹹽�����
		
		-- 	("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Game")
		-- }
	filter"configurations:Debug"
		defines"DM_DEBUG"
		runtime"Debug"
		symbols"on"--������ʽ
	filter"configurations:Release"
		defines"DM_RELEASE"
		runtime"Release"
		optimize"on"--�����Ż�
project"Game"
	location"Game"
	kind"ConsoleApp"
	language"C++"
	cppdialect"C++17"
	staticruntime"on"
	buildoptions"/utf-8"
	targetdir("bin/"..outputdir.."/%{prj.name}")	
	objdir("bin-int/"..outputdir.."/%{prj.name}")
	files{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}
	includedirs{
		"%{ThirdPartIncludeDir.spdlog}",
		"%{ThirdPartIncludeDir.GLM}",
		"%{ThirdPartIncludeDir.GLFW}",
		"%{ThirdPartIncludeDir.IMGUI}",
		"DM/Src"
	}
	links{
		"DM"
	}
	filter"system:windows"
		staticruntime"on"
		systemversion"latest"
		defines{
			"DM_PLATFORM_WINDOWS"
		}
	filter"configurations:Debug"
		defines"DM_DEBUG"
		runtime"Debug"
		symbols"on"
	filter"configurations:Release"
		defines"DM_RELEASE"
		runtime"Release"
		optimize"on"
	