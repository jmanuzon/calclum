#include "frame.h"
#include <stdexcept>

frame::frame()
{
    _pFrame = std::shared_ptr<AVFrame>(av_frame_alloc(),
    DeleterPtr<AVFrame, void, av_frame_free>());

    if(!_pFrame)
    {
        throw std::runtime_error("av_frame_alloc failed.");
    }
}

