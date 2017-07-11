//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//
#include "stdafx.h"


static const std::wstring VALID_USERNAME_CHARS = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_-";
static const size_t MAX_USERNAME_LENGTH = 32;

bool Helpers::IsValidUserName(const std::wstring& userName)
{
    if ((userName.size() == 0) || (userName.size() > MAX_USERNAME_LENGTH))
    {
        return false;
    }

    if (userName.back() == L'-')
    {
        return false;
    }

    // Ensure there are no illegal characters in the username.
    if (userName.find_first_not_of(VALID_USERNAME_CHARS.c_str()) != std::wstring::npos) {
        return false;
    }

    return true;
}
HRESULT _DoPromptAcceptance(const std::wstring& promptWord, const std::wstring& prompt)
{
    // Allocate one character more for null terminator.
    size_t promptWordSize = promptWord.size() + 1;
    std::unique_ptr<wchar_t[]> inputBuffer(new wchar_t[promptWordSize]);
    
    wprintf(L"%ls", prompt.c_str());

    size_t fieldsRead = wscanf_s(L"%s", inputBuffer.get(), (unsigned int)promptWordSize);
    if (fieldsRead == 1)
    {
        bool matches = (0 == _wcsicmp(inputBuffer.get(), promptWord.c_str()));
        if (matches)
        {
            return S_OK;
        }
    }
    return E_FAIL;
}

// Function Description:
// - Uses promptMsg to prompt the user to enter the text in promptWordMsg.
// Arguments:
// - promptWordMsg: the message ID of the propmt to display to the user
// - promptMsg: the message ID of the text response expected.
// Return Value:
// - S_OK if the user input the requested text, otherwise an HRESULT containing 
//      the error.
HRESULT Helpers::PromptAcceptance(DWORD promptWordMsg, DWORD promptMsg)
{
    std::wstring promptWord;
    std::wstring prompt;
    HRESULT hr = Helpers::FormatMessage(promptWordMsg, &promptWord);
    if (SUCCEEDED(hr))
    {
        hr = Helpers::FormatMessage(promptMsg, &prompt, promptWord.c_str());
        if (SUCCEEDED(hr))
        {
            hr = _DoPromptAcceptance(promptWord, prompt);
        }
    }

    return hr;
}

std::wstring Helpers::GetUserInput(DWORD promptMsg, size_t maxCharacters)
{
    assert(maxCharacters < SIZE_MAX);
    
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

HRESULT Helpers::PrintMessage(ULONG* const charactersPrinted, DWORD messageId, ...)
{
    va_list argList;
    va_start(argList, messageId);
    HRESULT hr = PrintMessageVa(charactersPrinted, messageId, argList);
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


