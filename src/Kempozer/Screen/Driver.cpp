/*
BSD 2-Clause License

Copyright (c) 2024, Bryan

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Kempozer/Screen/Driver.h"

namespace Kempozer::Screen {
    Driver *Driver::resolution(std::uint16_t& width, std::uint16_t& height) {
        if (rotated()) {
            width = mHeight;
            height = mWidth;
        } else {
            width = mWidth;
            height = mHeight;
        }
        return this;
    }
    
    Driver *Driver::writePixels(std::size_t count, const std::uint16_t *data) {
        for (size_t i = 0; i < count; ++i) {
            writePixel(data[i]);
        }
        return this;
    }

    Driver *Driver::writeRepeatedPixel(std::size_t count, const std::uint16_t color) {
        for (size_t i = 0; i < count; ++i) {
            writePixel(color);
        }
        return this;
    }

    Driver *Driver::write16(std::uint16_t u16) {
        write(std::uint8_t(u16));
        return write(std::uint8_t(u16 >> 8));
    }

    Driver *Driver::write32(std::uint32_t u32) {
        write16(std::uint16_t(u32));
        return write16(std::uint16_t(u32 >> 16));
    }

    Driver *Driver::write64(std::uint64_t u64) {
        write32(std::uint32_t(u64));
        return write32(std::uint32_t(u64 >> 32));
    }

    Driver *Driver::writeArray(std::size_t count, const std::uint8_t *data) {
        for (std::size_t i = 0; i < count; ++i) {
            write(data[i]);
        }
        return this;
    }

    void Driver::readPixels(std::size_t count, std::uint16_t *data) {
        for (std::size_t i = 0; i < count; ++i) {
            data[i] = readPixel();
        }
    }

    std::uint16_t Driver::read16() {
        return std::uint16_t(read()) | (std::uint16_t(read()) << 8);
    }

    std::uint32_t Driver::read32() {
        return std::uint32_t(read16()) | (std::uint32_t(read16()) << 16);
    }

    std::uint64_t Driver::read64() {
        return std::uint64_t(read32()) | (std::uint64_t(read32()) << 32);
    }

    void Driver::readArray(std::size_t count, std::uint8_t *data) {
        for (std::size_t i = 0; i < count; ++i) {
            data[i] = read();
        }
    }

    Driver *Driver::rotate(int rotation) {
        return this;
    }
}
