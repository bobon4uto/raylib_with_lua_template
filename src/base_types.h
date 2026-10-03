#ifdef    MONO_BUILD
#define BASE_TYPES_IMPLEMENTATION
#endif // MONO_BUILD
#ifndef    _BASE_TYPES_H_
#define    _BASE_TYPES_H_


// base_types interface
#include <lua.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <stdio.h>
#include "noutil.h"

#ifdef FAKEOUT
// this way we can register types without ever defining their attributes.
typedef struct svoid void;
typedef struct sint   int;
typedef struct su       u;
typedef struct schar char;
// you can also expose part of the attributes
typedef struct sStringBuilder {
  u capacity;
  u count;
  // char* items;
} StringBuilder;
#endif // FAKEOUT

// :fint
// theese functions are overriding default(udata) checks and pushes
int   int_check_lua(lua_State* L, int     index    );
void   int_push_lua(lua_State* L, int     self     );
// :fu
u     u_check_lua(lua_State* L, int     index    );
void   u_push_lua(lua_State* L, u       self     );
// :fchar
char*  char_check_lua(lua_State* L, int   index    );
void    char_push_lua(lua_State* L, char* self     );

// :fStringBuilder
char*         sb___tostring      (StringBuilder* self);
StringBuilder sb_clone           (StringBuilder* self);
StringBuilder sb_new             (char* s);
// free is mapped to __gc
// you can do sb___gc instead
void          string_builder_free(StringBuilder* self);
#ifdef      BASE_TYPES_IMPLEMENTATION
// base_types implementation

#ifndef   BT_LOG
#define   BT_LOG(...) do { printf("base types: "); printf(__VA_ARGS__); printf("\n"); fflush(stdout); } while (0)
#endif // BT_LOG

// :iint
int   int_check_lua(lua_State* L, int     index  ) {
  return luaL_checkinteger(L, index);
}
void  int_push_lua(lua_State* L, int     self   ) {
  lua_pushinteger(L, (lua_Integer)self );
}
// :iu
u     u_check_lua(lua_State* L, int     index    ) {
  lua_Integer i = luaL_checkinteger(L, index);
  if (i < 0) {
    luaL_error(L, "unsigned cannot be negative");
  }
  return (u)i;
}
void   u_push_lua(lua_State* L, u       self     ) {
  lua_pushinteger(L, (lua_Integer)self );
}
// :ichar
char*  char_check_lua(lua_State* L, int   index    ) {
  return (char*)luaL_checkstring(L, index);
}
void    char_push_lua(lua_State* L, char* self     ) {
  lua_pushlstring(L, self, strlen(self));
}
// :iStringBuilder
char* sb___tostring(StringBuilder* self) {
  char* ret = sb_to_str(self);
  return ret;
}
StringBuilder sb_clone           (StringBuilder* self) {
  return sb_from_sv(sv_from_sb(*self));
}
StringBuilder sb_new             (char* s) {
  return sb_from_str(s);
}
void          string_builder_free(StringBuilder* self) {
  BT_LOG( "Freeing [%p] {%.*s}", self->items, SB_FMT(*self) );
  sb_free(self);
}

#endif   // BASE_TYPES_IMPLEMENTATION
#endif   //_BASE_TYPES_H_


