#ifndef __BUSY_LOG_H__
#define __BUSY_LOG_H__

#include <cstdint>
#include <thread>
#include <ostream>
#include <sstream>
#include <iosfwd>

#define BLOG(str) \
    do { \
        std::string s(str); \
        printf("[%s %s][%s][%s:%d] %s\n", __DATE__, __TIME__, \
               __FUNCTION__, __FILE__, __LINE__, s.c_str()); \
    }while(0);

#endif // __BUSY_LOG_H__
