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

FILE: Methane/Graphics/ProgramBase.h
Base implementation of the program interface.

******************************************************************************/

#pragma once

#include <Methane/Graphics/Program.h>

#include "ShaderBase.h"
#include "DescriptorHeap.h"

#include <memory>

namespace Methane
{
namespace Graphics
{

class ContextBase;
class CommandListBase;

class ProgramBase
    : public Program
    , public std::enable_shared_from_this<ProgramBase>
{
    friend class ShaderBase;

public:
    class ResourceBindingsBase
        : public ResourceBindings
        , public std::enable_shared_from_this<ResourceBindingsBase>
    {
    public:
        ResourceBindingsBase(const Program::Ptr& sp_program, const ResourceByArgument& resource_by_argument);
        ResourceBindingsBase(const ResourceBindingsBase& other_resource_bingings, const ResourceByArgument& replace_resource_by_argument);
        virtual ~ResourceBindingsBase() override;

        Ptr GetPtr()                            { return shared_from_this(); }
        const Arguments& GetArguments() const   { return m_arguments; }

        // ResourceBindings interface
        virtual const Shader::ResourceBinding::Ptr& Get(const Argument& shader_argument) const override;

        // ResourceBindingsBase interface
        virtual void CompleteInitialization() = 0;

        bool AllArgumentsAreBoundToResources(std::string& missing_args) const;

    protected:
        using DescriptorHeapReservationByType = std::map<DescriptorHeap::Type, DescriptorHeap::Reservation>;

        void ReserveDescriptorHeapRanges();
        void SetResourcesForArguments(const ResourceByArgument& resource_by_argument);
        void VerifyAllArgumentsAreBoundToResources();

        const Program::Ptr              m_sp_program;
        Arguments                       m_arguments;
        ResourceBindingByArgument       m_resource_binding_by_argument;
        DescriptorHeapReservationByType m_descriptor_heap_reservations_by_type;
    };

    ProgramBase(ContextBase& context, const Settings& settings);
    virtual ~ProgramBase() override;

    // Program interface
    virtual const Settings&      GetSettings() const override                       { return m_settings; }
    virtual void                 SetName(const std::string& name) override          { m_name = name; }
    virtual const std::string&   GetName() const override                           { return m_name; }
    virtual const Shader::Types& GetShaderTypes() const override                    { return m_shader_types; }
    virtual const Shader::Ptr&   GetShader(Shader::Type shader_type) const override { return m_shaders_by_type[static_cast<size_t>(shader_type)]; }

    bool         HasShader(Shader::Type shader_type) const  { return !!GetShader(shader_type); }
    ContextBase& GetContext()                               { return m_context; }
    Ptr          GetPtr()                                   { return shared_from_this(); }

protected:
    void InitResourceBindings(const std::set<std::string>& constant_argument_names);
    const DescriptorHeap::Range& ReserveConstantDescriptorRange(DescriptorHeap& heap, uint32_t range_length);

    Shader& GetShaderRef(Shader::Type shader_type);
    uint32_t GetInputBufferIndexByArgumentName(const std::string& argument_name) const;
    uint32_t GetInputBufferIndexByArgumentSemantic(const std::string& argument_semantic) const;

    using ShadersByType = std::array<Shader::Ptr, static_cast<size_t>(Shader::Type::Count)>;
    static ShadersByType CreateShadersByType(const Shaders& shaders);

    struct DescriptorHeapReservation
    {
        DescriptorHeap::Ref       heap;
        DescriptorHeap::Range range;
    };

    using DescriptorRangeByHeapType = std::map<DescriptorHeap::Type, DescriptorHeapReservation>;

    ContextBase&              m_context;
    const Settings            m_settings;
    const ShadersByType       m_shaders_by_type;
    const Shader::Types       m_shader_types;
    ResourceBindingByArgument m_resource_binding_by_argument;
    std::string               m_name;
    DescriptorRangeByHeapType m_constant_descriptor_range_by_heap_type;
};

} // namespace Graphics
} // namespace Methane
