CODE_FILES=$(find src/ -name "*.cpp")

em++ -o index.js $CODE_FILES -std=c++17 -Os -Wall ./lib/libraylib.web.a -I. -Iinclude/ -L. -Llib/ -s USE_GLFW=3 --preload-file assets -DPLATFORM_WEB -sINITIAL_MEMORY=33554432 -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=10485760 -lembind -sASSERTIONS=2