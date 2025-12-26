#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "sha256.h"

static char *LUA_SHA256 = "lua_sha256";
static char *LUA_CYPHER = "lua_crypher";

int lua_sha256_new(lua_State* L) {
    SHA256_CTX *ctx = lua_newuserdata(L, sizeof(SHA256_CTX));
    sha256_init(ctx);
    luaL_newmetatable(L, LUA_SHA256);
    lua_setmetatable(L, -2);
    return 1;
}

int lua_sha256_update(lua_State* L) {
    if (!lua_isuserdata(L, 1)) {
        return luaL_argerror(L, 1, "the sha256 update invalid.");
    }
    SHA256_CTX *ctx = (SHA256_CTX*)lua_touserdata(L, 1);
    if (lua_isstring(L, 2)) {
        size_t len;
        const char *p = lua_tolstring(L, 2, &len);
        if (len > 0) {
            sha256_update(ctx, (const BYTE*)p, len);
        }
    }
    return 0;
}

int lua_sha256_final(lua_State* L) {
    if (!lua_isuserdata(L, 1)) {
        return luaL_argerror(L, 1, "the sha256 final invalid.");
    }
    SHA256_CTX *ctx = (SHA256_CTX*)lua_touserdata(L, 1);
    const char buf[SHA256_BLOCK_SIZE] = {0};
    sha256_final(ctx, (BYTE*)buf);
    lua_pushlstring(L, buf, SHA256_BLOCK_SIZE);
    return 1;
}

static luaL_Reg sha256_lib[] = {
    {"new", lua_sha256_new},
    {"update", lua_sha256_update},
    {"final", lua_sha256_final},
    {0, 0}
};

static void sha256_register(lua_State *L) {
    lua_newtable(L);
    luaL_newmetatable(L, LUA_SHA256);
    lua_newtable(L);
    luaL_setfuncs(L, sha256_lib, 0);
    lua_setfield(L, -2, "__index");
    lua_setmetatable(L,  -2);
    lua_setfield(L, -2, "sha256");
}

int luaopen_cypher(lua_State *L) {
    luaL_newmetatable(L, LUA_CYPHER);
    sha256_register(L);
    return 1;
}