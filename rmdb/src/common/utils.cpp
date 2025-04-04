#include <string>
#include <cstring>
#include <algorithm>
#include "common.h"

namespace common {

    int compareIgnoreCase(const char* str1, const char* str2) {
        std::string str1Lower = str1;
        std::string str2Lower = str2;
    
        // 转换为小写
        std::transform(str1Lower.begin(), str1Lower.end(), str1Lower.begin(), ::tolower);
        std::transform(str2Lower.begin(), str2Lower.end(), str2Lower.begin(), ::tolower);
    
        return strcmp(str1Lower.c_str(), str2Lower.c_str());
    }
    
    int compare_string(void *arg1, int arg1_max_length, void *arg2, int arg2_max_length)
    {
        const char *s1     = (const char *)arg1;
        const char *s2     = (const char *)arg2;
        int         maxlen = std::min(arg1_max_length, arg2_max_length);
        int         result = strncmp(s1, s2, maxlen);
        if (0 != result) {
            return result < 0 ? -1 : 1;
        }
    
        if (arg1_max_length > maxlen) {
            return 1;
        }
    
        if (arg2_max_length > maxlen) {
            return -1;
        }
        return 0;
    }
    
    int compare_int(void *arg1, void *arg2)
    {
        int v1 = *(int *)arg1;
        int v2 = *(int *)arg2;
        if (v1 > v2) {
            return 1;
        } else if (v1 < v2) {
            return -1;
        } else {
            return 0;
        }
    }
    
    int compare_float(void *arg1, void *arg2)
    {
        float v1  = *(float *)arg1;
        float v2  = *(float *)arg2;
        float cmp = v1 - v2;
        if (cmp > 0) {
            return 1;
        }
        if (cmp < 0) {
            return -1;
        }
        return 0;
    }
    
    std::string double_to_str(double v)
    {
        char buf[256];
        snprintf(buf, sizeof(buf), "%.2f", v);
        size_t len = strlen(buf);
        while (buf[len - 1] == '0') {
            len--;
        }
        if (buf[len - 1] == '.') {
            len--;
        }
    
        return std::string(buf, len);
    }
    
    };