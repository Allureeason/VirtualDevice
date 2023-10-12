#ifndef __BUSY_DEVICE_H__
#define __BUSY_DEVICE_H__

#include <cstdint>
#include <memory>
#include <atomic>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>
#include <map>

class IDevice
{
public:
    using Ptr = std::shared_ptr<IDevice>;


    IDevice();
    virtual ~IDevice();

    // 初始化接口
    virtual bool Init() = 0;
    // 登录
    virtual bool Login() = 0;
    // 登出
    virtual bool Logout() = 0;
    // 视频播放
    virtual uint64_t RealPlay() = 0;
    // 视频关闭
    virtual bool Stop(uint64_t playHandle) = 0;

    int64_t GetId() const { return m_id;}
    int64_t GetHandle() const { return m_handle;}
    void SetHandle(uint64_t handle) { m_handle = handle;}

    std::string ToString() const
    {
        std::stringstream ss;
        ss << "Device id[" << m_id << "] handle[" << m_handle << "]" << std::endl;
        return ss.str();
    }

private:
    static uint64_t GenerateSN();

private:
    int64_t m_id = 0;
    int64_t m_handle = -1;
};

struct Frame
{
    uint8_t* p = nullptr;
    size_t len = 0;
};

class VirtualDevice : public IDevice
{
public:
    VirtualDevice();
    virtual ~VirtualDevice();

    // 初始化接口
    virtual bool Init() override;
    // 登录
    virtual bool Login() override;
    // 登出
    virtual bool Logout() override;
    // 视频播放
    virtual uint64_t RealPlay() override;
    // 视频关闭
    virtual bool Stop(uint64_t playHandle) override;

private:
    std::vector<Frame> SplitFrame(const uint8_t* data, size_t size);
    void InputStreamFrame(const Frame& frame);
    void PushStreamWorkFunc(uint64_t playHandle, const std::vector<Frame>& frames);
private:
    static std::atomic<uint64_t> s_useCount;
    static std::atomic<int64_t> s_handle;
    static std::uint64_t s_playHandle;

    std::map<uint64_t, std::shared_ptr<std::thread>> m_playid2Thread;
    std::map<uint64_t, int> m_playid2Status;
    std::mutex m_playMtx;
};

// 海康、大华、宇视、华为
// 不一样的SDK 接入，
// HKDevice DHDevice
// dev1     dev2
// 行为-> RealPlay() dev1->RealPlay() dev2->RealPlay()
//
// DevMgr -> GetDev(type, id) -> return IDevice::ptr; ptr->RealPlay() // 多态
// DevMgr -> GetHKDev(id) -> return value ?
// DevMgr -> GetHDDev(id) -> return value ?
// 上层调度管理 需要考虑下层扩展改动是否会改动到上层调度

#endif // __BUSY_DEVICE_H__
