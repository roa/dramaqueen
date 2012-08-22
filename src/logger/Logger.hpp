#ifndef DRAMAQUEEN_LOGGER_HPP
#define DRAMAQUEEN_LOGGER_HPP

#include <iostream>
#include <fstream>
#include <sstream>

namespace Dramaqueen
{

class Logger
{

public:
    static Logger * getSingletonPtr();
    static Logger * getSingletonPtr( std::string _logDest );

    void log( std::string logMsg );
    void log( std::string logMsg, std::string extLogMsg );

private:
    static Logger* singletonPtr;
    Logger();
    Logger( std::string _logDest );
    Logger( const Logger& );
    ~Logger();

    static std::string logDest;

    std::string createTimestamp();

};

}

#endif
