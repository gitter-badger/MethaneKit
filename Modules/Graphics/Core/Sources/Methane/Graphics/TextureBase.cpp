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

FILE: Methane/Graphics/TextureBase.cpp
Base implementation of the texture interface.

******************************************************************************/

#include "TextureBase.h"
#include "DescriptorHeap.h"
#include "ContextBase.h"
#include "Instrumentation.h"

#include <cassert>

using namespace Methane::Graphics;

Texture::Settings Texture::Settings::Image(const Dimensions& dimensions, PixelFormat pixel_format, bool mipmapped, TextureBase::Usage::Mask usage)
{
    ITT_FUNCTION_TASK();

    Settings settings       = { };
    settings.type           = Type::Texture;
    settings.dimension_type = dimensions.depth > 1 ? DimensionType::Tex3D : DimensionType::Tex2D;
    settings.usage_mask     = usage;
    settings.pixel_format   = pixel_format;
    settings.dimensions     = dimensions;
    settings.mipmapped      = mipmapped;
    settings.cpu_accessible = true;
    return settings;
}

Texture::Settings Texture::Settings::FrameBuffer(const Dimensions& dimensions, PixelFormat pixel_format)
{
    ITT_FUNCTION_TASK();

    Settings settings       = { };
    settings.type           = Type::FrameBuffer;
    settings.dimension_type = DimensionType::Tex2D;
    settings.usage_mask     = Usage::RenderTarget;
    settings.pixel_format   = pixel_format;
    settings.dimensions     = dimensions;
    settings.cpu_accessible = false;
    return settings;
}

Texture::Settings Texture::Settings::DepthStencilBuffer(const Dimensions& dimensions, PixelFormat pixel_format, Usage::Mask usage_mask)
{
    ITT_FUNCTION_TASK();

    Settings settings       = {};
    settings.type           = Type::DepthStencilBuffer;
    settings.dimension_type = DimensionType::Tex2D;
    settings.usage_mask     = usage_mask;
    settings.pixel_format   = pixel_format;
    settings.dimensions     = dimensions;
    settings.cpu_accessible = false;
    return settings;
}

TextureBase::TextureBase(ContextBase& context, const Settings& settings, const DescriptorByUsage& descriptor_by_usage)
    : ResourceNT(Resource::Type::Texture, settings.usage_mask, context, descriptor_by_usage)
    , m_settings(settings)
{
    ITT_FUNCTION_TASK();

    if (m_settings.usage_mask == TextureBase::Usage::Unknown)
    {
        throw std::invalid_argument("Can not create texture with \"Unknown\" usage mask.");
    }
    if (m_settings.pixel_format == PixelFormat::Unknown)
    {
        throw std::invalid_argument("Can not create texture with \"Unknown\" pixel format.");
    }
    if (m_settings.dimensions == Dimensions(0, 0, 0))
    {
        throw std::invalid_argument("Can not create texture with all zero dimensions.");
    }
}
