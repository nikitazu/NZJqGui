#pragma once

#include <string>
#include <Windows.h>

#include "NZ_Pipe.h"

class NZ_JqProcess
{
public:
    static std::string run(std::string json, std::string query)
    {
        //char exe_path[MAX_PATH];
        //GetModuleFileNameA(nullptr, exe_path, MAX_PATH);

        SECURITY_ATTRIBUTES security_attr;

        security_attr.nLength = sizeof(SECURITY_ATTRIBUTES);
        security_attr.bInheritHandle = true;
        security_attr.lpSecurityDescriptor = nullptr;

        NZ_Pipe child_out(&security_attr);

        if (!child_out.is_ok()) {
            return "[ERR] Failed to create <output> pipe";
        }

        if (!child_out.set_read_no_inherit()) {
            return "[ERR] Failed to set <output> pipe read end to NO INHERIT";
        }

        NZ_Pipe child_in(&security_attr);

        if (!child_in.is_ok()) {
            return "[ERR] Failed to create <input> pipe";
        }

        if (!child_in.set_write_no_inherit()) {
            return "[ERR] Failed to set <input> pipe write end to NO INHERIT";
        }

        STARTUPINFOW startup_info;
        ZeroMemory(&startup_info, sizeof(startup_info));
        startup_info.cb = sizeof(startup_info);
        startup_info.dwFlags |= STARTF_USESTDHANDLES;
        child_out.connect_stderr(startup_info);
        child_out.connect_stdout(startup_info);
        child_in.connect_stdin(startup_info);

        PROCESS_INFORMATION process_info;
        ZeroMemory(&process_info, sizeof(process_info));

        std::wstring query_w = std::wstring(query.begin(), query.end());
        std::wstring jq_exe_path = L".\\jq-windows-i386.exe";
        std::wstring cli_args = jq_exe_path + L" \"" + query_w + L"\"";

        bool success = CreateProcessW(
            jq_exe_path.c_str(),
            cli_args.data(),
            nullptr,
            nullptr,
            true,
            CREATE_NO_WINDOW, // https://learn.microsoft.com/en-us/windows/win32/procthread/process-creation-flags
            nullptr,
            nullptr,
            &startup_info,
            &process_info
        );

        std::string result;

        if (success) {
            bool json_ok = child_in.write_string(json);

            child_in.close();

            if (!json_ok) {
                result = "[ERR] Failed to write to process <input> pipe";
            }
            else {
                if (!child_out.read_string(result)) {
                    result = "[ERR] Failed to read from process <output> pipe";
                }
            }

            CloseHandle(process_info.hProcess);
            CloseHandle(process_info.hThread);
        }
        else {
            result = "[ERR] Failed to run the process!";
        }

        return result;
    }
};
