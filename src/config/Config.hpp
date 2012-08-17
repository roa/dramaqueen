#ifndef DRAMAQUEEN_CONFIG_HPP
#define DRAMAQUEEN_CONFIG_HPP

#include <lua.hpp>
#include <iostream>
#include "../logger/Logger.hpp"

namespace Dramaqueen
{

class Config
{

public:
    static Config* getSingletonPtr();

    void load( const char* fname );
    std::string getUser();

private:
    Config();
    Config( const Config& );
    ~Config();

    static Config* singletonPtr;
    Logger *logger;
    lua_State *L;
    std::string user;
};

}
#endif
