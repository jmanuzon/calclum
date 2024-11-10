#ifndef __CONTAINER_H__
#define __CONTAINER_H__
#pragma once
#include <string>
#include <vector>
#include "frame.h"

struct container_val
{
    std::string _filename{};
    uint8_t _minL{};
    uint8_t _maxL{}; 
    double _meanL{};
    uint8_t _medianL{};
};

struct container
{
public:
    void push(container_val val)
    {
        std::lock_guard lock(_mutex);
        _map.push_back(val);
    }

    auto size() const
    {
        return _map.size();
    }

    auto at(size_t index) const
    {
        return _map.at(index);
    }

    double getMedian(const std::vector<uint8_t>& val) const
    {
        std::vector<uint8_t> temp(val.begin(), val.end());
        
        auto m = temp.begin() + temp.size() / 2;

        std::nth_element(temp.begin(), m, temp.end());
        if(temp.size() % 2 == 0) 
        {
            auto lm = std::max_element(temp.begin(), m);
            return (*lm + *m) / (double)2;
        }

        return *m;
    }

private:
    std::vector<container_val> _map;
    std::mutex _mutex;
};

#endif