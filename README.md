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

## Our additions (3.0.2.0, 3.1.0.0)

- **IPv6 for the remote control.** Poweroff listens on one dual-stack socket and answers both
  IPv6 and IPv4. Where that is not possible (Windows XP, IPv6 switched off) the original
  IPv4-only code runs unchanged. Remote controlling another machine resolves names to IPv6
  and IPv4 addresses and tries them in turn. Wake-on-LAN stays IPv4.
- **64-bit build** (`poweroff64.exe`) besides the 32-bit one (`poweroff32.exe`). The dialog
  procedures now have the Win32 signature (`INT_PTR CALLBACK`, `WPARAM`, `LPARAM`); with the
  Windows 3.x style `LONG lParam` of the original the 64-bit build crashed.
- **Service installation on 64-bit Windows.** The original 32-bit program copies itself to
  "system32" – which Windows redirects to `SysWOW64` for 32-bit programs – but registers the
  service as `system32\poweroff.exe`. The 64-bit service manager is not redirected, so the
  service did not start (or started an older copy lying in the real `system32`). Now the
  32-bit program registers the service in `SysWOW64`, where its copy is (like Windows' own
  32-bit services); the 64-bit program uses the real `system32`. On 32-bit Windows nothing
  changes. The installed copy is always called `poweroff.exe`.
- **Build with current tools**: CMake for MSVC (Visual Studio 2022) and MinGW, 32 and 64 bit,
  GitHub Actions.

The changes are kept as small as possible, everything else is the original code – including
its early start during boot.

## Download

Each release has `poweroff64.exe` (64-bit Windows – use this one) and `poweroff32.exe`
(32-bit Windows), both built with MSVC; the builds of every push are artifacts of the *Build*
workflow. Install the service with `poweroff64.exe -create_service` (or the menu); the copy in
the system folder is named `poweroff.exe`.

## Build yourself

```sh
# Visual Studio 2022 (Developer prompt)
cmake -S . -B build -A x64                  # or -A Win32 for 32-bit
cmake --build build --config Release        # build/Release/poweroff.exe

# MinGW cross compile (Linux)
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build-support/mingw-x86_64.cmake -DCMAKE_BUILD_TYPE=Release   # or mingw-i686.cmake
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
