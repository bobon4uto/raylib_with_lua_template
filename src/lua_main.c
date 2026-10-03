#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#define HAS_LUA
#include "game_state.h"

// :func
void main_loop(GameState* gs);

// :impl

#include "raylib.h"
#include "snake_case_api_raylib.h"
#include "snake_case_api_raymath.h"
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h> // Emscripten library
#endif

// :macro

#define GAME_TITLE "the game"

#define SUPPORT_LOG_INFO
#if defined(SUPPORT_LOG_INFO)
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif


#include "noutil.h"
#include "base_types.h"
#include "../build/gen/game.c"



int register_lua_state_lua(lua_State* L) {
  GameState* gs = (GameState*)luaL_checkudata(L, 1, GAME_STATE_META_TABLE);

  gs->L = L;

  return 0;
}


int main() {
  lua_State * L = luaL_newstate();
  luaL_requiref(L, "game", luaopen_game_lib, 1);
  lua_pop(L, 1);
  luaL_openlibs(L);
  lua_register(L, "register_lua_state", register_lua_state_lua);
  if (luaL_dostring(L,
        " game = require(\"game\")\n gs = game.GameState.init()\n register_lua_state(gs)\n game.main_loop(gs)\n ") != LUA_OK) {
      fprintf(stderr, "Lua error: %s\n", lua_tostring(L, -1));
      lua_pop(L, 1);
      lua_close(L);
      return 1;
  }

  lua_close(L);
  return 0;
}

void update_draw_frame(void* gs_uncast) {
  GameState* gs = (GameState*)gs_uncast;
  gs_update(gs);
  gs_draw  (gs);
}
void main_loop(GameState* gs) {
#if defined(PLATFORM_WEB)
  emscripten_set_main_loop_arg(update_draw_frame, gs, 60, 1);
#else
  set_target_f_p_s(60);

  while ( !window_should_close() )
  {
    gs_update(gs);
    gs_draw(gs);
  }

  gs_free(gs);
#endif
}
