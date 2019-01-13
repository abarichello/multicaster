import os
import sys
from shutil import copytree, rmtree

# Cross compile optional args
MINGW = "/usr/bin/x86_64-w64-mingw32-g++"
AddOption("--cross", help="Cross compile to Windows", metavar="0")
env = DefaultEnvironment(CROSS = GetOption("cross"))

# Determine compiler
CROSS = env["CROSS"]
if CROSS == "1":
    env["CXX"] = MINGW
print("--- Using compiler: {}".format(env["CXX"]))

# Link libraries
LINUX_LIBS = ["stdc++", "sfml-graphics", "sfml-window", "sfml-system", "tgui"]
WIN_LIBS = ["tgui", "sfml-graphics", "sfml-window", "sfml-system"]
MINGW_LIBS = ["-static-libgcc", "-static-libstdc++", "sfml-graphics", "sfml-window", "sfml-system"]

# Compiler/Linker flags
LINUX_CXXFLAGS = "-Isrc/ -I/usr/include/"
LINUX_LINKFLAGS = "-Wl,-rpath,.'$ORIGIN'/lib"
WIN_CXXFLAGS = "/Isrc/ /std:c++17 /O2 /FS /ZI /W2 /EHsc"
MINGW_CXXFLAGS = "-Isrc/ -Iinclude/"
MINGW_LINKFLAGS = "-Llib/"

# Common data
FILENAME = "bin/multicaster"
WIN_FILENAME = FILENAME + ".exe"
SOURCES = Glob("src/*.cpp")
SOURCES.extend(Glob("src/**/*.cpp"))
BIN_PATH = "./bin"

def pre_build():
    platform = sys.platform
    print("--- Building for " + platform)
    try:
        os.mkdir(BIN_PATH)
    except Exception:
        pass

    if CROSS == "1":
        build_cross()
    elif platform.startswith("win"):
        build_windows()
    elif platform.startswith("linux"):
        build_linux()
    else:
        print("--- No builds for your current OS: " + platform)
        sys.exit(-1)

def build_linux():
    Program(
        FILENAME,
        SOURCES,
        CXXFLAGS = LINUX_CXXFLAGS,
        LINKFLAGS = LINUX_LINKFLAGS,
        LIBS = LINUX_LIBS,
    )

def build_windows():
    Program(
        FILENAME,
        SOURCES,
        CXXFLAGS = WIN_CXXFLAGS,
        LIBS = WIN_LIBS,
        CPPPATH = "./include",
        LIBPATH = "./lib",
    )

# Cross compile using x86_64-w64-mingw32-g++
def build_cross():
    Program(
        WIN_FILENAME,
        SOURCES,
        CXXFLAGS = MINGW_CXXFLAGS,
        LINKFLAGS = MINGW_LINKFLAGS,
        LIBS = LINUX_LIBS,
    )

def post_build():
    # Make the resource folder acessible by the generated binary
    try:
        rmtree("bin/resources")
    except OSError as e:
        print(e)
    finally:
        copytree("resources", "bin/resources")

pre_build()
post_build()
