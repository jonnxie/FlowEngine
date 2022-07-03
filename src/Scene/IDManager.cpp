//
// Created by hasee on 2022/7/3.
//

#include "IDManager.h"
#include "config.h"
#include "Macro/Macro.h"

namespace Flow {
    IDManager &IDManager::get() {
        static IDManager manager;
        return manager;
    }

    IDManager::IDManager() {
        ids = std::list<uint64_t>();
    }

    uint64_t IDManager::generate() {
        GuardLock(lock);
        return ids.empty() ? count++ : ids.back();
    }

    void IDManager::free(uint64_t _id) {
        ids.push_back(_id);
    }
} // Flow