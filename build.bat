set files=

for /r src %%f in (*.cpp) do call set files=%%files%% %%f

g++ %files% -o game.exe -O1 -Wall -std=c++17 -Wno-missing-braces -I include/ lib/libraylib.win.a -lopengl32 -lgdi32 -lwinmm

.\game.exe