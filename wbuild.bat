set files=src/main.cpp src/Game/Game.cpp src/Entity/Entity.cpp src/Player/Player.cpp src/Enemy/Enemy.cpp src/UI/UI.cpp src/Systems/WorldEditor.cpp src/Shroom/Shroom.cpp src/Data/Data.cpp
em++ -o index.html %files% -std=c++17 -Os -Wall ./lib/libraylib.web.a -I. -Iinclude/ -L. -Llib/ -s USE_GLFW=3 --preload-file assets --shell-file shell.html -DPLATFORM_WEB -sINITIAL_MEMORY=33554432 -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=10485760 -sEXPORTED_FUNCTIONS=["_main","_SaveDataJSON","_LoadDataJSON"] -sEXPORTED_RUNTIME_METHODS=["ccall"] -sASSERTIONS=2

