# Triforce%

Triforce% is a hybrid RTA/TAS "speedrun" of Ocarina of Time which uses Arbitrary
Code Execution (ACE) to install a set of data loaders in system memory, enabling
arbitrary assets (scenes, objects, music, etc.) in the game ROM to be seamlessly
live-patched from the host PC. By modifying the game programming and assets,
beta content cut from the final version of OoT is restored and brought to life
on screen. A new plot is constructed based on this beta content and on urban
legends from the late '90s, culminating in Link obtaining the Triforce.

But, in front of thousands of live viewers, once we have the power of the
Goddesses--and the power to make the game whatever we can imagine--what will we
use this power for?


# Setup

- Install Linux (Ubuntu / other Debian derivative), either natively or through
WSL/WSL2 if you're on Windows.
- Make sure you got the Git submodules. The build system checks for some of
them but not all. You will need `libpng-dev`, `libelf-dev`, and `libglib2.0-dev`
for these to compile. You will also need `build-essential` in order to be able
to compile anything for your local machine.
- In your python3, install `pyserial` (not `serial`), `pillow`, and `psutil`.
- Install the N64 toolchain from https://github.com/glankk/n64. **See below for
more detailed instructions.**
- Get a copy of zzrtl which is stable enough to work on Linux with the default
(i.e. non-Jared Johnson) scripts, e.g. 0.01r4.
https://old.z64.me/tools/zzrtl/zzrtl-0.01-r4.zip Put this somewhere outside the
Git repo (i.e. not in the `toolchain` folder).
- Copy local.mk.example to local.mk and edit the paths defined there to point to
the relevant tools on your computer.
- Make a `build-shortcut` folder and paste the OoT 1.0U compressed ROM into it,
with the name `oot_1.0U_comp.z64`.
- Make a `build-romhack` and paste the OoT 1.0U uncompressed ROM into it, with
the name `oot_1.0U_uncomp.z64`.
- `make`. Do not use `-j4` etc., some of the dependencies may not be correctly
tracked/rebuilt in this case. Look for a `Done building` message at the end.
- If you make changes to Makefiles or any other part of the build toolchain,
make sure to `make clean`.

## N64 toolchain instructions

This was tried on a mostly fresh native install of Ubuntu 20.04, and on Ubuntu
20.04 through WSL2 on Windows 10. These are modifications/notes to the
installation instructions on the glank N64 toolchain github page, so you should
be following those instructions but also looking at this info at the same time.

- Install `libgmp-dev`.
- `git clone` the repo instead of downloading the zip file (because of the next
step).
- When it says "navigate to `n64-master`", this means `git checkout n64-ultra`.
- Before ./configure, I did
```
sudo mkdir /opt/n64
sudo chown yourusername /opt/n64
sudo chgrp yourusername /opt/n64
```
- `make -j4` or whatever works OK without issues.
- I don't think the `make install-local-exec` step is needed.
- If you don't already know, one way to add `/opt/n64/bin` to PATH is to add the
line
```
export PATH=/opt/n64/bin:$PATH
```
to somewhere in `~/.bashrc`, and then exit the current bash you are in and start
a new bash session.
- To check that everything is installed correctly, run `mips64-ultra-elf-gcc -v`
and verify that the output is a reasonable MIPS64 GCC version info.


# Credits

### TRIFORCE% OOT ACE SHOWCASE

Director \
SAURAEN

RTA Speedrunner \
SAVESTATE

Scenario \
SAURAEN \
REBECCAETRIPP \
TERUSTHEBIRD \
DWANGOAC

### ASSET UNIT

Scene Design \
CDI-FAILS \
ZEL \
SAURAEN

Music \
SAURAEN \
REBECCAETRIPP

Screen Text \
KIM-SUKLEY \
SAURAEN

Cinema Scenes \
SAURAEN \
DWANGOAC \
DEFENESAM

BotW Model Conversion \
ALI1234 \
SAURAEN

Animation \
UNESAG \
SAURAEN \
RANKAISIJA \
AEROARTWORK

Zelda (English Voice) \
SAOIRSE

Link (Japanese Voice) \
ZERO

Translator \
YUKLOJ

Textures \
CDI-FAILS \
KIM-SUKLEY \
ZEL \
SAURAEN

### PROGRAM UNIT

Actor Program \
SAURAEN \
RANKAISIJA \
Z64ME \
MNGOLDENEAGLE \
ZEL

Game / Actor Patches \
SAURAEN \
MNGOLDENEAGLE

System Patches \
SAURAEN \
ZEL

Cel Shading \
SAURAEN \
GLANK

Bootstrapper Chain \
SAURAEN

Hyperspeed Loader \
TERUSTHEBIRD \
SAURAEN

Host Frontend \
SAURAEN \
THEMAS3212

TAStm32 Firmware \
OWNASAURUS \
SAURAEN

SRM / ACE Setup \
MRCHEEZE \
SAVESTATE

Build Toolchain \
SAURAEN \
Z64ME

### COMMUNITY UNIT

Partner Creators \
SWANKYBOX \
RETRO GAME MECHANICS EXPLAINED \
HARD4GAMES

Partner Reactors \
HMK \
TETRABITGAMING

OST Published By \
SIIVAGUNNER

Video Editing \
MUSKET012 \
GRAVATOS \
SAVESTATE \
SAURAEN

Technical Support \
ZEL \
Z64ME \
MZXRULES \
THARO \
WISEGUY \
JACK WALKER

Special Thanks \
KAZE EMANUAR \
XDANIEL \
ARIANA ALMANDOZ

Executive Producer \
DWANGOAC

### PRESENTED AT

Summer Games Done Quick 2022

Assets, Toolchain, and Performance \
Copyright (C) 2019-2022 \
The Triforce% Team

The Legend of ZELDA: Ocarina of Time \
Copyright (C) 1998 \
Nintendo

