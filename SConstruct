import os
import sys

env = Environment(ENV = {"PATH": os.environ["PATH"]})

LINUX_LIBS = ["stdc++", "sfml-graphics", "sfml-window", "sfml-system"]
WIN_LIBS = ["sfml-graphics", "sfml-window", "sfml-system"]
WIN_FLAGS = "/O2 /std:c++17 /W2 /EHsc"
FILENAME = "caster"
SOURCES = Glob("src/*.cpp")
SOURCES.extend(Glob("src/**/*.cpp"))

platform = sys.platform
print("Building for " + platform)

def build_linux():
    Program(
        FILENAME,
        SOURCES,
        LIBS=LINUX_LIBS
    )

def build_windows():
    Program(
        FILENAME,
        SOURCES,
        CXXFLAGS = WIN_FLAGS,
        LIBS=WIN_LIBS,
        CPPPATH = "./include",
        LIBPATH = "./lib",
    )

if platform.startswith("win"):
    build_windows()
elif platform.startswith("linux"):
    build_linux()
else:
    print("No builds for your current OS: " + platform)
    sys.exit(-1)
