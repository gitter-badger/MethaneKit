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

FILE: Methane/Graphics/Texture.h
Methane graphics interface: graphics texture.

******************************************************************************/

#pragma once

#include "Resource.h"

#include <string>

namespace Methane
{
namespace Graphics
{

struct Texture : virtual Resource
{
    using Ptr     = std::shared_ptr<Texture>;
    using WeakPtr = std::weak_ptr<Texture>;

    enum class Type : uint32_t
    {
        Texture = 0,
        FrameBuffer,
        DepthStencilBuffer,
    };

    enum class DimensionType : uint32_t
    {
        Tex1D = 0,
        Tex1DArray,
        Tex2D,
        Tex2DArray,
        Tex2DMultisample,
        Cube,
        CubeArray,
        Tex3D,
    };

    struct Settings
    {
        Type           type;
        DimensionType  dimension_type;
        Usage::Mask    usage_mask;
        PixelFormat    pixel_format;
        Dimensions     dimensions;
        bool           mipmapped;
        bool           cpu_accessible;

        static Settings Image(const Dimensions& dimensions, PixelFormat pixel_format, bool mipmapped, Usage::Mask usage = Usage::Unknown);
        static Settings FrameBuffer(const Dimensions& dimensions, PixelFormat pixel_format);
        static Settings DepthStencilBuffer(const Dimensions& dimensions, PixelFormat pixel_format, Usage::Mask usage_mask = Usage::RenderTarget);
    };

    // Create Texture instance
    static Ptr CreateRenderTarget(Context& context, const Settings& settings, const DescriptorByUsage& descriptor_by_usage = DescriptorByUsage());
    static Ptr CreateFrameBuffer(Context& context, uint32_t frame_buffer_index, const DescriptorByUsage& descriptor_by_usage = DescriptorByUsage());
    static Ptr CreateDepthStencilBuffer(Context& context, const DescriptorByUsage& descriptor_by_usage = DescriptorByUsage());
    static Ptr CreateImage(Context& context, Dimensions dimensions, PixelFormat pixel_format, bool mipmapped, const DescriptorByUsage& descriptor_by_usage = DescriptorByUsage());

    // Texture interface
    virtual const Settings& GetSettings() const = 0;

    virtual ~Texture() override = default;
};

} // namespace Graphics
} // namespace Methane
