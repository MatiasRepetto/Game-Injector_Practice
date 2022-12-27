workspace "Game-Injector_ForestLabs"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

    startproject "Game-Injector_ForestLabs"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("./bin")
        print("Removing intermediate binaries")
        os.rmdir("./bin-int")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}

project "Game-Injector_ForestLabs"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("./bin/" .. outputdir .. "/%{prj.name}")
    objdir("./bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.cpp",
        "include/**.h"
    }

    includedirs {
        "include"
    }

    defines {
        "WINDOWS"
    }

    filter { "configurations:Debug" }
        buildoptions "/MTd"
        runtime "Debug"
        symbols "on"

    filter { "configurations:Release" }
        buildoptions "/MT"
        runtime "Release"
        optimize "on"