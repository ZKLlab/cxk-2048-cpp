#ifndef GAMEDEF_H
#define GAMEDEF_H

#define TILE_WIDTH 100
#define GUTTER_WIDTH 15
#define CONTAINER_WIDTH (TILE_WIDTH * 4 + GUTTER_WIDTH * 5)

#define TILE_PADDING 12
#define TILE_VALUE_SIZE 16
#define TILE_VALUE_MARGIN_LEFT 4
#define TILE_VALUE_MARGIN_TOP 0

#define ANIMATION_DURATION_BASE 100

#define GAME_WIN 1
#define GAME_LOSE 0
#define GAME_CONTINUE 2

#define MOVE_UP 0
#define MOVE_LEFT 1
#define MOVE_DOWN 2
#define MOVE_RIGHT 3

#endif // GAMEDEF_H
