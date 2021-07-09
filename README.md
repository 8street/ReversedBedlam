# OpenBedlam

An open source re-implementation of Bedlam 1996 game.

[![Lines of Code](https://tokei.rs/b1/github/8street/OpenBedlam?category=code)](https://github.com/XAMPPRocky/tokei)

# Project State

Not playable yet.

* Video: direct draw
* Sound: direct sound
* Mouse: yes
* Keyboard: yes
* Main menu: partially functioning
* Map room: partially functioning
* Shop room: no
* Briefing room: no
* Game process: no

# Contributing

Contributors, welcome. Create a fork of this repository, then create a branch. Modify the source code in your branch. Finally, create a pull request to merge with my main branch. Patches and improvements are welcome.

IDA .idb reverse file [here](https://www.dropbox.com/sh/h0yyypzx8gjkn9c/AABBuR-fwNthYnOYPf7VH-Q7a?dl=0).

# Compiling

1. Open msvc/OpenBedlam.sln in Visual Studio 2019
2. Compile x86 platform. x64 platform seems not support index8 direct draw mode
3. Put compiled .exe file in your Bedlam folder. Or put Bedlam files in VS output directory
4. Run

To run in a window mode, set the application 256 color compatibility mode.

# Planning

Migration to SDL and cross-platform. After very large piece of reverse engineering.
