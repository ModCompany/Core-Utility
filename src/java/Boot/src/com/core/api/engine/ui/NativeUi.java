package com.core.api.engine.ui;

import com.core.api.engine.ui.types.Element;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.innercore.api.log.DialogHelper;

import android.animation.ValueAnimator;
import android.animation.Animator;
import android.animation.Animator.AnimatorListener;
import android.animation.ValueAnimator.AnimatorUpdateListener;
import android.os.Handler;
import android.os.Looper;

public class NativeUi {
    public static interface NativeUiListener {
        public void onOpen(NativeUi ui);
        public void onClose(NativeUi ui);
        public void update(NativeUi ui, float value);
        public boolean touch(NativeUi ui, int type, float x, float y);
    }
    long ptr;
    public Element[] elements;
    public boolean ui_update;
    public ValueAnimator animator;
    public NativeUiListener listener;

    public NativeUi(Element[] elements){
        ptr = init(this, elements);
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
        if(listener != null)
            listener.onOpen(this);
        return this;
    }

    public NativeUi close(){
        close(ptr);
        animator.cancel();
        if(listener != null)
            listener.onClose(this);
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

    public void forceRefresh(){
        setElements(elements);
    }

    public void setListener(NativeUiListener listener){
        ui_update = true;
        this.listener = listener;
    }

    public void update(float value){
        if(listener != null)
            listener.update(this, value);
    }
    public boolean nativeTouch(int type, float x, float y){
        if(listener != null)
            return (boolean) listener.touch(this, type, x, y);
        return true;
    }
    private float time;
    private void upt(){
        try {
            animator = ValueAnimator.ofFloat(0, 1);
            animator.setDuration(1000);
            animator.setRepeatCount(ValueAnimator.INFINITE);
            NativeUi self = this;
            animator.addUpdateListener(new AnimatorUpdateListener() {
                @Override
                public void onAnimationUpdate(ValueAnimator arg0) {
                    try {
                        update(((float) arg0.getAnimatedValue()) - self.time);
                        self.time = (float) arg0.getAnimatedValue();
                    }catch(Exception e) {
                        Logger.error(e.getLocalizedMessage());
                        DialogHelper.openFormattedDialog(e.getLocalizedMessage(), "Ui-Error");
                        arg0.cancel();
                    }
                }
            });
            animator.addListener(new AnimatorListener() {
                @Override
                public void onAnimationCancel(Animator arg0) {}
                @Override
                public void onAnimationEnd(Animator arg0) {}
                @Override
                public void onAnimationRepeat(Animator arg0) {self.time = 0;}
                @Override
                public void onAnimationStart(Animator arg0) {}
            });;
            Handler handler = new Handler(Looper.getMainLooper());
            handler.post(new Runnable(){
                @Override
                public void run() {
                    animator.start();
                }
            });
        } catch (Exception e) {
            Logger.error(e.getLocalizedMessage());
            DialogHelper.openFormattedDialog(e.getLocalizedMessage(), "Ui-Error");
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
    static public native long init(Object self, Element[] elements);
}
