#include <iostream>
#include <chrono>

#include "calclum.h"
#include "video.h"
#include "helper.h"

calclum::calclum(const std::vector<std::string>& files, unsigned int threadcount) :
_files{files},
_threadcount{threadcount},
_threadpool{std::make_unique<ctpl::thread_pool>(threadcount)}
{
}

int calclum::calc(int id, const std::string& filename, container& _container)
{
    std::cout << "Started processing video:" <<  filename << " using threadid:" << id << '\n';

    video vid(filename);
    auto frames = vid.getFrames();
    if(frames.size() <= 0)
    {
        return 1;
    }

    long long luminance{};
    unsigned long luminance_count{};

    uint8_t minL{255};
    uint8_t maxL{0}; 
    uint8_t histogram[256]{};

    for(auto i = 0; i < frames.size(); ++i)
    {
        auto height = frames[i].getPtr()->height;
        auto width = frames[i].getPtr()->width;
        auto framesize = height * width;

        for(auto y = 0; y < height; ++y)
        {
            for(auto x = 0; x < width; ++x)
            {
                auto lum = frames[i].getPtr()->data[0][y * frames[i].getPtr()->linesize[0] + x];
                if(minL != 0)
                    minL = std::min(minL, lum);
                if(maxL != 255)
                    maxL = std::max(maxL, lum);

                //lumv.push_back(lum);
                histogram[lum]++;
                luminance+= lum;
                luminance_count++;
            }
        }
    }

    auto meanL = luminance/(double)luminance_count;
    //compute the median

    unsigned int sum{};
    for(int i = 0; i <= 255; ++i)
    {
        sum+=histogram[i];
    }

    auto index = sum / 2;

    unsigned int total{};
    uint8_t medianL{};
    for(uint8_t i = 0; i <= 255; ++i)
    {
        total += histogram[i];
        if( total > index)
        {
            medianL = i;
            break;
        }
    }

    container_val val;
    val._filename = filename;
    val._minL = minL;
    val._maxL = maxL;
    val._meanL = meanL;
    val._medianL = medianL;
    _container.push(val);

    std::cout << "************************Done processing video:" <<  filename << "************************" << '\n';
    std::cout << " min L:" << unsigned(minL) << 
        ", max L:" << unsigned(maxL) <<
        ", mean L:" << meanL <<
        ", median L:" << unsigned(medianL) << '\n';
     std::cout << "**********************************************************************************************\n";

    return 0;
}

int calclum::run()
{
    //process the video instance in a new thread
    for(const auto& file : _files)
    {
        _threadpool->push(&calclum::calc, std::ref(file), std::ref(_container));
    }

    //wait for all the work to finish
    _threadpool->stop(true);

    std::cout << "************************All files properties:************************\n";

    uint8_t minL{255};
    uint8_t maxL{0};
    double meanL{0.0};
    uint8_t medianL{0};
    std::vector<uint8_t> medians{};
     
    for(auto i = 0; i < _container.size(); ++i)
    {
        minL = std::min(minL, _container.at(i)._minL);
        maxL = std::max(maxL, _container.at(i)._maxL);
        meanL += _container.at(i)._meanL;
        medians.push_back(_container.at(i)._medianL);
    }

    std::cout << " min L:" << unsigned(minL) << 
        ", max L:" << unsigned(maxL) <<
        ", mean L:" << meanL/(double)_container.size() <<
        ", median L:" << _container.getMedian(medians) << '\n';
    std::cout << "**********************************************************************************************\n";

    return 0;
}

