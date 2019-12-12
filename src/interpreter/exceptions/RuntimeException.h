#pragma once

#include <exception>
#include <string>

class RuntimeException : public std::exception {
public:
    explicit RuntimeException(std::string msg);

    const char* what() const noexcept override;
    const std::string& what_str() const noexcept;

private:
    std::string _msg;
};
