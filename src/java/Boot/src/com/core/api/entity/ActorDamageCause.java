package com.core.api.entity;

import org.mozilla.javascript.Function;

import com.core.api.JsHelper;
import com.core.api.engine.PointerClass;
import com.core.api.mcpe.entity.Actor;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.log.DialogHelper;

public class ActorDamageCause {
    native public static void registerCause(int cause, ActorDamageCause type);

    Function deadMessage;
    public final int id;
    public ActorDamageCause(int cause){
        registerCause(cause, this);
        id = cause;
    }

    public ActorDamageCause setDeadMessage(Function deadMessage){
        this.deadMessage = deadMessage;
        return this;
    }

    public String getDeadMessage(long type, String name, long actor){
        try {
            Logger.debug(type+" "+name+" "+actor);
            return (String) JsHelper.callFunction(deadMessage, new Object[] {new PointerClass(type), name, new Actor(actor)});
        } catch (Exception e) {
            JsHelper.error(e);
        }
        return "kill";
    }
}
