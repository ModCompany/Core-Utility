package com.core.api.module_server;

import com.zhekasmirnov.innercore.api.NativeAPI;

import org.mozilla.javascript.ScriptableObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

public class Scales {
    public static interface IScaleDescription {
        String getName();
        String getFull();
        String getHelf();
        String getEmpty();
        boolean isLeft();
        boolean isReset();
        boolean isDisplay();
    }

    public static class ScalePlayer {
        Scales pointer;
        int value;

        public ScalePlayer(Scales pointer){
            this.pointer = pointer;
        }

        public void setValue(int value){
            this.value = value;
        }

        public int getValue(){
            return value;
        }

        public Scales getType(){
            return pointer;
        }

        public void reset(){
            value = 20;
        }
    }

    private static final HashMap<String, HashMap<String, ScalePlayer>> players = new HashMap<>();
    private static final HashMap<String, Scales> scales = new HashMap<>();

    public static String[] getPlayers(){
        final ArrayList<String> keys = new ArrayList<>();
        final Iterator<String> it = players.keySet().iterator();

        while (it.hasNext()) {
            keys.add(it.next());
        }

        return keys.toArray(new String[0]);
    }

    public static String[] getScales(){
        final ArrayList<String> keys = new ArrayList<>();
        final Iterator<String> it = scales.keySet().iterator();

        while (it.hasNext()) {
            keys.add(it.next());
        }

        return keys.toArray(new String[0]);
    }

    public static Scales getScaleByName(String name){
        return scales.get(name);
    }

    public static ScalePlayer getScaleByPlayer(long player, String name){
        return getScaleByPlayer(NativeAPI.getNameTag(player), name);
        //return new ScalePlayer(getScalePlayer(NativeAPI.getNameTag(player), name));
    }

    public static ScalePlayer getScaleByPlayer(String player, String name){
        HashMap<String, ScalePlayer> datas = players.get(player);
        if(datas == null){
            datas = new HashMap<>();
            players.put(player, datas);
        }

        ScalePlayer data = datas.get(name);
        if(data == null){
            data = new ScalePlayer(getScaleByName(name));
            datas.put(name, data);
        }

        return data;
    }

    public static Scales register(ScriptableObject description){
        return new Scales(description);
    }

    public static void registerScale(String name, boolean left, boolean reset, boolean display, Scales self){
        self.name = name;
        self.isLeft = left;
        self.isReset = reset;
        self.isDisplay = display;
        scales.put(name, self);
    }

    private String name;
    private boolean isLeft, isReset, isDisplay;

    public Scales(IScaleDescription description){
        registerScale(
            description.getName(),
            description.isLeft(),
            description.isReset(),
            description.isDisplay(),
            this
        );
    }

    public Scales(ScriptableObject object){
        registerScale(
            (String) object.get("name"),
            (boolean) object.get("isLeft"),
            (boolean) object.get("isReset"),
            object.has("isDisplay", object) ? (boolean) object.get("isDisplay") : true,
            this
        );
    }

    public String getName(){
        return name;
    }

    public String getFull(){
        return "";
    }

    public void setFull(String name){
    }

    public String getHelf(){
        return "";
    }

    public void setHelf(String name){
    }

    public String getEmpty(){
        return "";
    }

    public void setEmpty(String name){
    }

    public boolean isLeft(){
        return isLeft;
    }

    public boolean isReset(){
        return isReset;
    }

    public boolean isDisplay(){
        return isDisplay;
    }

    public void setDisplay(boolean v){
       isDisplay = v;
    }

    public IScaleDescription getScaleDescription(){
        Scales _this = this;
        return new IScaleDescription() {
            @Override
            public String getName() {
                return _this.getName();
            }
            @Override
            public String getFull() {
                return _this.getFull();
            }
            @Override
            public String getHelf() {
                return _this.getHelf();
            }
            @Override
            public String getEmpty() {
                return _this.getEmpty();
            }
            @Override
            public boolean isLeft() {
                return _this.isLeft();
            }
            @Override
            public boolean isReset() {
                return _this.isReset();
            }
            @Override
            public boolean isDisplay() {
                return _this.isDisplay();
            }
        };
    }

    public ScriptableObject getScriptable(){
        ScriptableObject object = new ScriptableObject(){
            @Override
            public String getClassName() {
                return "null";
            }
        };
        object.put("name", object, getName());
        object.put("full", object, getFull());
        object.put("helf", object, getHelf());
        object.put("empty", object, getEmpty());
        object.put("isLeft", object, isLeft());
        object.put("isReset", object, isReset());
        return object;
    }
}

