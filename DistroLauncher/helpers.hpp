//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#pragma once

namespace Helpers
{
    // Console helpers
    HRESULT PromptAcceptance(DWORD promptWordMsg, DWORD promptMsg);
    std::wstring GetUserInput(DWORD promptMsg, size_t maxCharacters);

    // Output Helpers
    HRESULT FormatMessage(DWORD messageId, std::wstring* message, ...);
    HRESULT PrintMessage(ULONG* const charactersPrinted, DWORD messageId, ...);
    HRESULT PrintMessage(DWORD messageId, ...);

    // User Input Helpers
    bool IsValidUserName(const std::wstring& userName);

}