#pragma once

template<typename Type, typename Store> 
struct AutomaticID { 
    Store v; 
    AutomaticID(); 
    AutomaticID(Store v) : v(v) {} 
    Store value() const; 
    bool operator!=(AutomaticID const &) const; 
    bool operator==(AutomaticID const &) const; 
    operator Store() const { return v; } 
    static Store _makeRuntimeID(); 
}; 


class ActorUniqueID {
public:
    long long id;
    ActorUniqueID(long long id) : id(id) {
    }

    operator long long() const {
        return this->id;
    }

    long long getId(){
        return id;
    }
};

