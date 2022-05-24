# Getting started

* [Harbour programming language](https://en.wikipedia.org/wiki/Harbour_(programming_language))
* [Homepage](https://harbour.github.io)
* Select your Harbour:
   - [hb30](https://sourceforge.net/projects/harbour-project/files/)
   - [hb32](https://github.com/harbour/core)
   - [hb34](https://github.com/vszakats/harbour-core)

# Installing on Windows

### Install raylib

Download [raylib](https://github.com/raysan5/raylib/releases/tag/4.0.0) binary archive from this page and unpack in the directory:

```
c:\raylib\bin *.dll
c:\raylib\include *.h
c:\raylib\lib *.a
```

### install hb-raylib

Environment Variables

```
set HB_WITH_RAYLIB=c:\raylib\include
set PATH=c:\raylib\bin;%path%
```

Clone an existing repository only fetching the 10 most recent commits on the default branch (useful to save time):

```
git clone --depth 10 https://github.com/dev-harbour/hb-raylib.git
cd hb-raylib
hb-raylib>hbmk2 hbraylib.hbp
```

To test it, type:

```
hb-raylib\examples\harbour\tutorial>hbmk2 tutorial_01.prg
```

# Installing and building raylib on multiple platforms

raylib contains detailed instructions on building and usage on multiple platforms.

 - [Working on Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows)
 - [Working on macOS](https://github.com/raysan5/raylib/wiki/Working-on-macOS)
 - [Working on GNU Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)
 - [Working on FreeBSD](https://github.com/raysan5/raylib/wiki/Working-on-FreeBSD)
 - [Working on Raspberry Pi](https://github.com/raysan5/raylib/wiki/Working-on-Raspberry-Pi)
 - [Working for Android](https://github.com/raysan5/raylib/wiki/Working-for-Android)
 - [Working for Web (HTML5)](https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5))
 - [Working anywhere with CMake](https://github.com/raysan5/raylib/wiki/Working-with-CMake)

---

[Edit me](https://github.com/rjopek/hb-raylib/edit/main/docs/tutorial/README.md)
