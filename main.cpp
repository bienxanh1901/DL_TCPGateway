
#include "CloudGateway.h"

int main(int argc, char* argv[])
{
    CloudGateway* instance = CloudGateway::instance();
    instance->start();

    return 0;
}
