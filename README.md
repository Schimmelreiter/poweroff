# Poweroff

**Poweroff** is a small Windows utility by **Jorgen Bosman** (Antwerp, Belgium) that powers off,
shuts down, restarts, puts to standby/hibernate or locks a PC – right away, on a schedule or
after a process ends – and can be **remote controlled over TCP** (port 3210). It runs as a
program or as a service and starts very early during boot, so it is often still reachable
when nothing else on a machine is.

## Thanks

All credit goes to **Jorgen Bosman**, who wrote Poweroff, gave it away as freeware and shipped
it with its full source code. This repository only keeps that work available and builds it
with current tools. Thank you, Jorgen!

## What is here

| Path | Content |
| --- | --- |
| [`doc/poweroff.htm`](doc/poweroff.htm) | **The original documentation** (Poweroff 3.0), unchanged – read it for all features, command line options and the remote control. |
| `poweroff.exe` | The original program, version 3.0.1.3, unchanged. |
| `src/` | The original source code (Visual C++ 6 project `poweroff.dsp`) with our changes below. |
| `CMakeLists.txt`, `build-support/` | Build with current compilers (added). |
| `.github/workflows/build.yml` | Builds on every push, release for tags `v*` (added). |

The first commit contains the original files exactly as distributed; every change after it is
in the history and in [CHANGES.md](CHANGES.md).

## Our additions (3.0.2.0)

- **IPv6 for the remote control.** Poweroff listens on one dual-stack socket and answers both
  IPv6 and IPv4. Where that is not possible (Windows XP, IPv6 switched off) the original
  IPv4-only code runs unchanged. Remote controlling another machine resolves names to IPv6
  and IPv4 addresses and tries them in turn. Wake-on-LAN stays IPv4.
- **Build with current tools**: CMake for MSVC (Visual Studio 2022) and MinGW, GitHub Actions.
  The program stays 32-bit like the original (it runs on 64-bit Windows; the original code is
  not 64-bit clean).

The changes are kept as small as possible, everything else is the original code – including
its early start during boot.

## Download

The workflow attaches `poweroff.exe` (MSVC, 32-bit) to each release; the build of every push
is available as an artifact of the *Build* workflow.

## Build yourself

```sh
# Visual Studio 2022 (Developer prompt)
cmake -S . -B build -A Win32
cmake --build build --config Release        # build/Release/poweroff.exe

# MinGW cross compile (Linux)
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build-support/mingw-i686.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build                         # build/poweroff.exe
```

The original `src/poweroff.dsp` still works with Visual C++ 6.

## Remote control in short

Line based over TCP (default port 3210): `PASSWORD p`, `ACTION shutdown|poweroff|reboot|standby|hibernate|lock|logoff|monitor_off|monitor_on`,
`WHO local`, `WHEN immediate`, `WARNING on`, `WARNTIME s`, `MESSAGE text`, `FORCE on`,
`SIMULATE on`, `DOIT`, `QUIT`, `HELP` – answers `250 OK`, `201 <info>` or `501 <error>`.
Details in the original documentation. A Home Assistant integration that uses it:
[hass-poweroff](https://github.com/Schimmelreiter/hass-poweroff).

## License

Poweroff was published by Jorgen Bosman as freeware with full source code; the original
documentation names no further license. This repository passes it on unchanged in that spirit
and our changes under the same terms. If you are the author and want anything changed or
removed, please open an issue.
