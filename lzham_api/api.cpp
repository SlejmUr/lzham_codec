/*
 * MIT License

 * Copyright (c) 2023 Pawe³ Lidwin

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.


 * --------------------------------------------------------------------------------

 * Made to Dll: SlejmUr

 *
 */


#include "pch.h"

#include <iostream>
#include <cstring>

#define EXPORT extern "C" _declspec(dllexport)

#define LZHAM_DEFINE_ZLIB_API

#include "../include/lzham_dynamic_lib.h"
#include <string>
#include <fstream>

#define uint8 unsigned char

EXPORT int decompress(BYTE* source, size_t source_size, BYTE* dest, size_t decompressed_size) {
    z_stream stream;

    stream.next_in = source;
    stream.avail_in = source_size;
    stream.next_out = dest;
    stream.avail_out = decompressed_size;

    if (inflateInit2(&stream, Z_DEFAULT_WINDOW_BITS) != Z_OK) {
        std::cerr << "Failed to init inflate" << std::endl;
        return 1;
    }
    int status;
    while (stream.avail_in) {

        status = inflate(&stream, Z_NO_FLUSH);
        if (status == Z_STREAM_END) {
            break;
        }

        if (status != Z_OK) {
            std::cerr << "Error decompressing " << status << std::endl;
            if (status == LZHAM_Z_DATA_ERROR) {
                std::cerr << "Invalid data" << std::endl;
            }
            inflateEnd(&stream);
            return 1;
        }

    }
    inflateEnd(&stream);
    return 0;
}