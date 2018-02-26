//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#pragma once

namespace Helpers
{
    // Console helpers
    std::wstring GetUserInput(DWORD promptMsg, DWORD maxCharacters);

    // Output Helpers
    HRESULT FormatMessage(DWORD messageId, std::wstring* message, ...);
    HRESULT PrintErrorMessage(HRESULT hr);
    HRESULT PrintMessage(DWORD messageId, ...);
    void PromptForInput();
}