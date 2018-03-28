//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//

#pragma once

namespace DistributionInfo
{
    // The name of the distribution. This will be displayed to the user via
    // wslconfig.exe and in other places. This value must not change between
    // versions, otherwise users upgrading from older versions will see launch
    // failures.
    //
    // It must only conform to the following regular expression: ^[a-zA-Z0-9._-]+$
    const std::wstring Name = L"MyDistribution";

    // The title bar for the console window while the distrubiton is installing.
    const std::wstring WindowTitle = L"My Distribution";
}