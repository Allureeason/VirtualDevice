#ifndef __BUSY_MEDIA_SERVICE_H__
#define __BUSY_MEDIA_SERVICE_H__

#include <memory>
class MediaService
{
public:
    MediaService* GetInstance()
    {
        static MediaService ms;
        return &ms;
    }

    bool Start();
    bool Stop();

private:
    MediaService() {}
    ~MediaService() {}

private:
};

#endif // __BUSY_MEDIA_SERVICE_H__
