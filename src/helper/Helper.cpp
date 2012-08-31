#include "Helper.hpp"

namespace Dramaqueen
{

namespace Helper
{

void dropPrivs()
{
    passwd *pw = getpwnam( Config::getSingletonPtr()->getUser().c_str() );
    if( getuid() == 0)
    {
        if( setgid( pw->pw_gid ) != 0 )
            log( "setgid: Unable to drop group privileges:", strerror( errno ) );
        if( setuid( pw->pw_uid ) != 0 )
            log( "setuid: Unable to drop user privileges:", strerror( errno ) );
    }
}

void log( std::string logMsg )
{
    std::ofstream logFile;
    logFile.open ( Config::getSingletonPtr()->getLogDest(), std::ios::app );

    logFile << createTimestamp()
            << "    "
            << logMsg
            << std::endl;

    logFile.close();
}

void log( std::string logMsg, std::string logMsg2 )
{
    std::ofstream logFile;
    logFile.open ( Config::getSingletonPtr()->getLogDest(), std::ios::app );

    logFile << createTimestamp()
            << "    "
            << logMsg
            << " "
            << logMsg2
            << std::endl;

    logFile.close();
}

void log( std::string logMsg, std::string logMsg2, std::string logMsg3 )
{
    std::ofstream logFile;
    logFile.open ( Config::getSingletonPtr()->getLogDest(), std::ios::app );

    logFile << createTimestamp()
            << "    "
            << logMsg
            << " "
            << logMsg2
            << " "
            << logMsg3
            << std::endl;

    logFile.close();
}

std::string createTimestamp()
{
    std::stringstream timestamp;
    time_t rawtime;
    struct tm * timeinfo;
    time( &rawtime );
    timeinfo = localtime( &rawtime );
    timestamp   << timeinfo->tm_year + 1900 << "-";
    if( timeinfo->tm_mon < 10 )
    {
        timestamp << 0 << timeinfo->tm_mon  << "-";
    }
    else
    {
        timestamp << timeinfo->tm_mon  << "-";
    }

    if( timeinfo->tm_mday < 10 )
    {
        timestamp << 0 << timeinfo->tm_mday  << "-";
    }
    else
    {
        timestamp << timeinfo->tm_mday << " ";
    }

    if( timeinfo->tm_hour < 10 )
    {
        timestamp << 0 << timeinfo->tm_hour  << ":";
    }
    else
    {
        timestamp << timeinfo->tm_hour << ":";
    }

    if( timeinfo->tm_min < 10 )
    {
        timestamp << 0 << timeinfo->tm_min  << ":";
    }
    else
    {
        timestamp << timeinfo->tm_min << ":";
    }

    if( timeinfo->tm_sec < 10 )
    {
        timestamp << 0 << timeinfo->tm_sec;
    }
    else
    {
        timestamp << timeinfo->tm_sec;
    }
    return timestamp.str();
}

}

}
