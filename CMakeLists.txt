cmake_minimum_required(VERSION 3.16)
project(poweroff C RC)

set(SOURCES
  src/action.c src/clientcommands.c src/commandline.c src/message.c src/poweroff.c
  src/process.c src/processbrowser.c src/program.c src/registry.c src/remote.c
  src/remote_control.c src/sanity.c src/schedule.c src/servercommands.c src/service.c
  src/settings.c src/sockets.c src/warning.c src/wol.c src/poweroff.rc)

add_executable(poweroff WIN32 ${SOURCES})
target_compile_definitions(poweroff PRIVATE WIN32 NDEBUG _WINDOWS _MBCS
  _CRT_SECURE_NO_WARNINGS _WINSOCK_DEPRECATED_NO_WARNINGS
  # The isolation-aware inline headers of current Windows SDKs do not compile as C;
  # the program activates common controls 6 through its manifest anyway.
  ISOLATION_AWARE_ENABLED=0)
# MFC is not needed: afxres.h comes from build-support
target_include_directories(poweroff PRIVATE src build-support)
set_property(SOURCE src/poweroff.rc APPEND PROPERTY INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}/build-support ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(poweroff PRIVATE kernel32 user32 gdi32 advapi32 comdlg32 comctl32
  shell32 winmm mpr ws2_32)
if(MSVC)
  target_compile_options(poweroff PRIVATE /W3 /O1)
  # The program brings its own manifest (resource 24 in poweroff.rc)
  target_link_options(poweroff PRIVATE /MANIFEST:NO)
  set_property(TARGET poweroff PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
else()
  # the header defines g_hWnd in every unit (old C "common" symbol)
  target_compile_options(poweroff PRIVATE -O2 -Wall -Wno-unused -Wno-format-truncation -fcommon)
  target_link_options(poweroff PRIVATE -static -static-libgcc)
endif()
