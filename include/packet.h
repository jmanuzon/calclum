#ifndef __PACKET_H__
#define __PACKET_H__

#include <memory>
#include "ffmpeg.h"
#include "helper.h"

class packet
{
public:
    packet();
    packet(const packet&) = delete;
    packet& operator=(const packet&) = delete;

    packet(packet&&) = default;
    packet& operator=(packet&&) = default;

public:
    AVPacket* getPtr() const { return _packet.get(); }
    void unref() const { av_packet_unref(_packet.get()); } 

private:
    std::unique_ptr<AVPacket, DeleterPtr<AVPacket, void, av_packet_free>> _packet;
};

#endif