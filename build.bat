:: Needed for looping through src/
setlocal enabledelayedexpansion

set CODE_FILES=
for /R src %%f in (*.cpp) do (
    set "CODE_FILES=!CODE_FILES! %%f"
)
g++ %CODE_FILES% -o game.exe -O1 -Wall -std=c++17 -Wno-missing-braces -I include/ lib/libraylib.win.a -lopengl32 -lgdi32 -lwinmm
game.exe
