FROM ubuntu:18.10
LABEL author="artur@barichello.me"

RUN apt-get update && apt-get install -y \
    binutils-dev \
    build-essential \
    clang \
    g++ \
    gcc \
    libsfml-dev \
    libtool \
    scons
