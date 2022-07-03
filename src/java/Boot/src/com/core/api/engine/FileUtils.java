package com.core.api.engine;

public class FileUtils {
    
    public static native void deleteDirectory(String path);
    public static native void deleteDirectoryContents(String path);
    public static native void deleteEmptyDirectory(String dir);
    public static native void deleteFile(String file);
    public static native void renameDirectory(String old_name, String new_name);
    public static native void renameFile(String old_name,String new_name);
    public static native void copyDirectory(String from,String to); 
    public static native boolean fileExists(String file);
    public static native boolean directoryExists(String dir);    
    public static native boolean isValidPath(String path);
    public static native boolean isRelativePath(String path);
    public static native boolean isExists(String path_or_file);
    public static native void createDirectory(String path);
    public static native void createDirectoryForFile(String path);


}
