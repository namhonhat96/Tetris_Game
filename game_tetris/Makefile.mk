CFLAGS += -I./sources/game_tetris
CPPFLAGS += -I./sources/game_tetris

VPATH += sources/game_tetris

SOURCES_CPP += ./sources/game_tetris/tetris_coordinate.cpp
SOURCES_CPP += ./sources/game_tetris/task_sm_tetris.cpp
SOURCES_CPP += ./sources/game_tetris/task_gc_tetris.cpp
SOURCES_CPP += ./sources/game_tetris/task_ui_tetris.cpp
SOURCES_CPP += ./sources/game_tetris/Tetris_MovingObject.cpp
SOURCES_CPP += ./sources/game_tetris/Tetris_StandingObject.cpp
