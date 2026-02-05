workspace "DM"
	architecture"x64"--x64
	configurations{
		"Debug",
		"Release",
	}
	startproject"DM"
	staticruntime "off"  
	language"C++"
	cppdialect "C++20"  
    buildoptions "/utf-8"
outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
ThirdPartBaseDir="%{wks.basedir}/ThirdPart/"
VULKAN_SDK = os.getenv("VULKAN_SDK")
EngineName="DM"
EidtorName="Editor"
GameName="Game"
ThirdPartIncludeDir={}
ThirdPartIncludeDir["spdlog"]=ThirdPartBaseDir.."spdlog/include"
ThirdPartIncludeDir["GLFW"]=ThirdPartBaseDir.."glfw/glfw/include"
ThirdPartIncludeDir["GLAD"]=ThirdPartBaseDir.."glad/glad/include"
ThirdPartIncludeDir["IMGUI"]=ThirdPartBaseDir.."imgui/imgui"
ThirdPartIncludeDir["GLM"]=ThirdPartBaseDir.."glm/glm"
ThirdPartIncludeDir["stb_image"]=ThirdPartBaseDir.."stb_image"
ThirdPartIncludeDir["rapidjson"]=ThirdPartBaseDir.."rapidjson/include"
ThirdPartIncludeDir["json"]=ThirdPartBaseDir.."json"
ThirdPartIncludeDir["entt"]=ThirdPartBaseDir.."entt"
ThirdPartIncludeDir["yaml_cpp"]=ThirdPartBaseDir.."yaml_cpp/yaml_cpp/include"
ThirdPartIncludeDir["ImGuizmo"]=ThirdPartBaseDir.."ImGuizmo/ImGuizmo"
ThirdPartIncludeDir["GeneratedCode"]="%{wks.basedir}/Intermediate/GeneratedCode"
ThirdPartIncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
ThirdPartIncludeDir["shaderc"] = "%{VULKAN_SDK}/Include"
ThirdPartIncludeDir["SPIRV_Cross"] = ThirdPartBaseDir.."SPIRV-Cross/SPIRV-Cross/Include"


LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"



group "Dependencies"
	include "ThirdPart/glfw"
	include "ThirdPart/glad"
	include "ThirdPart/imgui"
	include "ThirdPart/yaml_cpp"
	include "ThirdPart/ImGuizmo"
	-- include "ThirdPart/shaderc"
	include "ThirdPart/SPIRV-Cross"
group""
group "Engine"
	include"CodeGenerator"
	include"DM"
	-- include"DM/Reflection"
	-- include"Editor"
group""
-- include"Game"

	