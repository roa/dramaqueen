#ifndef DRAMAQUEEN_DROPPRIVS_HPP
#define DRAMAQUEEN_DROPPRIVS_HPP

#include <sys/types.h>
#include <pwd.h>

#include <string.h>

#include "config/Config.hpp"
#include "logger/Logger.hpp"

namespace Dramaqueen
{

namespace Helper
{
    void dropPrivs();
}

}

#endif
