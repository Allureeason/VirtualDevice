#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <unistd.h>

#include "Device.h"
#include "Log.h"

int main(int argc, char* argv[])
{

    BLOG("test log");

    VirtualDevice dev;
    dev.Init();
    dev.Login();
    auto playHandle = dev.RealPlay();

    sleep(5);

    dev.Stop(playHandle);

    return 0;
}
