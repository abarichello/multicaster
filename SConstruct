import os
import sys

env = Environment(ENV = {"PATH": os.environ["PATH"]})

LINUX_LIBS = ["stdc++", "sfml-graphics", "sfml-window", "sfml-system"]
WIN_LIBS = ["sfml-graphics", "sfml-window", "sfml-system"]
WIN_FLAGS = "/O2 /std:c++17 /W2"
FILENAME = "caster"
GLOB = "src/*.cpp"

platform = sys.platform
print("Building for " + platform)

def build_linux():
    Program(
        FILENAME,
        Glob(GLOB),
        LIBS=LINUX_LIBS
    )

def build_windows():
    Program(
        FILENAME,
        Glob(GLOB),
        CXXFLAGS = WIN_FLAGS,
        LIBS=WIN_LIBS,
        CPPPATH = "./SFML-2.5.1/include",
        LIBPATH = "./SFML-2.5.1/lib",
    )

if platform.startswith("win"):
    build_windows()
elif platform.startswith("linux"):
    build_linux()
else:
    print("No builds for your current OS: " + platform)
    sys.exit(-1)
