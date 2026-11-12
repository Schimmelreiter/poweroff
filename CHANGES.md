# Changes

## 3.1.0.0 (this repository)

- 64-bit build: the ten dialog procedures are declared `INT_PTR CALLBACK Proc(HWND, UINT,
  WPARAM, LPARAM)` instead of `BOOL FAR PASCAL Proc(HWND, unsigned, DWORD, LONG)` (the
  `LONG lParam` cut the settings pointer in half on 64-bit Windows); src/wol.c keeps the
  socket in a `SOCKET` instead of an `int`.
- Service installation: the 3.0.2.0 change (switching the WOW64 redirection off and copying to
  the real `system32`) is replaced. `CopyPoweroffToSystem` (src/service.c) of the 32-bit build
  now uses `GetSystemWow64Directory` (looked up with `GetProcAddress`) for the copy and the
  service path: on 64-bit Windows `SysWOW64\poweroff.exe`, the right place for a 32-bit
  program; on 32-bit and older Windows `GetSystemDirectory` as in the original. The 64-bit
  build uses `GetSystemDirectory` (the real `system32`).
- Build: MSVC Win32 and x64, MinGW i686 and x86_64; the release has `poweroff32.exe` and
  `poweroff64.exe`.
- Version 3.1.0.0 (greeting and version resource).

## 3.0.2.0 (this repository)

- IPv6 for the remote control:
  - `CreateServerSocket` (src/sockets.c): first a dual-stack IPv6 socket (`IPV6_V6ONLY` off,
    `in6addr_any`) that also accepts IPv4; if that fails, the original IPv4 code, unchanged.
  - `OpenServerConnection` (src/sockets.c): `getaddrinfo` instead of `gethostbyname`/`inet_addr`,
    every address is tried in turn (IPv6 and IPv4).
  - src/poweroff.h: `winsock2.h` and `ws2tcpip.h` before `windows.h`, `_WIN32_WINNT 0x0501`
    (getaddrinfo, Windows XP and newer).
  - src/poweroff.dsp: `ws2_32.lib` instead of `wsock32.lib` (release build).
- Service installation on 64-bit Windows: `CopyPoweroffToSystem` (src/service.c) switches the
  WOW64 file system redirection off for the copy (`Wow64DisableWow64FsRedirection`, looked up
  with `GetProcAddress`, so older Windows versions behave as before). Before, the copy of the
  32-bit program to `system32` landed in `SysWOW64`, while the service manager starts
  `system32\poweroff.exe` - an older copy kept running, or the service did not start at all.
- Build:
  - `CMakeLists.txt` for MSVC and MinGW, toolchain files and an `afxres.h` stand-in in
    `build-support/` (no MFC needed), GitHub Actions workflow.
  - src/poweroff.h: `ISOLATION_AWARE_ENABLED` is 1 unless the build defines it (the empty define
    of the original breaks current SDK headers); CMake builds with 0 because the isolation-aware
    inline headers of current Windows SDKs do not compile as C - the program activates common
    controls 6 through its manifest anyway.
- Version string `3.0.2.0` (shown in the remote control greeting).

## 3.0.1.3 and earlier

By Jorgen Bosman, see the original documentation in `doc/poweroff.htm`.
