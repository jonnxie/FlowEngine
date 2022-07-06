//
// Created by hasee on 2022/7/3.
//

#ifndef FLOWENGINE_IDMANAGER_H
#define FLOWENGINE_IDMANAGER_H

#include <vector>
#include <cstdint>
#include <list>
#include <mutex>

namespace Flow {

    class IDManager {
    public:
        static IDManager& get();
        uint64_t generate();
        void free(uint64_t _id);
    private:
        IDManager();
        std::list<uint64_t> ids{};
        std::mutex lock;
        uint64_t count{};
    };



#define FlowID IDManager::get().generate()
} // Flow

#endif //FLOWENGINE_IDMANAGER_H
