#ifndef __HELPER_H__
#define __HELPER_H__
#pragma once

template<typename T, typename R, R(*Fn)(T**)> struct DeleterPtr {
    inline void operator() (T* ptr) const {
        if (ptr) Fn(&ptr);
    }
};

#endif