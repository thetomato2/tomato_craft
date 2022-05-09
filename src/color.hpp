#pragma once
#ifndef COLOR_HPP_
#define COLOR_HPP_
#include "core.hpp"

namespace tom
{
struct color_argb
{
    union
    {
        u32 argb;
        struct
        {
            u8 b;
            u8 g;
            u8 r;
            u8 a;
        };
    };
};

namespace colors
{
// note: argb
global_var constexpr color_argb red   = { 0xff'ff'00'00 };
global_var constexpr color_argb green = { 0xff'00'ff'00 };
global_var constexpr color_argb blue  = { 0xff'00'00'ff };
global_var constexpr color_argb pink  = { 0xff'ff'00'ff };
global_var constexpr color_argb black = { 0xff'ff'ff'ff };
}  // namespace colors
}  // namespace tom

#endif  // COLOR_HPP_

