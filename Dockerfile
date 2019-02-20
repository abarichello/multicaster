FROM ubuntu:18.10
LABEL author="artur@barichello.me"

# Dependencies required to build on linux and to cross compile for windows 64bits
RUN apt-get update \
    && apt-get install -y \
    binutils-dev \
    build-essential \
    g++ \
    g++-mingw-w64-x86-64 \
    liblua5.3-0 \
    liblua5.3-dev \
    libsfml-dev \
    lua5.3 \
    scons \
    software-properties-common \
    unzip \
    wget

RUN add-apt-repository ppa:texus/tgui-0.8 \
    && apt-get update \
    && apt-get install libtgui-dev

RUN wget -S --tries=3 -O sfml.zip https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip \
    && unzip sfml.zip

RUN wget -S --tries=3 -O tgui.zip https://github.com/texus/TGUI/releases/download/v0.8.3/TGUI-0.8.3-mingw-7.3.0-64bit-for-SFML-2.5.1.zip \
    && unzip tgui.zip

RUN wget -S --tries=3 -O sol.hpp https://github.com/ThePhD/sol2/releases/download/v2.20.6/sol.hpp
RUN wget -S --tries=3 -O lua53.zip 'https://downloads.sourceforge.net/project/luabinaries/5.3.5/Windows Libraries/Dynamic/lua-5.3.5_Win64_dllw6_lib.zip?r=https://sourceforge.net/projects/luabinaries/files/5.3.5/Windows%20Libraries/Dynamic/&ts=1550692616&use_mirror=ufpr' \
    && unzip lua53.zip -d ./lua/
