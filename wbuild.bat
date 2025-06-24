:: Needed for looping through src/
setlocal enabledelayedexpansion

set CODE_FILES=
for /R src %%f in (*.cpp) do (
    set "CODE_FILES=!CODE_FILES! %%f"
)
em++ -o index.html %CODE_FILES% -std=c++17 -Os -Wall ./lib/libraylib.web.a -I. -I include/ -L. -L lib/ -s USE_GLFW=3 --shell-file shell.html -DPLATFORM_WEB