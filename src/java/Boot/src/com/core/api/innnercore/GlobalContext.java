package com.core.api.innnercore;

import com.core.api.mcpe.client.ClientInstance;
import com.core.api.mcpe.entity.LocalPlayer;
import com.core.api.mcpe.entity.ServerPlayer;
import com.core.api.mcpe.level.Level;
import com.core.api.mcpe.level.LevelServer;

public class GlobalContext {
    native private static long getClientInstacePointer();
    native private static long getServerPlayerPointer();
    native private static long getLocalPlayerPointer();
    native private static long getServerLevelPointer();
    native private static long getLevelPointer();

    public static ClientInstance getClientInstace(){
        return new ClientInstance(getClientInstacePointer());
    }
    public static LevelServer getLevelServer(){
        return new LevelServer(getServerLevelPointer());
    }
    public static Level getLevel(){
        return new Level(getLevelPointer());
    }
    public static LocalPlayer getLocalPlayer(){
        return new LocalPlayer(getLocalPlayerPointer());
    }
    public static ServerPlayer getServerPlayer(){
        return new ServerPlayer(getServerPlayerPointer());
    }
}
