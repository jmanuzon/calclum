#include "frame.h"
#include <stdexcept>

frame::frame()
{
    _pFrame = std::unique_ptr<AVFrame, DeleterPtr<AVFrame, void, av_frame_free>>
    { av_frame_alloc() };

    if(!_pFrame)
    {
        throw std::runtime_error("av_frame_alloc failed.");
    }
}

