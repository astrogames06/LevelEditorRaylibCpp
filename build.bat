set files=src/main.cpp src/Game/Game.cpp src/Entity/Entity.cpp src/Player/Player.cpp src/Enemy/Enemy.cpp src/UI/UI.cpp src/Systems/WorldEditor.cpp src/Shroom/Shroom.cpp

g++ %files% -o game.exe -O1 -Wall -std=c++17 -Wno-missing-braces -I include/ lib/libraylib.win.a -lopengl32 -lgdi32 -lwinmm

.\game.exe