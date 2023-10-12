#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <unistd.h>

#include "Device.h"
#include "Log.h"
#include "mk_frame.h"
#include "mk_media.h"


void TestSn()
{
    std::vector<IDevice::Ptr> devices;
    // for(int i = 0; i < 100; i++)
    //     devices.push_back(std::make_shared<VirtualDevice>());

    std::vector<std::thread> workers;
    std::mutex mtx;
    for(int i = 0; i < 20; i++)
        workers.push_back(std::thread([&devices, &mtx](){
                                         for(int i = 0; i < 1000; i++)
                                         {
                                         std::lock_guard<std::mutex> lock(mtx);
                                         devices.push_back(std::make_shared<VirtualDevice>());
                                         }
                                         }));


    for(auto& worker : workers)
        worker.join();

    for(auto dev :devices)
        std::cout << dev->ToString();
}

void TestMediaSource()
{
}

int main(int argc, char* argv[])
{

    BLOG("test log");
    getchar();

    VirtualDevice dev;
    dev.Init();
    dev.Login();
    auto playHandle = dev.RealPlay();

    sleep(5);

    dev.Stop(playHandle);

    // TestSn();
    // sleep(5);

    return 0;
}
