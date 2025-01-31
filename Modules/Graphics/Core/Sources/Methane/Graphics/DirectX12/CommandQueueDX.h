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

FILE: Methane/Graphics/DirectX12/CommandQueueDX.h
DirectX 12 implementation of the command queue interface.

******************************************************************************/

#pragma once

#include <Methane/Graphics/CommandQueueBase.h>

#include <wrl.h>
#include <d3d12.h>

namespace Methane
{
namespace Graphics
{

namespace wrl = Microsoft::WRL;

class ContextDX;
class RenderStateBase;

class CommandQueueDX final : public CommandQueueBase
{
public:
    CommandQueueDX(ContextBase& context);
    virtual ~CommandQueueDX() override = default;

    // CommandQueue interface
    virtual void Execute(const CommandList::Refs& command_lists) override;

    // Object interface
    virtual void SetName(const std::string& name) override;

    ContextDX& GetContextDX();

    wrl::ComPtr<ID3D12CommandQueue>& GetNativeCommandQueue()     { return m_cp_command_queue; }

protected:
    wrl::ComPtr<ID3D12CommandQueue> m_cp_command_queue;
};

} // namespace Graphics
} // namespace Methane
