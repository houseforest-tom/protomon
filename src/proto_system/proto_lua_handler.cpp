#include "../../include/proto_system/proto_lua_handler.h"
#include "../../include/proto_system/proto_dialog_system.h"

lua_State *ProtoLuaHandler::m_pLuaState = nullptr;

void ProtoLuaHandler::init(void)
{
    //Create Lua State if non-existent
    m_pLuaState = ((m_pLuaState != nullptr) ? m_pLuaState : luaL_newstate());

    //Open Lua Libraries (math, stdio, ...)
    luaL_openlibs();

    /*
    static const luaL_Reg lualibs[] =
    {
        { "base",   luaopen_base },
        { nullptr,  nullptr}
    };

    const luaL_Reg *lib = lualibs;
    for(; lib->func != nullptr; lib++)
    {
        lib->func(m_pLuaState);
        lua_settop(m_pLuaState, 0);
    }
    */

    lua_register(m_pLuaState, "enqmsg", &proto_lua_enqmsg);
}

void ProtoLuaHandler::executeFile(const string &file)
{
    luaL_dofile(m_pLuaState, file.c_str());
}

void ProtoLuaHandler::destroy(void)
{
    if(m_pLuaState != nullptr)
        lua_close(m_pLuaState);
}

int proto_lua_enqmsg(lua_State *L)
{
    const char *msg = lua_tostring(L, 1);
    ProtoDialogSystem::enqueueMessage(string(msg));
    return 0;
}
