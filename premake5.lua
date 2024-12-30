

workspace "SortingAlgorithms"
   architecture "x86_64"
   configurations { "Debug", "Release" }
   
   outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
   
   project "SortingAlgorithms"
   location "SortingAlgorithms"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   files {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp",
      "%{prj.name}/imgui/**.h",
      "%{prj.name}/imgui/**.cpp",
      "%{prj.name}/src/glad.c",
   }

   includedirs {
      "%{prj.name}",
      "./vendor/glad/include",
      "./vendor/glfw/include"
   }

   libdirs {
    "./vendor/glfw/lib"
   }

   links {
      "opengl32.lib",
      "glfw3.lib"
   }

   filter "configurations:Debug"
      defines "DEBUG"
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      defines "NDEBUG"
      runtime "Release"
      optimize "on"