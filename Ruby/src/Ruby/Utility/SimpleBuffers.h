#pragma once

#include <cstring>
#include <stdint.h>

namespace Ruby 
{
    struct DataBuffer
    {
        uint8_t* Data = nullptr;
        uint64_t Size = 0;

        constexpr DataBuffer() noexcept = default;

        DataBuffer(uint64_t size) noexcept
        {
            Data = new uint8_t[size];
            Size = size;
        }

        // Wraps an existing pointer to a buffer, but does not take ownership, as
        // the releasing of the memory is still controlled by the user, not automatic.
        DataBuffer(uint8_t* buffer, uint64_t size) noexcept
        {
            Data = buffer;
            Size = size;
        }

        DataBuffer(DataBuffer&& other) noexcept
        {
            Data = other.Data;
            Size = other.Size;
            other.Data = nullptr;
        }

        DataBuffer(const DataBuffer& other) noexcept
        {
            Data = new uint8_t[other.Size];
            memcpy(Data, other.Data, other.Size);
            Size = other.Size;
        }

        ~DataBuffer() noexcept = default;

        inline void allocate(uint64_t size)
        {
            clear();

            Data = new uint8_t[size];
            Size = size;
        }

        inline void clear()
        {
            delete[] Data;
            Data = nullptr;
            Size = 0;
        }

        inline operator bool() const
        {
            return Data == nullptr;
        }

    };

    struct ScopedBuffer
    {
        uint8_t* Data = nullptr;
        uint64_t Size = 0;

        constexpr ScopedBuffer() noexcept = default;

        ScopedBuffer(uint64_t size) noexcept
        {
            Data = new uint8_t[size];
            Size = size;
        }

        ScopedBuffer(const DataBuffer& buffer) noexcept
        {
            Data = new uint8_t[buffer.Size];
            Size = buffer.Size;
        }

        ScopedBuffer(DataBuffer&& buffer) noexcept
        {
            Data = buffer.Data;
            Size = buffer.Size;
            buffer.Data = nullptr;
        }

        ScopedBuffer(ScopedBuffer&& other) noexcept // Takes ownership of buffer
        {
            Data = other.Data;
            Size = other.Size;
            other.Data = nullptr;
        }

        ScopedBuffer(const ScopedBuffer& other) noexcept // Creates new buffer.
        {
            Data = new uint8_t[other.Size];
            memcpy(Data, other.Data, other.Size);
            Size = other.Size;
        }

        ~ScopedBuffer() noexcept
        {
            delete[] Data;
        }

        inline operator bool() const
        {
            return Data == nullptr;
        }

        explicit inline operator DataBuffer() const
        {
            DataBuffer buffer;
            buffer.Data = Data;
            buffer.Size = Size;
            return buffer;
        }

    };

}