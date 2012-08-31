/**
    the serverforge object is used to start the baseserver node.
    if a server dies, it is not restarted. on most server failures
    abort() is called to ensure, that the programm dies loadly.
    servers are expected to run forever, but they will never try
    to catch exceptions nor will they start if it is not sure, they will work
**/
#ifndef DRAMAQUEEN_SERVERFORGE_HPP
#define DRAMAQUEEN_SERVERFORGE_HPP

#include "BaseServer.hpp"
#include "../helper/Helper.hpp"

namespace Dramaqueen
{

class ServerForge
{

public:
    void operator() () const;

};

}

#endif
