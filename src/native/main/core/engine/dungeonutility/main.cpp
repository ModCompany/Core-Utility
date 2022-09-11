#include <core/DungeonUtility.h>
#include <java.h>
#include <innercore_callbacks.h>
#include <symbol.h>
#include <hook.h>
#include <logger.h>

DungeonUtility::DungeonUtilityModule::DungeonUtilityModule(): Module("core_utility.dungeonutility"){

}

void DungeonUtility::DungeonUtilityModule::initialize(){
    JNIEnv* env;
	ATTACH_JAVA(env, JNI_VERSION_1_6){
        DungeonUtility::StructureJavaParser::parserClass = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/core/api/dungeonutility/struct/StructureParser")));

        DungeonUtility::StructureJavaParser::saveID = env->GetMethodID(DungeonUtility::StructureJavaParser::parserClass, "nativeSave", "(J)Ljava/lang/String;");
        DungeonUtility::StructureJavaParser::readID = env->GetMethodID(DungeonUtility::StructureJavaParser::parserClass, "nativeRead", "(Ljava/lang/String;)J");
    }
}