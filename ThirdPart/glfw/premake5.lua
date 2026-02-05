project "GLFW"
    kind "StaticLib"  
    language "C"
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
        "glfw/src/*.h",         
        "glfw/src/*.c",         
        "glfw/src/win32/*.h",   
        "glfw/src/win32/*.c",   
    }
    includedirs {
        "include",             
        "glfw/src",            
        "glfw/src/win32"       
    }

    filter "system:windows"
        systemversion "latest" 
        defines {
            "_GLFW_WIN32=1",            
            "_CRT_SECURE_NO_WARNINGS",  
            "_WIN32_WINNT=0x0601",      
            "UNICODE", "_UNICODE",      
            "_GLFW_BUILD_STATIC=1"      
        }
        links {
            "gdi32",    
            "user32",   
            "kernel32", 
            "shell32",  
            "ole32",    
            "advapi32", 
            "imm32",    
            "hid",      
            "winmm"     
        }

    filter "system:not windows"
        removefiles {
            "glfw/src/win32/*",  
        }

    filter "configurations:Debug"
        symbols "on"
        runtime"Debug"
        defines { "GLFW_DEBUG=1" }  
    filter "configurations:Release"
        optimize "on"
        runtime"Release"
        defines { "GLFW_RELEASE=1" }
   