#include "util.h"

#include <fstream>
#include <streambuf>

std::string read_file(const std::string& name) {
    std::ifstream t(name);
    std::string result;

    t.seekg(0, std::ios::end);
    result.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    result.assign(std::istreambuf_iterator<char>{t}, std::istreambuf_iterator<char>{});
    return result;
}
