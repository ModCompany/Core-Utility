package com.core.api;

import java.io.File;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.NativeJavaClass;

import com.core.api.module.types.Parameter;
import com.zhekasmirnov.apparatus.adapter.innercore.EngineConfig;
import com.zhekasmirnov.horizon.runtime.logger.Logger;
import com.zhekasmirnov.horizon.util.FileUtils;
import com.zhekasmirnov.innercore.api.log.DialogHelper;
import com.zhekasmirnov.innercore.api.log.ICLog;
import com.zhekasmirnov.innercore.mod.executable.Compiler;

import org.json.JSONArray;

public class JsHelper {
    public static Context context = Context.enter();
    public static Scriptable scriptable = context.initStandardObjects();
    private static Scriptable that = context.newObject(scriptable);

    public static Object callFunction(Function function, Object[] args) {
        Scriptable parent = function.getParentScope();
        return function.call(Compiler.assureContextForCurrentThread(), parent, parent, args);
    }

    public static String comment(String input) {
        String[] RE_BLOCKS = new String[] {
            "\\/(\\*)[^*]*\\*+(?:[^*\\/][^*]*\\*+)*\\/", // multiline comments
            "\\/(\\/)[^\\n]*$", // single line comments
            "\"(?:[^\"\\\\]*|\\\\[\\S\\s])*\"|'(?:[^'\\\\]*|\\\\[\\S\\s])*'|(?:[^`\\\\]*|\\\\[\\S\\s])*", // strings
            "(?:[$\\w\\)\\]]|\\+\\+|--)\\s*\\/(?![*\\/])" // division operator
        };
        StringBuilder regexBuilder = new StringBuilder();
        for (int i = 0; i < RE_BLOCKS.length; i++) {
            regexBuilder.append(RE_BLOCKS[i]);
            if (i != RE_BLOCKS.length - 1) {
                regexBuilder.append("|");
            }
        }
        String regex = regexBuilder.toString();
        Pattern pattern = Pattern.compile(regex, Pattern.MULTILINE);
        Matcher matcher = pattern.matcher(input);
        StringBuffer resultBuilder = new StringBuffer();
        while (matcher.find()) {
            if (matcher.group(1) != null) { // if it's a multiline comment
                matcher.appendReplacement(resultBuilder, " ");
            } else if (matcher.group(2) != null) { // if it's a single line comment
                matcher.appendReplacement(resultBuilder, "");
            } else { // if it's a string or regex literal
                matcher.appendReplacement(resultBuilder, matcher.group());
            }
        }
        matcher.appendTail(resultBuilder);
        return resultBuilder.toString();
    }
    public static String readFile(String path) throws Exception {
        File file = new File(path);
        if(!file.exists()) return null;
        return FileUtils.readFileText(file);
    }

    public static JSONArray loadFromPath(String path) throws Exception {
        String file = readFile(path);
        if(file == null) return null;
        return new JSONArray(comment(file)); 
    }

    public static void log(Exception e){
        Logger.info(Boot.LOOGER_PREFIX, ICLog.getStackTrace(e));
    }

    public static void log(String text){
        Logger.info(Boot.LOOGER_PREFIX, text);
    }

    public static void error(Exception e){
        String message = ICLog.getStackTrace(e);
        Logger.error("CoreUtility", message);
        
        if(EngineConfig.isDeveloperMode())
            DialogHelper.openFormattedDialog(message, "CoreUtility");
    }

    public static Object get(Class<?> _class){
        NativeJavaClass nativeClass = new NativeJavaClass(scriptable, _class, true);
        return new Function(){
            @Override
            public Scriptable construct(Context context, Scriptable self, Object[] args) {
                return nativeClass.construct(context, self, args);
            }
            @Override
            public Object call(Context context, Scriptable self, Scriptable scriptable, Object[] args) {
                return nativeClass.call(context, self, scriptable, args);
            }
            @Override
            public Object get(String arg0, Scriptable arg1) {
                return nativeClass.get(arg0, arg1);
            }

            @Override
            public Object get(int arg0, Scriptable arg1) {
                return nativeClass.get(arg0, arg1);
            }

            @Override
            public void put(String arg0, Scriptable arg1, Object arg2) {
                nativeClass.put(arg0, arg1, arg2);
            }

            @Override
            public void put(int arg0, Scriptable arg1, Object arg2) {
                nativeClass.put(arg0, arg1, arg2);
            }

            @Override
            public Scriptable getParentScope() {
                return nativeClass.getParentScope();
            }

            @Override
            public Scriptable getPrototype() {
                return nativeClass.getPrototype();
            }

            @Override
            public String getClassName() {
                return nativeClass.getClassName();
            }

            @Override
            public boolean has(String arg0, Scriptable arg1) {
                return nativeClass.has(arg0, arg1);
            }

            @Override
            public boolean has(int arg0, Scriptable arg1) {
                return nativeClass.has(arg0, arg1);
            }

            @Override
            public boolean hasInstance(Scriptable arg0) {
                return nativeClass.hasInstance(arg0);
            }

            @Override
            public int hashCode() {
                return nativeClass.hashCode();
            }

            @Override
            public Object[] getIds() {
                return nativeClass.getIds();
            }
            @Override
            public void delete(String arg0) {
                nativeClass.delete(arg0);
            }
            @Override
            public void delete(int arg0) {
                nativeClass.delete(arg0);
            }
            @Override
            public Object getDefaultValue(Class<?> arg0) {
                return nativeClass.getDefaultValue(arg0);
            }
            @Override
            public void setParentScope(Scriptable arg0) {
                nativeClass.setParentScope(arg0);
            }
            @Override
            public void setPrototype(Scriptable arg0) {
                nativeClass.setPrototype(arg0);;
            }

            @Override
            protected Object clone() throws CloneNotSupportedException {
                return this;
            }
        };
    }

    public static Object callUnsafe(Function f, Object...obj){
        return f.call(context,scriptable,that,obj);
    }
    public static Object callFunction(Function function, Parameter[] args) {
        Object[] args_ = new Object[args.length];
        for (int i = 0; i < args_.length; i++)
            args_[i] = args[i];
        return callFunction(function, args_);
    }
}
