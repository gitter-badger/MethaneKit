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

FILE: Methane/Graphics/ResourceBase.cpp
Base implementation of the resource interface.

******************************************************************************/

#include "ResourceBase.h"
#include "TextureBase.h"
#include "ContextBase.h"
#include "Instrumentation.h"

#include <cassert>
#include <sstream>

using namespace Methane::Graphics;

const Resource::Usage::Values Resource::Usage::values;

std::string Resource::GetTypeName(Type type) noexcept
{
    ITT_FUNCTION_TASK();
    switch (type)
    {
    case Resource::Type::Buffer:  return "Buffer";
    case Resource::Type::Texture: return "Texture";
    case Resource::Type::Sampler: return "Sampler";
    default:                      assert(0);
    }
    return "Unknown";
}

std::string Resource::GetUsageName(Usage::Value usage) noexcept
{
    ITT_FUNCTION_TASK();
    switch (usage)
    {
    case Resource::Usage::ShaderRead:   return "Shader Read";
    case Resource::Usage::ShaderWrite:  return "Shader Write";
    case Resource::Usage::RenderTarget: return "Render Target";
    default:                            assert(0);
    }
    return "Unknown";
}

std::string Resource::GetUsageNames(Usage::Mask usage_mask) noexcept
{
    ITT_FUNCTION_TASK();

    std::stringstream names_ss;
    bool first_usage = true;

    for (Usage::Value usage : Usage::values)
    {
        if (!(usage & usage_mask))
            continue;

        if (!first_usage)
        {
            names_ss << ", ";
        }

        names_ss << GetUsageName(usage);
        first_usage = false;
    }

    return names_ss.str();
}

ResourceBase::ResourceBase(Type type, Usage::Mask usage_mask, ContextBase& context, const DescriptorByUsage& descriptor_by_usage)
    : m_type(type)
    , m_usage_mask(usage_mask)
    , m_context(context)
    , m_descriptor_by_usage(descriptor_by_usage)
{
    ITT_FUNCTION_TASK();

    for (auto& usage_and_descriptor : m_descriptor_by_usage)
    {
        if (usage_and_descriptor.second.index >= 0)
        {
            usage_and_descriptor.second.heap.ReplaceResource(*this, usage_and_descriptor.second.index);
        }
        else
        {
            usage_and_descriptor.second.index = usage_and_descriptor.second.heap.AddResource(*this);
        }
    }
}

ResourceBase::~ResourceBase()
{
    ITT_FUNCTION_TASK();

    for (const auto& usage_and_descriptor : m_descriptor_by_usage)
    {
        if (usage_and_descriptor.second.index >= 0)
        {
            usage_and_descriptor.second.heap.RemoveResource(usage_and_descriptor.second.index);
        }
    }
}

void ResourceBase::InitializeDefaultDescriptors()
{
    ITT_FUNCTION_TASK();

    for (Usage::Value usage : Usage::values)
    {
        if (!(m_usage_mask & usage))
            continue;

        auto descriptor_by_usage_it = m_descriptor_by_usage.find(usage);
        if (descriptor_by_usage_it == m_descriptor_by_usage.end())
        {
            // Create deafult resource descriptor by usage
            const DescriptorHeap::Type heap_type = GetDescriptorHeapTypeByUsage(usage);
            Descriptor descriptor(m_context.GetResourceManager().GetDescriptorHeap(heap_type));
            descriptor.index = descriptor.heap.AddResource(*this);
            m_descriptor_by_usage.emplace(usage, descriptor);
        }
    }
}

const Resource::Descriptor& ResourceBase::GetDescriptor(Usage::Value usage) const
{
    ITT_FUNCTION_TASK();

    auto descriptor_by_usage_it = m_descriptor_by_usage.find(usage);
    if (descriptor_by_usage_it == m_descriptor_by_usage.end())
    {
        throw std::runtime_error("Resource \"" + GetName() + "\" does not support \"" + GetUsageName(usage) + "\" usage");
    }
    return descriptor_by_usage_it->second;
}

DescriptorHeap::Type ResourceBase::GetDescriptorHeapTypeByUsage(ResourceBase::Usage::Value resource_usage) const
{
    ITT_FUNCTION_TASK();

    switch (resource_usage)
    {
    case Resource::Usage::ShaderRead:
    {
        return (m_type == Type::Sampler)
                ? DescriptorHeap::Type::Samplers
                : DescriptorHeap::Type::ShaderResources;
    }
    case Resource::Usage::ShaderWrite:
    case Resource::Usage::RenderTarget:
        return (m_type == Type::Texture && static_cast<const TextureBase&>(*this).GetSettings().type == Texture::Type::DepthStencilBuffer)
                ? DescriptorHeap::Type::DepthStencil
                : DescriptorHeap::Type::RenderTargets;
    case Resource::Usage::Unknown:
        return DescriptorHeap::Type::Undefined;
    default:
        throw std::runtime_error("Resource usage value (" + std::to_string(static_cast<uint32_t>(resource_usage)) + ") does not map to descriptor heap.");
    }
}

const Resource::Descriptor& ResourceBase::GetDescriptorByUsage(Usage::Value usage) const
{
    ITT_FUNCTION_TASK();

    auto descriptor_by_usage_it = m_descriptor_by_usage.find(usage);
    if (descriptor_by_usage_it == m_descriptor_by_usage.end())
    {
        throw std::runtime_error("Resource \"" + GetName() + "\" does not have descriptor for usage \"" + GetUsageName(usage) + "\"");
    }

    return descriptor_by_usage_it->second;
}

DescriptorHeap::Types ResourceBase::GetUsedDescriptorHeapTypes() const noexcept
{
    ITT_FUNCTION_TASK();

    DescriptorHeap::Types heap_types;
    for (auto usage_and_descriptor : m_descriptor_by_usage)
    {
        heap_types.insert(usage_and_descriptor.second.heap.GetSettings().type);
    }
    return heap_types;
}

void ResourceBase::SetState(State state, Barriers& out_barriers)
{
    ITT_FUNCTION_TASK();

    if (m_state == state)
        return;

    if (m_state != State::Common)
    {
        assert(state != State::Common);
        out_barriers.emplace_back(Barrier{ Barrier::Type::Transition, *this, m_state, state });
    }

    m_state = state;
}
