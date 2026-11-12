# Changes

## 3.0.2.0 (this repository)

- IPv6 for the remote control:
  - `CreateServerSocket` (src/sockets.c): first a dual-stack IPv6 socket (`IPV6_V6ONLY` off,
    `in6addr_any`) that also accepts IPv4; if that fails, the original IPv4 code, unchanged.
  - `OpenServerConnection` (src/sockets.c): `getaddrinfo` instead of `gethostbyname`/`inet_addr`,
    every address is tried in turn (IPv6 and IPv4).
  - src/poweroff.h: `winsock2.h` and `ws2tcpip.h` before `windows.h`, `_WIN32_WINNT 0x0501`
    (getaddrinfo, Windows XP and newer).
  - src/poweroff.dsp: `ws2_32.lib` instead of `wsock32.lib` (release build).
- Build:
  - `CMakeLists.txt` for MSVC and MinGW, toolchain files and an `afxres.h` stand-in in
    `build-support/` (no MFC needed), GitHub Actions workflow.
  - src/poweroff.h: `#define ISOLATION_AWARE_ENABLED 1` (the empty define of the original
    breaks current Windows SDK headers).
- Version string `3.0.2.0` (shown in the remote control greeting).

## 3.0.1.3 and earlier

By Jorgen Bosman, see the original documentation in `doc/poweroff.htm`.
