#include <java.h>
#include <core/Global.h>
#include <core/JavaClass.h>




export(void, engine_FileUtils_copyDirectory,jstring from,jstring to){
    return Global::getFileSystem()->copyDirectoryAndContentsRecursivelyWithLimit(Core::Path(JavaClass::toStlString(env,from)),Core::Path(JavaClass::toStlString(env,to)));
} 

export(jboolean, engine_FileUtils_directoryExists,jstring file){
    return Global::getFileSystem()->directoryExists(Core::Path(JavaClass::toStlString(env,file)));
}

export(jboolean, engine_FileUtils_fileExists,jstring file){
    return Global::getFileSystem()->fileExists(Core::Path(JavaClass::toStlString(env,file)));
}

export(jboolean,engine_FileUtils_isExists,jstring file){
    return Global::getFileSystem()->fileOrDirectoryExists(Core::Path(JavaClass::toStlString(env,file)));     
}

export(jboolean,engine_FileUtils_isRelativePath,jstring file){
    return Global::getFileSystem()->isRelativePath(Core::Path(JavaClass::toStlString(env,file)));     
}

export(jboolean,engine_FileUtils_isValidPath,jstring file){
    return Global::getFileSystem()->isValidPath(Core::Path(JavaClass::toStlString(env,file)));     
}

export(void, engine_FileUtils_renameFile,jstring from,jstring to){
    return Global::getFileSystem()->renameFile(Core::Path(JavaClass::toStlString(env,from)),Core::Path(JavaClass::toStlString(env,to)));
}

export(void, engine_FileUtils_renameDirectory,jstring from,jstring to){
    return Global::getFileSystem()->renameDirectory(Core::Path(JavaClass::toStlString(env,from)),Core::Path(JavaClass::toStlString(env,to)));
}

export(void, engine_FileUtils_deleteEmptyDirectory,jstring file){
    return Global::getFileSystem()->deleteEmptyDirectory(Core::Path(JavaClass::toStlString(env,file)));
}

export(void, engine_FileUtils_deleteDirectoryContents,jstring file){
    return Global::getFileSystem()->deleteDirectoryContentsRecursively(Core::Path(JavaClass::toStlString(env,file)));
}

export(void, engine_FileUtils_deleteDirectory,jstring file){
    return Global::getFileSystem()->deleteDirectoryAndContentsRecursively(Core::Path(JavaClass::toStlString(env,file)));
}

export(void, engine_FileUtils_deleteFile,jstring file){
    return Global::getFileSystem()->deleteFile(Core::Path(JavaClass::toStlString(env,file)));
}

export(void, engine_FileUtils_createDirectory,jstring file){
    return Global::getFileSystem()->createDirectoryRecursively(Core::Path(JavaClass::toStlString(env,file)));   
}

export(void,engine_FileUtils_createDirectoryForFile,jstring file){
    return Global::getFileSystem()->createDirectoryForFile(Core::Path(JavaClass::toStlString(env,file)));     
}
