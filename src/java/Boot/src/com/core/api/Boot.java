package com.core.api;

import java.util.HashMap;

import com.core.api.module.Hook;
import com.core.api.item.ToolTip;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

class Boot {
    public static void boot(HashMap<?, ?> data) {
        Hook.jsonLoad();
        ToolTip.init();
        Logger.debug("TEST_MOD", "Hello from Java");
    }  
}
 