#ifndef __CALCLUM_H__
#define __CALCLUM_H__
#pragma once
#include <vector>
#include <string>
#include <memory>
#include <ctpl_stl.h>

#include "video.h"
#include "frame.h"
#include "container.h"


class calclum
{
    public:
        calclum(const std::vector<std::string>&, unsigned int);
        int run();
    
    private:
    
    private:
        static int calc(int, const std::string&, container& _container);
        
    private:
        const std::vector<std::string>& _files{};
        const unsigned int _threadcount{};
        std::unique_ptr<ctpl::thread_pool> _threadpool;
        container _container{};
};

#endif