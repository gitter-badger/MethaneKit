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

FILE: Methane/Graphics/Metal/DescriptorHeapMT.mm
Metal "dummy" implementation of the descriptor heap.

******************************************************************************/

#include "DescriptorHeapMT.h"

#include <Methane/Graphics/Instrumentation.h>

using namespace Methane::Graphics;

DescriptorHeap::Ptr DescriptorHeap::Create(ContextBase& context, const Settings& settings)
{
    ITT_FUNCTION_TASK();
    return std::make_shared<DescriptorHeapMT>(context, settings);
}

DescriptorHeapMT::DescriptorHeapMT(ContextBase& context, const Settings& settings)
    : DescriptorHeap(context, settings)
{
    ITT_FUNCTION_TASK();
}

DescriptorHeapMT::~DescriptorHeapMT()
{
    ITT_FUNCTION_TASK();
}
