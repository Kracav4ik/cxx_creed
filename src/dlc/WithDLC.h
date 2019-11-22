#pragma once

#include <memory>
#include <vector>

template <typename T>
class WithDLC {
public:
    using DLC = T;

    void add_dlc(std::shared_ptr<DLC> dlc) {
        _dlc_list.push_back(std::move(dlc));
    }

protected:
    std::vector<std::shared_ptr<DLC>> _dlc_list;
};

