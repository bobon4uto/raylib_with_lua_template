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

// :main
int main(void) {
#if !defined(_DEBUG)
  set_trace_log_level(LOG_NONE);
#endif
  // :init
  GameState gs = gs_init();

  main_loop(&gs);
  // :deinit
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
