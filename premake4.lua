-- define some vars
local home_dir  = os.getenv("HOME")
local build_dir = "build" 
local obj_dir   = build_dir .. "/obj"
local bin_dir   = build_dir .. "/bin"

solution "codeArena"
    configurations { "Debug", "Release" }

    -- use all files and their subdirectories
    files { 
        "include/**.h",
        "src/**.cpp"
    }

    -- add extra include directories
    includedirs {
        "include",
        "OaxLib/include"
    }

    libdirs {
        "OaxLib/build/lib"
    }


    project "codeArena"
        kind "ConsoleApp"
        language "C++"
        location (build_dir.."/make")

        -- all configurations will use this define    
        defines { 
            "HAVE_VERSION_FILE"
        }


        -- Debug configuration
        configuration "Debug"
            defines {
                "ENABLE_DEBUG"
            }

            links {
                "ncurses"
            }

            -- generic flags for gcc
            flags {
                "Symbols"
            }

            local config = "Debug"
            objdir (obj_dir.."/"..config)
            targetdir (bin_dir.."/"..config)


        -- Release configuration
        configuration "Release"
            defines {
            }

            links {
                "ncurses"
            }

            -- generic flags for gcc
            flags {
                "Optimize"
            }

            local config = "Release"
            objdir (obj_dir.."/"..config)
            targetdir (bin_dir.."/"..config)
