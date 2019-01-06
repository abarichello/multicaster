# multicaster [![pipeline status](https://gitlab.com/BARICHELLO/multicaster/badges/master/pipeline.svg)](https://gitlab.com/BARICHELLO/multicaster/commits/master) [![](https://img.shields.io/github/repo-size/badges/shields.svg)](https://github.com/aBARICHELLO/multicaster)

Raycasting game engine.

## Screenshots
<img src="https://i.imgur.com/PjfQQvB.png">

## Download
This project uses GitLab CI to automatically create packaged zip files with all dependencies included from every commit sent. Follow instructions below to download and play:<br>

1. Visit the [GitLab CI](https://gitlab.com/BARICHELLO/multicaster/-/jobs) page and find the first occurrence of your operating system on the column `name`. Click the `Download artifacts` button on the right side of the same line.
2. Extract the zip to your preffered location and start the executable.

PS: CI builds for windows not available yet.

## Compiling
### Arch Linux
```
sudo pacman -S libsfml-dev
scons
./bin/multicaster
```

### Windows
1. [Download SFML 2.5.1 or later from website](https://www.sfml-dev.org/download.php).
2. Place `include`, `lib` and `bin` folder together with `src`.
3. `scons` and `.\bin\multicaster.exe`.

## References

- Made using [Lode's raycasting tutorials](https://lodev.org/cgtutor/) as reference for the raycasting engine.
