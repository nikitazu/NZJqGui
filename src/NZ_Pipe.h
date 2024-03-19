#pragma once

#include <string>
#include <Windows.h>

class NZ_Pipe
{
private:
    bool ok = false;
    HANDLE read_handle = nullptr;
    HANDLE write_handle = nullptr;

public:
    NZ_Pipe(LPSECURITY_ATTRIBUTES security_attr_p)
    {
        ok = CreatePipe(&read_handle, &write_handle, security_attr_p, 0);
    }

    ~NZ_Pipe()
    {
        close();
    }

    bool is_ok() const
    {
        return ok;
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

    void connect_stderr(STARTUPINFOW& startup_info) const
    {
        startup_info.hStdError = write_handle;
    }

    void connect_stdout(STARTUPINFOW& startup_info) const
    {
        startup_info.hStdOutput = write_handle;
    }

    void connect_stdin(STARTUPINFOW& startup_info) const
    {
        startup_info.hStdInput = read_handle;
    }

    bool set_read_no_inherit() const
    {
        return SetHandleInformation(read_handle, HANDLE_FLAG_INHERIT, 0);
    }

    bool set_write_no_inherit() const
    {
        return SetHandleInformation(write_handle, HANDLE_FLAG_INHERIT, 0);
    }

    bool write_string(std::string& str) const
    {
        DWORD bytes_written = 0;
        bool ok = WriteFile(write_handle, str.c_str(), str.size(), &bytes_written, nullptr);
        return ok && bytes_written > 0;
    }

    bool read_string(std::string& result) const
    {
        DWORD bytes_read = 0;
        char ch_buffer[BUFSIZ]{};
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
