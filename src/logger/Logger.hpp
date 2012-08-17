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
    static Logger* getSingletonPtr();
    void log( std::string logMsg );
    void log( std::string logMsg, std::string extLogMsg );

private:
    static Logger* singletonPtr;
    Logger();
    Logger( const Logger& );
    ~Logger();

    std::string createTimestamp();
};

}

#endif
