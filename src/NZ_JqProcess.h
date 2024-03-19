#pragma once

#include <string>
#include <Windows.h>

struct NZ_Pipe
{
    bool ok = false;
    HANDLE read_handle = nullptr;
    HANDLE write_handle = nullptr;

    NZ_Pipe(LPSECURITY_ATTRIBUTES security_attr_p)
    {
        ok = CreatePipe(&read_handle, &write_handle, security_attr_p, 0);
    }

    ~NZ_Pipe()
    {
        close();
    }

    void close()
    {
        if (write_handle != nullptr) {
            CloseHandle(write_handle);
            write_handle = nullptr;
        }

        if (read_handle != nullptr) {
            CloseHandle(read_handle);
            read_handle = nullptr;
        }
    }

    bool set_read_no_inherit()
    {
        return SetHandleInformation(read_handle, HANDLE_FLAG_INHERIT, 0);
    }

    bool set_write_no_inherit()
    {
        return SetHandleInformation(write_handle, HANDLE_FLAG_INHERIT, 0);
    }

    bool write_string(std::string& str)
    {
        DWORD bytes_written = 0;
        bool ok = WriteFile(write_handle, str.c_str(), str.size(), &bytes_written, nullptr);
        return ok && bytes_written > 0;
    }

    bool read_string(std::string& result)
    {
        DWORD bytes_read = 0;
        char ch_buffer[BUFSIZ];
        bool ok = false;

        do {
            ok = ReadFile(read_handle, ch_buffer, BUFSIZ, &bytes_read, nullptr);

            if (ok) {
                result.append(ch_buffer, bytes_read);
            }
        } while (ok && bytes_read == BUFSIZ);

        return ok;
    }
};

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

        if (!child_out.ok) {
            return "[ERR] Failed to create <output> pipe";
        }

        if (!child_out.set_read_no_inherit()) {
            return "[ERR] Failed to set <output> pipe read end to NO INHERIT";
        }

        NZ_Pipe child_in(&security_attr);

        if (!child_in.ok) {
            return "[ERR] Failed to create <input> pipe";
        }

        if (!child_in.set_write_no_inherit()) {
            return "[ERR] Failed to set <input> pipe write end to NO INHERIT";
        }

        STARTUPINFOW startup_info;
        ZeroMemory(&startup_info, sizeof(startup_info));
        startup_info.cb = sizeof(startup_info);
        startup_info.hStdError = child_out.write_handle;
        startup_info.hStdOutput = child_out.write_handle;
        startup_info.hStdInput = child_in.read_handle;
        startup_info.dwFlags |= STARTF_USESTDHANDLES;

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
