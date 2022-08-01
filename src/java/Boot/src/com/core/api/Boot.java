package com.core.api;

import java.util.HashMap;

import com.core.api.module.Hook;
import com.reider.ModLoader;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

class Boot {
    public static void boot(HashMap<?, ?> data) {
        Hook.jsonLoad();
        ModLoader.boot(data);
        Logger.debug("TEST_MOD", "Hello from Java");
    }  
}
 