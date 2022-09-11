#include <core/DungeonUtility.h>
#include <core/JavaClass.h>
#include <java.h>
#include <innercore_callbacks.h>

std::map<std::string, DungeonUtility::StructurePool*> DungeonUtility::StructurePool::pools;
std::map<DungeonUtility::StructurePool*, DungeonUtility::LoadData*> DungeonUtility::StructurePool::loads;

DungeonUtility::StructurePool::StructurePool(){

}
void DungeonUtility::StructurePool::put(std::string name, DungeonUtility::StructureObject* structure){
    structures[name] = structure;
}
DungeonUtility::StructureObject* DungeonUtility::StructurePool::get(std::string name) const {
    return structures.find(name)->second;
}
void DungeonUtility::StructurePool::load(std::string text, std::string name, std::string type) {
    DungeonUtility::LoadData* load = new DungeonUtility::LoadData();
    load->text = text;
    load->name = name;
    load->type = type;
    DungeonUtility::StructurePool::loads[this] = load;
}

void DungeonUtility::StructurePool::loadRuntime(std::string text, std::string name, std::string type) {
    this->put(name, DungeonUtility::StructureParser::getParserByName(type)->read(text));
}

void DungeonUtility::StructurePool::registerPool(std::string name, StructurePool* pool){
    DungeonUtility::StructurePool::pools[name] = pool;
}

export(void, dungeonutility_struct_StructurePool_levelPreLoaded){
    auto it = DungeonUtility::StructurePool::loads.begin();
    while (it !=  DungeonUtility::StructurePool::loads.end()){
        DungeonUtility::LoadData* data = it->second;
        it->first->loadRuntime(data->text, data->name, data->type);
        it++;
    }
    
}

export(jlong, dungeonutility_struct_StructurePool_newStructurePool){
    return (jlong) new DungeonUtility::StructurePool();
}

export(void, dungeonutility_struct_StructurePool_registerStructurePool, jstring str, jlong pool){
    DungeonUtility::StructurePool::registerPool(JavaClass::toString(env, str), (DungeonUtility::StructurePool*) pool);
}

export(jlong, dungeonutility_struct_StructurePool_get, jlong ptr, jstring str){
    return (jlong) ((DungeonUtility::StructurePool*) ptr)->get(JavaClass::toString(env, str));
}

export(void, dungeonutility_struct_StructurePool_put, jlong ptr, jstring str, jlong stru){
    ((DungeonUtility::StructurePool*) ptr)->put(JavaClass::toString(env, str), (DungeonUtility::StructureObject*) stru);
}

export(void, dungeonutility_struct_StructurePool_load, jlong ptr, jstring text, jstring name, jstring type){
    ((DungeonUtility::StructurePool*) ptr)->load(JavaClass::toString(env, text), JavaClass::toString(env, name), JavaClass::toString(env, type));
}

export(void, dungeonutility_struct_StructurePool_loadRuntime, jlong ptr, jstring text, jstring name, jstring, jstring type){
    ((DungeonUtility::StructurePool*) ptr)->loadRuntime(JavaClass::toString(env, text), JavaClass::toString(env, name), JavaClass::toString(env, type));
}