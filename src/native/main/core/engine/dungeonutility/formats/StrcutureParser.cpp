#include <core/DungeonUtility.h>
#include <core/JavaClass.h>
#include <java.h>
#include <innercore_callbacks.h>

std::map<std::string, DungeonUtility::StructureParser*> DungeonUtility::StructureParser::pasrsers;
jclass DungeonUtility::StructureJavaParser::parserClass;
jmethodID DungeonUtility::StructureJavaParser::readID, DungeonUtility::StructureJavaParser::saveID;

DungeonUtility::StructureParser::StructureParser(){

}

std::string DungeonUtility::StructureParser::save(DungeonUtility::StructureObject* object) const {
    return "";
}

DungeonUtility::StructureObject* DungeonUtility::StructureParser::read(std::string const& text) const {
    return nullptr;
}

void DungeonUtility::StructureParser::registerParser(std::string name, DungeonUtility::StructureParser* pasrser){
    pasrsers[name] = pasrser;
}

DungeonUtility::StructureParser* DungeonUtility::StructureParser::getParserByName(std::string name){
    return pasrsers[name];
}

bool DungeonUtility::StructureParser::canParser(std::string name){
    return pasrsers.find(name) != pasrsers.end();
}

DungeonUtility::StructureJavaParser::StructureJavaParser(jobject object){
    this->self = object;
}

std::string DungeonUtility::StructureJavaParser::save(DungeonUtility::StructureObject* object) const {
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        return JavaClass::toString(env, (jstring) env->CallObjectMethod(this->self, DungeonUtility::StructureJavaParser::saveID, (jlong) object));
    }
}

DungeonUtility::StructureObject* DungeonUtility::StructureJavaParser::read(std::string const& text) const {
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        return (DungeonUtility::StructureObject*) env->CallLongMethod(this->self, DungeonUtility::StructureJavaParser::readID, JavaClass::toString(env, text));
    }
}

export(jstring, dungeonutility_struct_StructureParser_save, jlong self, jlong structure){
    return JavaClass::toString(env, ((DungeonUtility::StructureParser*) self)->save((DungeonUtility::StructureObject*) structure));
}
export(jlong, dungeonutility_struct_StructureParser_read, jlong self, jstring structure){
    return (jlong) ((DungeonUtility::StructureParser*) self)->read(JavaClass::toString(env, structure));
}

export(void, dungeonutility_struct_StructureParser_registerFormat, jstring name, jobject parser){
    DungeonUtility::StructureParser::registerParser(JavaClass::toString(env, name), new DungeonUtility::StructureJavaParser(env->NewGlobalRef(parser)));
}
export(jboolean, dungeonutility_struct_StructureParser_canParser, jstring name){
    return DungeonUtility::StructureParser::canParser(JavaClass::toString(env, name)) ? JNI_TRUE : JNI_FALSE;
}
export(jlong, dungeonutility_struct_StructureParser_nativeGetParser, jstring name){
    return (jlong) DungeonUtility::StructureParser::getParserByName(JavaClass::toString(env, name));
}