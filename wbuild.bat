:: Needed for looping through src/
setlocal enabledelayedexpansion

set CODE_FILES=
for /R src %%f in (*.cpp) do (
    set "CODE_FILES=!CODE_FILES! %%f"
)
em++ -o index.html %CODE_FILES% -std=c++17 -Os -Wall ./lib/libraylib.web.a -I. -Iinclude/ -L. -Llib/ -s USE_GLFW=3 --preload-file assets --shell-file shell.html -DPLATFORM_WEB -sINITIAL_MEMORY=33554432 -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=10485760 -sEXPORTED_FUNCTIONS=["_main","_SaveDataJSON","_LoadDataJSON"] -sEXPORTED_RUNTIME_METHODS=["ccall"] -sASSERTIONS=2