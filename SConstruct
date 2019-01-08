import os
import sys
from shutil import copytree, rmtree

env = Environment()

# Link libraries
LINUX_LIBS = ["stdc++", "sfml-graphics", "sfml-window", "sfml-system"]
WIN_LIBS = ["sfml-graphics", "sfml-window", "sfml-system"]

# Compiler/Linker flags
LINUX_CXXFLAGS = "-Isrc/"
LINUX_LINKFLAGS = "-Wl,-rpath,.'$ORIGIN'/lib"
WIN_CXXFLAGS = "/Isrc/ /std:c++17 /O2 /FS /ZI /W2 /EHsc"

# Common data
FILENAME = "bin/multicaster"
SOURCES = Glob("src/*.cpp")
SOURCES.extend(Glob("src/**/*.cpp"))
BIN_PATH = "./bin"

def pre_build():
    platform = sys.platform
    print("Building for " + platform)
    try:
        os.mkdir(BIN_PATH)
    except Exception:
        pass

    if platform.startswith("win"):
        build_windows()
    elif platform.startswith("linux"):
        build_linux()
    else:
        print("No builds for your current OS: " + platform)
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
        CXXFLAGS = WIN_FLAGS,
        LIBS = WIN_LIBS,
        CPPPATH = "./include",
        LIBPATH = "./lib",
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
