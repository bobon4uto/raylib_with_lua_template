#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

// :macro
#define RAYLIB_PATH "./thirdparty/raylib"
#define LUA_PATH "./thirdparty/lua"

#define MODULES_(T) \
  T("game_state") \
  T("noutil")

// :type
typedef enum {
  TARGET_LINUX,
  TARGET_HTML5,
} Target;

typedef enum {
  BUILD_DEBUG,
  BUILD_RELEASE,
} BuildState;

typedef struct sDAcstr {
  size_t capacity;
  size_t count;
  char** items;
} DAcstr;

typedef struct sOptions {
  Target target;
  BuildState build_state;
  bool integrate_lua;
} Options;

// :glob
Cmd cmd0 = {0};
Cmd* cmd = &cmd0;
Options ops = {0};
DAcstr objects = {0};
bool force = true;
// :func
Options ops_default();
Target target_from_letter(char letter);
BuildState build_state_from_letter(char letter);

void cc_cflags(Cmd* cmd);
void cc_ldflags(Cmd* cmd);
void cc_exflags(Cmd* cmd);

void build_();

int main(int argc, char** argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);

  mkdir_if_not_exists("build");
  mkdir_if_not_exists("build/obj");
  mkdir_if_not_exists("build/gen");

  ops = ops_default();
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      ops.target = target_from_letter(argv[i][0]);
    } else {
      ops.build_state = build_state_from_letter(argv[i][1]);
      if (argv[i][1] != '\0') {
        if (argv[i][2] == 'l') {
          ops.integrate_lua = true;
        } else {
          ops.integrate_lua = false;
        }
      }
    }
  }

  if (ops.target == TARGET_HTML5) {
    mkdir_if_not_exists("build/web");
  }

  build_();

  da_free(objects);

}


Options ops_default() {
  Options self = {0};

  self.target = target_from_letter('\0');
  self.build_state = build_state_from_letter('\0');
  self.integrate_lua = true;

  return self;
}
Target target_from_letter(char letter) {
  switch (letter) {
    case 'l': return TARGET_LINUX;
    case 'h': return TARGET_HTML5;
    default:  return TARGET_LINUX;
  }
}
BuildState build_state_from_letter(char letter) {
  switch (letter) {
    case 'd': return BUILD_DEBUG;
    case 'r': return BUILD_RELEASE;
    default: return BUILD_DEBUG;
  }
}

void cc_(Cmd* cmd) {
  if (ops.target == TARGET_LINUX) {
    nob_cc(cmd);
  } else if (ops.target == TARGET_HTML5) {
    //cmd_append(cmd, "clang", "--target=wasm32");
    cmd_append(cmd, "emcc");
  }
}
void clink_(Cmd* cmd) {
  if (ops.target == TARGET_LINUX) {
    nob_cc(cmd);
  } else if (ops.target == TARGET_HTML5) {
    cmd_append(cmd, "emcc");
  }
}
void cc_cflags(Cmd* cmd) {

  cmd_append(cmd, "-Wall", "-Wextra", "-Werror", "-std=gnu23", "-D_DEFAULT_SOURCE", "-g"  );
  if (ops.target == TARGET_HTML5) {
    cmd_append(cmd, "-Wno-error=version-check");
    cmd_append(cmd, "-DPLATFORM_WEB");
  } // I have very clunky install of emcc


  if (ops.build_state == BUILD_DEBUG) {
    cmd_append(cmd, "-D_DEBUG");
  } else if (ops.build_state == BUILD_RELEASE) {
    cmd_append(cmd, "-D_RELEASE");
  }

  cmd_append(cmd, "-I.", "-I"RAYLIB_PATH"/src", "-I"RAYLIB_PATH"/src/external");
  if (ops.integrate_lua) {
    cmd_append(cmd, "-I"LUA_PATH"/src");
    cmd_append(cmd, "-DSUPPORT_LUA");
  }

}
void cc_ldflags(Cmd* cmd) {

  if (ops.target == TARGET_LINUX) {
    cmd_append(cmd, "-L"RAYLIB_PATH"/src", "-lraylib","-lm","-lX11");
  } else if (ops.target == TARGET_HTML5) {
    cmd_append(cmd, "-L"RAYLIB_PATH"/src", "-lraylib.web");
  }
  if (ops.integrate_lua) {
    if (ops.target == TARGET_LINUX) {
      cmd_append(cmd, "-L"LUA_PATH"/src", "-llua");
    } else if (ops.target == TARGET_HTML5) {
      cmd_append(cmd, "-L"LUA_PATH"/src", "-llua.web");
    }
  }
}
void cc_exflags(Cmd* cmd) {
  if (ops.target == TARGET_HTML5) {
    cmd_append(cmd, "-DPLATFORM_WEB",
      "-s", "USE_GLFW=3",
      "-s", "ASYNCIFY",
      //"-s", "TOTAL_MEMORY=67108864",
      "-s", "TOTAL_MEMORY=67108864",
      "-s", "STACK_SIZE=10000000",
      //"-s", "STACK_SIIZE=65536",
//      "-s", "ALLOW_MEMORY_GROWTH",
      "-s", "FORCE_FILESYSTEM=1",
      "-s", "EXPORTED_RUNTIME_METHODS=ccall",
      "--preload-file", "./assets",
      "--shell-file", "src/shell.html"
    );
  }
}

#define BUILD_O(FILE) do {\
  cc_(cmd); \
  cmd_append(cmd, "-c"); \
  const char* in_file = "src/"FILE".c"; \
  char* out_file = "build/obj/"FILE".o"; \
  da_append(&objects, out_file); \
  if ( file_exists("src/"FILE".c") ) { \
    in_file = "src/"FILE".c"; \
    nob_cc_inputs(cmd, "src/"FILE".c"); \
  } else if ( file_exists("src/"FILE".h") ) { \
    cmd_append(cmd, "-DMONO_BUILD"); \
    cmd_append(cmd, "-x", "c"); \
    nob_cc_inputs(cmd, "src/"FILE".h"); \
    in_file = "src/"FILE".h"; \
  } else { \
    nob_log(NOB_ERROR, "error building " FILE "\n no module file found"); exit(1); \
  } \
  if (force || nob_needs_rebuild1(out_file, in_file)) { \
    nob_cc_output(cmd, out_file); \
    nob_cc_flags(cmd); \
    cc_cflags(cmd); \
    if (!cmd_run(cmd)) { \
      nob_log(NOB_ERROR, "error building " FILE); exit(1); \
    }; \
  } else { \
    cmd->count = 0; \
    nob_log(NOB_INFO, "Not building " FILE); \
  } \
} while (0)

void build_() {


  if (ops.integrate_lua) {

    cmd_append(cmd, "./thirdparty/lua_embed/build/util/stage0",
        "src/base_types.h", "src/lua_main.c", "src/game_state.h",
        "-n", "game", "-o", "build/gen/game.c");
    if (!cmd_run(cmd) ) {
      nob_log(NOB_ERROR, "Failed to generate lua bindings");
      exit(1);
    }



    BUILD_O("base_types");
    BUILD_O("lua_main");
  } else {
    BUILD_O("main");
  }
#define UNWRAP_MODULES(MODULE) BUILD_O(MODULE);
  MODULES_(UNWRAP_MODULES)

  clink_(cmd);
  for (size_t i = 0; i < objects.count; ++i) {
    nob_cc_inputs(cmd, objects.items[i]);
  }
  char* game_exe = "build/game.exe";
  if (ops.target == TARGET_LINUX) {
    game_exe = "build/game";
  } else if (ops.target == TARGET_HTML5) {
    game_exe = "build/web/index.html";
  }
  nob_cc_output(cmd, game_exe);
  nob_cc_flags(cmd);
  cc_cflags(cmd);
  cc_ldflags(cmd);
  cc_exflags(cmd);

  if ( cmd_run(cmd) && ops.target!=TARGET_HTML5 ) {
    cmd_append(cmd, game_exe);
    cmd_run(cmd);
  }
}
