FROM ubuntu:18.10
LABEL author="artur@barichello.me"

# Dependencies required to build on linux and to cross compile for windows 64bits
RUN apt-get update \
    && apt-get install -y \
    binutils-dev \
    build-essential \
    g++ \
    g++-mingw-w64-x86-64 \
    libsfml-dev \
    liblua5.3-dev \
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
RUN wget -S --tries=3 -O lua53.zip 'https://onedrive.live.com/download.aspx?cid=E05E4118C4109044&authKey=!AN3RUdA5ybdvi9c&resid=E05E4118C4109044!1113&canary=YL14ve2cRJBsIYhXpfN4uow%2B8skZAExYCx4S%2BeSpabE%3D2&ithint=.zip' \
    && unzip lua53.zip -d ./lua/
