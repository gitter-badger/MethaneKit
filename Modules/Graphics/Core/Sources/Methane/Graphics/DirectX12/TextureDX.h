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

FILE: Methane/Graphics/DirectX12/TextureDX.h
DirectX 12 implementation of the texture interface.

******************************************************************************/

#pragma once

#include <Methane/Graphics/TextureBase.h>
#include <Methane/Graphics/CommandListBase.h>
#include <Methane/Graphics/Windows/Helpers.h>

#include <d3dx12.h>
#include <cassert>

namespace Methane
{
namespace Graphics
{

template<typename... ExtraArgs>
class TextureDX : public TextureBase
{
public:
    TextureDX(ContextBase& context, const Settings& settings, const DescriptorByUsage& descriptor_by_usage, ExtraArgs... extra_args)
        : TextureBase(context, settings, descriptor_by_usage)
    {
        InitializeDefaultDescriptors();
        Initialize(extra_args...);
    }

    virtual ~TextureDX() override = default;

    // Resource interface
    virtual void SetData(Data::ConstRawPtr p_data, Data::Size data_size) override
    {
        throw std::logic_error("Setting texture data is allowed for image textures only.");
    }

    virtual Data::Size GetDataSize() const override
    {
        return m_settings.dimensions.GetPixelsCount() * GetPixelSize(m_settings.pixel_format);
    }

protected:
    void Initialize(ExtraArgs...);
};

struct ImageTextureArg { };

template<>
class TextureDX<ImageTextureArg> : public TextureBase
{
public:
    TextureDX(ContextBase& context, const Settings& settings, const DescriptorByUsage& descriptor_by_usage, ImageTextureArg);

    // Resource interface
    virtual void SetData(Data::ConstRawPtr p_data, Data::Size data_size) override;
    virtual Data::Size GetDataSize() const override { return m_data_size; }

protected:
    Data::Size                    m_data_size = 0;
    wrl::ComPtr<ID3D12Resource> m_cp_upload_resource;
};

using RenderTargetTextureDX         = TextureDX<>;
using FrameBufferTextureDX          = TextureDX<uint32_t /* frame_buffer_index */>;
using DepthStencilBufferTextureDX   = TextureDX<Depth /*depth_clear_value*/, Stencil /*stencil_clear_value*/>;
using ImageTextureDX                = TextureDX<ImageTextureArg>;

} // namespace Graphics
} // namespace Methane
