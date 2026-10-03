#ifdef    MONO_BUILD
#define GAME_STATE_IMPLEMENTATION
#endif // MONO_BUILD
#ifndef    _GAME_STATE_H_
#define    _GAME_STATE_H_
// game_state interface

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <raylib.h>
#include "snake_case_api_raylib.h"
#include "snake_case_api_raymath.h"
#include "noutil.h"



#ifdef FAKEOUT
typedef struct slua_State lua_State;
#endif // FAKEOUT


typedef struct sGameState {
  u screen_x_;
  u screen_y_;
  u frame;
  lua_State* L;
} GameState;

// :fGameState
GameState gs_init();
void      gs_update(GameState* self);
void      gs_reset (GameState* self);
void      gs_draw  (GameState* self);
void      gs_free  (GameState* self);

#ifdef      GAME_STATE_IMPLEMENTATION
// game_state implementation


// :iGameState
GameState gs_init() {
  GameState self = {0};

  self.screen_x_ = 720;
  self.screen_y_ = 720;

  self.frame = 0;

  init_window(self.screen_x_, self.screen_y_, "raylib game");

  return self;
}
void      gs_update(GameState* self) {
  self->frame++;

  if ( is_key_pressed(KEY_A) ) {
    if (luaL_dostring(self->L,
        " gs:reset() ") != LUA_OK) {
      fprintf(stderr, "Lua error: %s\n", lua_tostring(self->L, -1));
      lua_pop(self->L, 1);
      lua_close(self->L);
      return;
    }

  }
  if ( is_key_pressed(KEY_S) ) {
    gs_reset(self);
  }



}
void gs_reset(GameState* self) {
  self->frame = 0;
}



void      gs_draw  (GameState* self) {
  begin_drawing();
  clear_background(RAYWHITE);
  draw_text(text_format(" %zu ",self->frame ), 10, 10, 30, RED);
    end_drawing();
}
void      gs_free  (GameState* self) {
  (void)self;
}



#endif   // GAME_STATE_IMPLEMENTATION
#endif   //_GAME_STATE_H_

