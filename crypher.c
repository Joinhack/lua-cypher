
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "sha256.h"

static char *LUA_SHA256 = "lua_sha256";
static char *LUA_CRYPHER = "lua_crypher";

int lua_sha256_new(lua_State* L) {
    SHA256_CTX *ctx = lua_newuserdata(L, sizeof(SHA256_CTX));
    sha256_init(ctx);
    luaL_newmetatable(L, LUA_SHA256);
    lua_setmetatable(L, -2);
    return 1;
}


static luaL_Reg sha256_lib[] = {
    {"new", lua_sha256_new},
    // {"update", sha256_update},
    {0, 0}
};

static int sha256_register(lua_State *L) {
    luaL_newmetatable(L, LUA_SHA256);
    lua_newtable(L);
    luaL_setfuncs(L, sha256_lib, 0);
    lua_setfield(L, -2, "__index");
}

int luaopen_crypher(lua_State *L) {
    luaL_newmetatable(L, LUA_CRYPHER);
    sha256_register(L);
    return 1;
}