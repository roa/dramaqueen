#ifndef DRAMAQUEEN__HPP
#define DRAMAQUEEN__HPP

#include <iostream>
#include <fstream>
#include <sstream>

namespace Dramaqueen
{

class
{

public:
    //static  * getSingletonPtr();
    static  * getSingletonPtr();

    void log( std::string logMsg );
    void log( std::string logMsg, std::string extLogMsg );

private:
    static * singletonPtr;
    ();
    ( std::string _logDest );
    ( const & );
    ~();

    static std::string logDest;

    std::string createTimestamp();

};

}

#endif
