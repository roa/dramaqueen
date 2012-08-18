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

    std::string getUser();
    std::string getGroup();
    std::string getXmppUser();
    std::string getXmppPasswd();

private:
    Config();
    Config( const Config& );
    ~Config();

    void load( const char* fname );

    static Config* singletonPtr;
    Logger *logger;
    lua_State *L;

    std::string user;
    std::string group;
    std::string xmppUser;
    std::string xmppPasswd;

};

}
#endif
