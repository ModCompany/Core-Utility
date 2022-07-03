package com.core.api.mcpe;

public class World {
    native public static void setFlatGenerator(String json);
    native public static void addWorldToCache(String world_path);
    native public static void updateWorlds();
    native public static int getWorldsCount();
}
