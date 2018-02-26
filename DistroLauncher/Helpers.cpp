//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#include "stdafx.h"

std::wstring Helpers::GetUserInput(DWORD promptMsg, DWORD maxCharacters)
{
    std::wstring prompt;
    Helpers::FormatMessage(promptMsg, &prompt);

    size_t bufferSize = maxCharacters + 1;
    std::unique_ptr<wchar_t[]> inputBuffer(new wchar_t[bufferSize]);
    wprintf(L"%ls", prompt.c_str());
    std::wstring input;
    if (wscanf_s(L"%s", inputBuffer.get(), (unsigned int)bufferSize) == 1) {
        input = inputBuffer.get();
    }

    // Throw away any additional chracters that did not fit in the buffer.
    wchar_t wch;
    do 
    {
        wch = getwchar();

    } while ((wch != L'\n') && (wch != WEOF));

    return input;
}

HRESULT FormatMessageHelperVa(DWORD messageId, va_list vaList, std::wstring* message)
{
    PWSTR buffer = nullptr; 
    DWORD written = FormatMessageW(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                                     NULL,
                                     messageId,
                                     0,
                                     (PWSTR)&buffer,
                                     10,
                                     &vaList);
    *message = buffer;
    HeapFree(GetProcessHeap(), 0, buffer);

    return written > 0? S_OK : HRESULT_FROM_WIN32(GetLastError());
}

HRESULT PrintMessageVa(ULONG* const charactersPrinted, DWORD messageId, va_list vaList)
{
    std::wstring message;
    HRESULT hr = FormatMessageHelperVa(messageId, vaList, &message);
    if (SUCCEEDED(hr))
    {
        unsigned long _charsPrinted = wprintf(L"%ls", message.c_str());
        if (charactersPrinted != nullptr)
        {
            *charactersPrinted = _charsPrinted;
        }
    }
    return hr;
}

HRESULT Helpers::FormatMessage(DWORD messageId, std::wstring* message, ...)
{
    va_list argList;
    va_start(argList, message);
    HRESULT hr = FormatMessageHelperVa(messageId, argList, message);
    va_end(argList);
    return hr;
}

HRESULT Helpers::PrintMessage(DWORD messageId, ...)
{
    va_list argList;
    va_start(argList, messageId);
    HRESULT hr = PrintMessageVa(nullptr, messageId, argList);
    va_end(argList);
    return hr;
}


