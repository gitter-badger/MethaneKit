/******************************************************************************

Copyright 2019 Evgeny Gorodetskiy

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*******************************************************************************

FILE: Methane/Graphics/Types.h
Methane primitive graphics types.

******************************************************************************/

#pragma once

#include <Methane/Data/Types.h>
#include <Methane/Graphics/MathTypes.h>

#include <cstdint>

namespace Methane
{
namespace Graphics
{

template<typename T>
using Point2T = Data::Point2T<T>;

using Point2i = Point2T<int32_t>;
using Point2u = Point2T<uint32_t>;
using Point2f = Point2T<float>;
using Point2d = Point2T<double>;

template<typename T, typename D>
using Rect = Data::Rect<T, D>;

using FrameRect    = Data::FrameRect;
using FrameSize    = Data::FrameSize;
using ScissorRect  = Rect<uint32_t, uint32_t>;
using ScissorRects = std::vector<ScissorRect>;
    
ScissorRect GetFrameScissorRect(const FrameSize& frame_size);

template<typename T>
class Point3T : public cml::vector<T, cml::fixed<3>>
{
public:
    Point3T() = default;
    Point3T(T x, T y, T z) : cml::vector<T, cml::fixed<3>>(x, y, z) { }
    
    T x() const noexcept { return (*this)[0]; }
    T y() const noexcept { return (*this)[1]; }
    T z() const noexcept { return (*this)[2]; }
    
    void setX(T x) noexcept { (*this)[0] = x; }
    void setY(T y) noexcept { (*this)[1] = y; }
    void setZ(T z) noexcept { (*this)[2] = z; }
};

using Point3i = Point3T<int32_t>;
using Point3u = Point3T<uint32_t>;
using Point3f = Point3T<float>;
using Point3d = Point3T<double>;

template<typename T, typename D>
struct Volume
{
    struct Size : Rect<T, D>::Size
    {
        D depth = 1;
        
        Size() = default;
        Size(const typename Rect<T, D>::Size& rect_size, D d = 1) : Rect<T, D>::Size(rect_size), depth(d) { }
        Size(D w, D h, D d = 1) : Rect<T, D>::Size(w, h), depth(d) { }
        
        bool operator==(const Size& other) const
        { return Rect<T, D>::Size::operator==(other) && depth == other.depth; }

        D GetPixelsCount() const noexcept { return depth * Rect<T, D>::Size::GetPixelsCount(); }
    };

    using Point = Point3T<T>;

    Point origin;
    Size  size;
};

using Dimensions = Volume<int32_t, uint32_t>::Size;

using Viewport  = Volume<double, double>;
using Viewports = std::vector<Viewport>;

Viewport GetFrameViewport(const FrameSize& frame_size);

class Color : public Vector4f
{
public:
    Color() : Vector4f() {}
    Color(float r, float g, float b, float a) : Vector4f(r, g, b, a) { }
    
    float r() const noexcept { return (*this)[0]; }
    float g() const noexcept { return (*this)[1]; }
    float b() const noexcept { return (*this)[2]; }
    float a() const noexcept { return (*this)[3]; }
    
    void setR(float r) noexcept { (*this)[0] = r; }
    void setG(float g) noexcept { (*this)[1] = g; }
    void setB(float b) noexcept { (*this)[2] = b; }
    void setA(float a) noexcept { (*this)[3] = a; }
};

using Depth = float;
using Stencil = uint8_t;

enum class PixelFormat
{
    Unknown,
    RGBA8,
    RGBA8Unorm,
    BGRA8Unorm,
    R32Float,
    R32Uint,
    R32Sint,
    R16Uint,
    Depth32Float
};

uint32_t GetPixelSize(PixelFormat data_format) noexcept;

enum class Compare : uint32_t
{
    Never = 0,
    Always,
    Less,
    Greater,
    LessEqual,
    GreaterEqual,
    Equal,
    NotEqual,
};

} // namespace Graphics
} // namespace Methane
