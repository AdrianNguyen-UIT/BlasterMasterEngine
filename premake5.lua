workspace "BlasterMasterEngine"
    architecture "x64"
    startproject "BlasterMasterEngine"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "BlasterMasterEngine/vendor/spdlog/include"

project "BlasterMasterEngine"
    location "BlasterMasterEngine"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("obj/"..outputdir.."/%{prj.name}")

    pchheader "d3dpch.h"
    pchsource "%{prj.name}/src/d3dpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/Assets/**.h",
        "%{prj.name}/Assets/**.cpp"
    }

    includedirs
    {
        "%{prj.name}",
        "%{prj.name}/src",
        "%{IncludeDir.spdlog}"
    }

    sysincludedirs
    {
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
    }

    syslibdirs
    {
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64"
    }
    
    links
    {
        "d3d9.lib",
        "winmm.lib",
        "d3dx9.lib",
        "dxguid.lib",
        "dinput8.lib",
        "dsound.lib"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "__DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"