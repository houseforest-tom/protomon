#pragma once

#include <lua.hpp>
#include "proto_enums.h"

class ProtoLuaHandler
{
private:
    static lua_State *m_pLuaState;

public:
    static void init(void);
    static void executeFile(const string &file);
    static void destroy(void);
};

int proto_lua_enqmsg    (lua_State *L);
int proto_lua_enqqst    (lua_State *L);
int proto_lua_freeze    (lua_State *L);
int proto_lua_unfreeze  (lua_State *L);
int proto_lua_turn      (lua_State *L);
int proto_lua_walk      (lua_State *L);
int proto_lua_wbattle   (lua_State *L);
int proto_lua_tbattle   (lua_State *L);
