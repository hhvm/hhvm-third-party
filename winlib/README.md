winlib
================

Designed to expose posix apis but use winapi calls internally
Eventually these should be entirely replaced with something cleaner
It's never nice to force one OS to act like another

For Mingw and MSVC 14 builds of HHVM
( Cygwin builds use cygwin posix wrappers )

Not yet complete

Contains 2 bundled small libraries

dlfcn-win32 - https://code.google.com/p/dlfcn-win32/ (LGPL)
mman-win32 https://code.google.com/p/mman-win32/ (MIT)

All other code is apache licensed