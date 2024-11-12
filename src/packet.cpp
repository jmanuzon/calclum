#include <stdexcept>
#include "packet.h"

packet::packet()
{
    _packet = std::unique_ptr<AVPacket, DeleterPtr<AVPacket, void, av_packet_free>>{av_packet_alloc()};

    if (!_packet.get())
    {
        throw std::runtime_error("av_packet_alloc failed"); 
    }
}