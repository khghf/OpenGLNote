project "GLFW"
    kind "StaticLib"  -- ���־�̬�⣨��Ҫ��̬���Ϊ SharedLib����ͬ���޸ĺ꣩
    language "C"
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    -- �ؼ� 1������ GLFW ���°����к����ļ�����Դ��ԭ���ṹ������©��
    files {
        -- ����ͷ�ļ���GLFW ���Ⱪ¶��ͷ�ļ���
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
        -- GLFW �ڲ������ļ������°���裬֮ǰ©�ˣ���
        "glfw/src/*.h",          -- �����ڲ�ͷ�ļ���internal.h��platform.h �ȣ�
        "glfw/src/*.c",          -- �����ڲ�����Դ�루context.c��init.c �ȣ�
        -- Windows ƽ̨ר���ļ������°�ԭ��֧�֣������ֶ�ɸѡ��
        "glfw/src/win32/*.h",    -- Windows �ڲ�ͷ�ļ���win32_platform.h �ȣ�
        "glfw/src/win32/*.c",    -- Windows ƽ̨ʵ�֣�������ȷ�� _glfwSelectPlatform��
    }

    -- �ؼ� 2����ȷ���ð���Ŀ¼���� GLFW Դ�����ҵ�����ͷ�ļ���
    includedirs {
        "include",              -- ����ͷ�ļ�Ŀ¼�����������Ŀ���ã�
        "glfw/src",             -- GLFW �ڲ�����ͷ�ļ�Ŀ¼��src/*.h��
        "glfw/src/win32"        -- Windows ƽ̨�ڲ�ͷ�ļ�Ŀ¼��src/win32/*.h��
    }

    -- �ؼ� 3��Windows ƽ̨�������ã�ƥ�����°� GLFW Ҫ��
    filter "system:windows"
        systemversion "latest"  -- ʹ������ Windows SDK
        defines {
            "_GLFW_WIN32=1",            -- ǿ������ Windows ƽ̨�����°�������
            "_CRT_SECURE_NO_WARNINGS",  -- ���� CRT ��ȫ����
            "_WIN32_WINNT=0x0601",      -- ���֧�� Windows 7��GLFW 3.4+ Ҫ��
            "UNICODE", "_UNICODE",      -- ���� Unicode��Windows ƽ̨���裩
            "_GLFW_BUILD_STATIC=1"      -- �ؼ������� GLFW ���뾲̬�⣨ƥ�� kind "StaticLib"��
        }
        -- ���°� GLFW Windows �����ϵͳ�⣨���ٷ��ĵ���
        links {
            "gdi32",    -- ͼ���豸�ӿ�
            "user32",   -- ���ڹ���
            "kernel32", -- �ں˹��ܣ��߳�/�ڴ棩
            "shell32",  -- ϵͳ�ǹ���
            "ole32",    -- COM �����������/IME��
            "advapi32", -- �߼� API��Ȩ��/ע�����
            "imm32",    -- ���뷨֧��
            "hid",      -- �ֱ� HID �豸֧��
            "winmm"     -- ��ý�嶨ʱ�������°�����������
        }

    -- �ؼ� 4���ų��� Windows ƽ̨�ļ�����������ͻ��
    filter "system:not windows"
        removefiles {
            "glfw/src/win32/*",  -- �� Windows ƽ̨ʱ���ų� Windows ����ļ�
        }

    -- ���������Ż���Debug/Release ���֣�
    filter "configurations:Debug"
        symbols "on"
        runtime"Debug"
        defines { "GLFW_DEBUG=1" }  -- ���� GLFW ����ģʽ����ѡ�������Ų����⣩
    filter "configurations:Release"
        optimize "on"
        runtime"Release"
        defines { "GLFW_RELEASE=1" }
   