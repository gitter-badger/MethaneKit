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

FILE: Methane/Platform/Windows/Utils.h
Windows platform utilitary functions.

******************************************************************************/

#pragma once

#include <string>
#include <vector>

namespace Methane
{
namespace Platform
{
namespace Windows
{

void GetDesktopResolution(uint32_t& width, uint32_t& height);

} // namespace Windows
} // namespace Platform
} // namespace Methane
