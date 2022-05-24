#pragma once

#include <stl/string>
#define stl std::__ndk1

#include <unordered_map>

class ItemStack;

enum ContainerEnumName {
	Enchant = 21,
};

enum ContainerCategory {
    
};

class Container {
    public:

};

class SparseContainer : public Container {
    public:

};




class ContainerModel {
    public:

};
class ContainerController {
    public:
    ContainerModel* getContainerModel() const;
};  

class ContainerManagerController {
	public:
	ItemStack const& _getItem0(ContainerEnumName) const;
};

class EnchantingContainerManagerController : public ContainerManagerController {
	public:

};