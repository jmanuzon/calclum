#ifndef __FRAME_H__
#define __FRAME_H__
#pragma once

#include <memory>
#include "helper.h"
#include "ffmpeg.h"

class frame
{
public:
    frame();
    frame(const frame&) = delete;
    frame& operator=(const frame&) = delete;

    frame(frame&&) = default;
    frame& operator=(frame&&) = default;

public:
    AVFrame* get() const {return _pFrame.get();}

private:
    std::shared_ptr<AVFrame> _pFrame; 
};

#endif