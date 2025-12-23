project "GLAD"
    kind "StaticLib"  -- ���־�̬�⣨��Ҫ��̬���Ϊ SharedLib����ͬ���޸ĺ꣩
    language "C"
    staticruntime "on"      -- ��̬����ʱ��������Ŀ����һ�£�
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")
    -- �ؼ� 1������ GLFW ���°����к����ļ�����Դ��ԭ���ṹ������©��
    files {
       "glad/include/GLAD/glad.h",
       "glad/include/KHR/khrplatform.h",
       "glad/src/glad.c"
    }
    includedirs{
        "glad/include"
    }
    filter "system:windows"
        systemversion "latest"  -- ʹ������ Windows SDK
    filter "configurations:Debug"
        runtime"Debug"
        symbols "on"
    filter "configurations:Release"
        runtime"Release"
        optimize "on"