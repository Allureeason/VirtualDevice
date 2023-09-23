#include "Device.h"
#include "Log.h"
#include <cstdint>
#include <cstdio>
#include <mutex>
#include <vector>
#include <thread>
#include <functional>

IDevice::IDevice()
{
    m_id = GenerateSN();
}

IDevice::~IDevice()
{}

uint64_t IDevice::GenerateSN()
{
    static uint64_t s_sn = 0;
    return ++s_sn;
}

std::atomic<uint64_t> VirtualDevice::s_useCount{0};
std::atomic<uint64_t> VirtualDevice::s_handle{0};
std::uint64_t VirtualDevice::s_playHandle {0};

VirtualDevice::VirtualDevice()
    :IDevice()
{
    BLOG("");
}

VirtualDevice::~VirtualDevice()
{
    BLOG("");
}

bool VirtualDevice::Init()
{
    if(s_useCount.load() == 0)
    {
        BLOG("first init VirtualDevice");
    }
    s_useCount++;
    return true;
}

bool VirtualDevice::Login()
{
    BLOG("");
    auto handle = s_handle++;
    SetHandle(handle);
    return true;
}

bool VirtualDevice::Logout()
{
    SetHandle(-1);
    BLOG("");
    return false;
}

const std::string g_videoFilename = "test.h264";
uint64_t VirtualDevice::RealPlay()
{
    auto handle = GetHandle();
    if(handle == -1)
    {
        BLOG("invalid handle, please login.");
        return 1;
    }

    // 1. 读取文件
    FILE* fp = fopen(g_videoFilename.c_str(), "rb");
    if(!fp)
    {
        BLOG("open file " + g_videoFilename + " failed.");
        return 2;
    }
    BLOG("");
    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    auto dataSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    BLOG("open file size: " + std::to_string(dataSize));
    std::vector<uint8_t> data(dataSize);
    fread(&data[0], 1, dataSize, fp);
    fclose(fp);

    // 2. 码流分析/码流分帧
    auto frames = SplitFrame(&data[0], dataSize);

    // 3. 码流推送
    // 如果在这里直接去推送码流，会有什么问题？
    // 应该开一条线程出去，然后由这条线程去做码流推送逻辑
    std::lock_guard<std::mutex> lock(m_playMtx);
    uint64_t playHandle = s_playHandle++;
    m_playid2Thread[playHandle]
        = std::make_shared<std::thread>(std::bind(&VirtualDevice::PushStreamWorkFunc, this, playHandle, frames));
    m_playid2Status[playHandle] = 1;

    return playHandle;
}

bool VirtualDevice::Stop(uint64_t playHandle) 
{ 
    std::unique_lock<std::mutex> lock(m_playMtx);
    auto it = m_playid2Thread.find(playHandle);
    if(it != m_playid2Thread.end())
    {
        m_playid2Status[playHandle] = 0;
        lock.unlock();
        BLOG("");
        it->second->join();

        lock.lock();
        m_playid2Thread.erase(it);
    }

    return true;
}

std::vector<Frame> VirtualDevice::SplitFrame(const uint8_t* data, size_t size)
{
    BLOG("Do SplitFrame");
    return {};
}

void VirtualDevice::InputStreamFrame(const Frame& frame)
{
    BLOG("Do InputStreamFrame");
}

void VirtualDevice::PushStreamWorkFunc(uint64_t playHandle, const std::vector<Frame>& frames)
{
    while(true)
    {
        BLOG("Do PushStreamWorkFunc");
        std::lock_guard<std::mutex> lock(m_playMtx);
        auto it = m_playid2Status.find(playHandle);
        if(it->second == 0)
            break;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    BLOG("Stop PushStream");
}
