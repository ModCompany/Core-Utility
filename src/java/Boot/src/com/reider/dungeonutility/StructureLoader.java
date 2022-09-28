package com.reider.dungeonutility;

import com.zhekasmirnov.innercore.api.mod.adaptedscript.AdaptedScriptAPI;
import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.ScriptableObject;

import java.util.*;

public class StructureLoader {
    public static final String logger_name = "DungeonUtility";
    public static ScriptableObject ids = new ScriptableObject() {
        @Override
        public String getClassName() {
            return "DungeonUtility";
        }
    };
    public static Scriptable BlockID;

    private static boolean isNumber(String str){
        char[] chars = str.toCharArray();
        for(char c : chars)
            if(!Character.isDigit(c))
                return false;
        return true;
    }

    public static int getIdBlock(String id){
        if(id.equals(""))
            return 0;
        if(isNumber(id))
            return Integer.parseInt(id);
        return (int) (BlockID.get(id, BlockID));
    }
    public static Object getIdBlock(int id){
        if(id > 8000)
            return AdaptedScriptAPI.IDRegistry.getNameByID(id);
        return id;
    }
    public static int getInt(String integer){
        if(integer.equals(""))
            return 0;
        return Integer.parseInt(integer);
    }
   /*  public static HashMap<String, Integer> getHashMapToJson(LinkedTreeMap<String, Double> object){
        HashMap<String, Integer> result = new HashMap<>();
        Set<Map.Entry<String, Double>> keys = object.entrySet();
        for(Map.Entry<String, Double> key : keys)
            result.put(key.getKey(), key.getValue().intValue());
        return result;
    }
*/
    public static String[] split(String str, char symbol){
        ArrayList<String> list = new ArrayList<>();
        list.add("");
        char[] chars = str.toCharArray();
        for(char s : chars)
            if(s == symbol)
                list.add("");
            else{
                int index = list.size() - 1;
                list.set(index, list.get(index) + s);
            }
        return list.toArray(new String[list.size()]);
    }

    static {
        AdaptedScriptAPI.IDRegistry.injectAPI(ids);
        BlockID = (Scriptable) ids.get("BlockID");
    }
}
