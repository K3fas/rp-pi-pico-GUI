#pragma once

#include <cstdint>
#include <cstring>
#include <utility>

namespace rpgui::common
{
    struct SpriteData
    {
        uint8_t *image;
        const int16_t size;
        const int16_t width;
        const int16_t height;
        const int16_t pitch;

        // Rule of 5
        SpriteData() : image(nullptr), size(0), width(0), height(0), pitch(0) {}
        SpriteData(const SpriteData &s) : image(s.image), size(s.size), width(s.width), height(s.height), pitch(s.pitch) {}

        SpriteData(SpriteData &&s) noexcept : image(std::exchange(s.image, nullptr)),
                                                size(s.size),
                                                width(s.width),
                                                height(s.height),
                                                pitch(s.pitch)
        {
        }
        ~SpriteData() = default;

        SpriteData(uint8_t *img, const int16_t size, const int16_t width, const int16_t height, const int16_t pitch)
            : image(img), size(size), width(width), height(height), pitch(pitch) {}

        // Copy assignment
        SpriteData &operator=(const SpriteData &rhs)
        {
            if (this == &rhs)
                return *this;

            image = rhs.image;
            const_cast<int16_t &>(size) = rhs.size;
            const_cast<int16_t &>(width) = rhs.width;
            const_cast<int16_t &>(height) = rhs.height;
            const_cast<int16_t &>(pitch) = rhs.pitch;

            return *this;
        }
        // Move assignment
        SpriteData &operator=(SpriteData &&rhs) noexcept
        {
            if (this == &rhs)
                return *this;

            delete[] image;
            image = std::exchange(rhs.image, nullptr);
            const_cast<int16_t &>(size) = rhs.size;
            const_cast<int16_t &>(width) = rhs.width;
            const_cast<int16_t &>(height) = rhs.height;
            const_cast<int16_t &>(pitch) = rhs.pitch;

            return *this;
        }
    };
} // namespace rpgui::type
