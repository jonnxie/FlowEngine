//
// Created by hasee on 2022/7/3.
//

#ifndef FLOWENGINE_COMPONENTS_H
#define FLOWENGINE_COMPONENTS_H

#include <utility>
#include "IDManager.h"

namespace Flow{

    struct ID{
        ID(){
            id = FlowID;
        };
        ID(uint64_t _id): id(_id){}
        ~ID(){
            IDManager::get().free(id);
        }
        operator uint64_t() const {return id;}
        uint64_t id;
    };

    struct Relation{
        uint64_t parentHandle = 0;
        std::vector<uint64_t> children;
        Default(Relation);
        Relation(const uint64_t& _parent) : parentHandle(_parent){}
    };

    struct Tag{
        std::string tag;
        Default(Tag);
        Tag(std::string  _tag) : tag(std::move(_tag)){}
        operator const std::string& () const {return tag;}
    };

    struct MultipleComponent{

    };
}

#endif //FLOWENGINE_COMPONENTS_H
