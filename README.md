# multicaster [![pipeline status](https://gitlab.com/BARICHELLO/multicaster/badges/master/pipeline.svg)](https://gitlab.com/BARICHELLO/multicaster/commits/master) [![](https://img.shields.io/github/repo-size/badges/shields.svg)](https://github.com/aBARICHELLO/multicaster)

Raycasting game engine.

## Screenshots
<img src="https://i.imgur.com/PjfQQvB.png">

## Download
This project uses GitLab CI to automatically create packaged zip files with all dependencies included from every commit sent. Follow instructions below to download and play:<br>

1. Visit the [GitLab CI](https://gitlab.com/BARICHELLO/multicaster/-/jobs) page and find the first occurrence of your operating system on the column `name`. Click the `Download artifacts` button on the right side of the same line.
2. Extract the zip to your preffered location and start the executable.

PS:
1. CI builds for windows in progress.
2. `glibc` version 2.28 required for Linux (`musl` build pending)

## Compiling
### Arch Linux
```
sudo pacman -S libsfml-dev tgui-git lua
scons
./bin/multicaster
```

### Windows
1. [Download SFML 2.5.1 or later from website](https://www.sfml-dev.org/download.php) and [tmgui](https://tgui.eu/).
2. Place `include`, `lib` and `bin` folder together with `src`.
3. `scons` and `.\bin\multicaster.exe`.

## References

- Made using [Lode's raycasting tutorials](https://lodev.org/cgtutor/) as reference for the raycasting engine.
