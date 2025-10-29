#include "Networking/Utils.h"
#include <mongoose.h>
#include <sstream>
#include <string>

std::string addrString(mg_addr& addr)
{
    std::stringstream ss;
    ss << (int)addr.ip[0] << "." << (int)addr.ip[1] << "." << (int)addr.ip[2] << "." << (int)addr.ip[3] << ":"
       << addr.port;

    return ss.str();
}

