# sdl2 cmake project-config input for ./configure scripts

set(prefix "/home/consta_n/SDL2") 
set(exec_prefix "${prefix}")
set(libdir "${exec_prefix}/lib64")
set(SDL2_PREFIX "/home/consta_n/SDL2")
set(SDL2_EXEC_PREFIX "/home/consta_n/SDL2")
set(SDL2_LIBDIR "${exec_prefix}/lib64")
set(SDL2_INCLUDE_DIRS "${prefix}/include/SDL2")
set(SDL2_LIBRARIES "-L${SDL2_LIBDIR} -Wl,-rpath,${libdir} -lSDL2 ")
