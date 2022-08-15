package com.core.api.engine.ui;

import org.mozilla.javascript.Function;

import com.core.api.JsHelper;
import com.core.api.engine.ui.types.Element;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.log.DialogHelper;

import android.animation.ValueAnimator;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.os.Handler;
import android.os.Looper;

public class NativeUi {
    long ptr;
    public Element[] elements;
    public boolean ui_update;
    public ValueAnimator animator;
    public Function jsUpdate;

    public NativeUi(Element[] elements){
        ptr = init(elements);
        this.elements = elements;
        ui_update = false;
    }
    public NativeUi(){
        this(new Element[] {});
    }

    public boolean isOpen(){
        return isOpen(ptr);
    }

    public NativeUi open(){
        open(ptr);
        if(ui_update)
            upt();
        return this;
    }

    public NativeUi close(){
        close(ptr);
        animator.cancel();
        return this;
    }

    public NativeUi setElements(Element[] elements){
        setElements(ptr, elements);
        return this;
    }

    public Element[] getElements(){
        return elements;
    }

    boolean isFree = false;
    public void free(){
        if(!isFree)
            free(ptr);
        isFree = true;
    }

    public void force(){
        setElements(elements);
    }

    public void setHandlerUpdate(Function function){
        ui_update = true;
        jsUpdate = function;
    }

    public void update(float value){
        if(jsUpdate != null)
            JsHelper.callFunction(jsUpdate, new Object[] {this, value});
    }

    private void upt(){
        try {
            animator = ValueAnimator.ofFloat(0, 1);
            animator.setDuration(1000);
            animator.setRepeatCount(ValueAnimator.INFINITE);
            animator.addUpdateListener(new AnimatorUpdateListener() {
                @Override
                public void onAnimationUpdate(ValueAnimator arg0) {
                    try {
                        update((float) arg0.getAnimatedValue());
                    }catch(Exception e) {
                        Logger.error(e.getLocalizedMessage());
                        DialogHelper.reportNonFatalError("NativeUi-update", e.getCause());
                        arg0.cancel();
                    }
                }
            });
            Handler handler = new Handler(Looper.getMainLooper());
            handler.post(new Runnable(){
                @Override
                public void run() {
                    animator.start();
                }
            });
        } catch (Exception e) {
            Logger.error(e.getLocalizedMessage());
            DialogHelper.reportNonFatalError("NativeUi-update", e.getCause());
        }
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        free();
    }
    
    static public native Element[] getElements(long ptr);
    static public native void setElements(long ptr, Element[] elements);
    static public native void setPriority(long ptr, int priority);
    static public native void open(long ptr);
    static public native void close(long ptr);
    static public native boolean isOpen(long ptr);
    static public native void free(long ptr);
    static public native long init(Element[] elements);
}
