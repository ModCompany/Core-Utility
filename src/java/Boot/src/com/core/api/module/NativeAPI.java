package com.core.api.module;

public class NativeAPI {
    native public static int dynamicToStatic(int id, int type);
    native public static int staticToDynamic(int id, int type);
    native public static long getActorID(long ptr);
    native public static int getXBlockPos(long ptr);
    native public static int getYBlockPos(long ptr);
    native public static int getZBlockPos(long ptr);
    native public static long getActorById(long id);

    native public static void setWorldGenerator(String json);
}
