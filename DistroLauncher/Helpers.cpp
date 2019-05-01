//
//    Copyright (C) Microsoft.  All rights reserved.
// Licensed under the terms described in the LICENSE file in the root of this project.
//

#include "stdafx.h"

namespace {
	HRESULT FormatMessageHelperVa(DWORD messageId, va_list vaList, std::wstring* message);
	HRESULT PrintMessageVa(DWORD messageId, va_list vaList);
}

std::wstring Helpers::GetUserInput(DWORD promptMsg, DWORD maxCharacters)
{
	Helpers::PrintMessage(promptMsg);
	const auto bufferSize = 1 + static_cast<size_t>(maxCharacters);
	std::unique_ptr<wchar_t[]> inputBuffer(new wchar_t[bufferSize]);
	std::wstring input;
	if (wscanf_s(L"%s", inputBuffer.get(), static_cast<unsigned int>(bufferSize)) == 1) {
		input = inputBuffer.get();
	}

	// Throw away any additional chracters that did not fit in the buffer.
	wchar_t wch;
	do {
		wch = getwchar();

	} while ((wch != L'\n') && (wch != WEOF));

	return input;
}

void Helpers::PrintErrorMessage(HRESULT error)
{
	PWSTR buffer = nullptr;
	::FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		nullptr,
		error,
		0x0409, //EN_US,
		reinterpret_cast<PWSTR>(&buffer),
		0,
		nullptr);

	PrintMessage(MSG_ERROR_CODE, error, buffer);
	if (buffer != nullptr) {
		HeapFree(GetProcessHeap(), 0, buffer);
	}
}

HRESULT Helpers::PrintMessage(DWORD messageId, ...)
{
	va_list argList;
	va_start(argList, messageId);
	const auto hr = PrintMessageVa(messageId, argList);
	va_end(argList);
	return hr;
}

void Helpers::PromptForInput()
{
	PrintMessage(MSG_PRESS_A_KEY);
	while (!_kbhit()) {};
}

DWORD Helpers::GetExePath(LPWSTR lpstr, DWORD nSize)
{
	auto _nSize = GetModuleFileName(nullptr, lpstr, nSize) - 1;
	if (_nSize != 0) while (_nSize-- > 0) if (lpstr[_nSize] == '\\')
	{
		lpstr[++_nSize] = 0;
		break;
	}
	return _nSize + 1;
}

//HRESULT Helpers::RunScript(const WslApiLoader* lpWslApi, LPSTR lpstr, DWORD* exitCode)
//{
//	// Create a pipe to write the input of the launched process.
//	HANDLE readPipe, writePipe;
//	DWORD _exitCode;
//	auto hr = S_OK;
//	*exitCode = 0;
//	SECURITY_ATTRIBUTES sa{ sizeof sa, nullptr, true };
//	if (CreatePipe(&readPipe, &writePipe, &sa, 0)) 
//	{
//		HANDLE child;
//		auto result = false;
//		auto hr = lpWslApi->WslLaunch(L"/bin/cat > /tmp/tmp_script.sh", true, readPipe, GetStdHandle(STD_OUTPUT_HANDLE), GetStdHandle(STD_ERROR_HANDLE), &child);
//		if (SUCCEEDED(hr)) {
//			DWORD bytesWrite;
//			while(*lpstr != '\0') if (!(result = WriteFile(writePipe, lpstr++, sizeof CHAR, &bytesWrite, nullptr))) break;
//
//			WaitForSingleObject(child, INFINITE);
//			result = result && GetExitCodeProcess(child, &_exitCode);
//			if (!result) hr = HRESULT_FROM_WIN32(GetLastError());
//		}
//		CloseHandle(child);
//	}
//	CloseHandle(writePipe);
//	CloseHandle(readPipe);
//
//	if (SUCCEEDED(hr)) hr = lpWslApi->WslLaunchInteractive(L"/bin/bash /tmp/tmp_script.sh", true, exitCode);
//	if (SUCCEEDED(hr)) hr = lpWslApi->WslLaunchInteractive(L"/bin/rm -rf /tmp/tmp_script.sh", true, &_exitCode);
//	return hr;
//}
HRESULT Helpers::RunScript(const WslApiLoader * lpWslApi, LPWSTR lpScriptPath, DWORD * exitCode)
{
	auto hr = S_OK;
	WCHAR exePath[MAX_PATH];
	LPWSTR oldCurrentDirectory = nullptr;
	auto result = GetExePath(exePath, MAX_PATH) != 0;

	DWORD length = 0;
	if (result) result = (length = GetCurrentDirectory(0, nullptr)) != 0;
	if (result) {
		oldCurrentDirectory = static_cast<LPWSTR>(malloc(sizeof WCHAR * (length + 1)));
		if (oldCurrentDirectory == nullptr) return HRESULT_FROM_WIN32(ERROR_OUTOFMEMORY);
		result = GetCurrentDirectory(length + 1, oldCurrentDirectory) != 0;
	}
	if (result) result = SetCurrentDirectory(exePath);

	if (result) {
		std::wstring command = L"/bin/bash ";
		command += lpScriptPath;
		hr = lpWslApi->WslLaunchInteractive(command.c_str(), true, exitCode);
		result = SetCurrentDirectory(oldCurrentDirectory);
	}
	if (SUCCEEDED(hr) && !result) hr = HRESULT_FROM_WIN32(GetLastError());
	if (oldCurrentDirectory) free(oldCurrentDirectory);
	return hr;
}

namespace {
	HRESULT FormatMessageHelperVa(DWORD messageId, va_list vaList, std::wstring* message)
	{
		PWSTR buffer = nullptr;
		const auto written = ::FormatMessageW(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			nullptr,
			messageId,
			0x0409, //EN_US
			reinterpret_cast<PWSTR>(&buffer),
			10,
			&vaList);
		*message = buffer;
		if (buffer != nullptr) {
			HeapFree(GetProcessHeap(), 0, buffer);
		}

		return (written > 0) ? S_OK : HRESULT_FROM_WIN32(GetLastError());
	}

	HRESULT PrintMessageVa(DWORD messageId, va_list vaList)
	{
		std::wstring message;
		const auto hr = FormatMessageHelperVa(messageId, vaList, &message);
		if (SUCCEEDED(hr)) {
			wprintf(L"%ls", message.c_str());
		}

		return hr;
	}
}
