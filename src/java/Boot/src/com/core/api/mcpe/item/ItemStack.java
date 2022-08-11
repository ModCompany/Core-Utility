package com.core.api.mcpe.item;

import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.ScriptableObject;

import com.core.api.Injector;
import com.core.api.engine.PointerClass;
import com.core.api.mcpe.block.Block;
import com.core.api.mcpe.block.BlockLegacy;
import com.core.api.module.types.Parameter;

public class ItemStack extends PointerClass {
    Injector injector;

    public int id;
    public int data;
    public int count;

    public ItemStack(long ptr){
        super(ptr);
        injector = new Injector(ptr);
        id = getId();
        data = getDamageValue();
        count = getCount();
    }

    public boolean isBlock(){
        return injector.setArgsTypes().getBoolResult("_ZNK13ItemStackBase7isBlockEv");
    }

    public boolean isGlint(){
        return injector.setArgsTypes().getBoolResult("_ZNK13ItemStackBase7isGlintEv");
    }

    public boolean isExplodable(){
        return injector.setArgsTypes().getBoolResult("_ZNK13ItemStackBase12isExplodableEv");
    }

    public boolean isFireResistant(){
        return injector.setArgsTypes().getBoolResult("_ZNK13ItemStackBase15isFireResistantEv");
    }

    public boolean isArmorItem(){
        return injector.setArgsTypes().getBoolResult("_ZNK13ItemStackBase11isArmorItemEv");
    }

    public Block getBlock(){
        return new Block(injector.setArgsTypes().getPointerResult("_ZNK13ItemStackBase8getBlockEv"));
    }

    public BlockLegacy getLegacyBlock(){
        return new BlockLegacy(injector.setArgsTypes().getPointerResult("_ZNK13ItemStackBase14getLegacyBlockEv"));
    }

    public Item getItem(){
        return new Item(injector.setArgsTypes().getPointerResult("_ZNK13ItemStackBase7getItemEv"));
    }

    public int getIdAux(){
        return injector.setArgsTypes().getIntResult("_ZNK13ItemStackBase8getIdAuxEv");
    }

    public int getId(){
        return injector.setArgsTypes().getIntResult("_ZNK13ItemStackBase5getIdEv");
    }

    public int getDamageValue(){
        return injector.setArgsTypes().getIntResult("_ZNK13ItemStackBase14getDamageValueEv");
    }

    public int getAttackDamage(){
        return injector.setArgsTypes().getIntResult("_ZNK13ItemStackBase15getAttackDamageEv");
    }

    public int getMaxStackSize(){
        return injector.setArgsTypes().getIntResult("_ZNK13ItemStackBase15getMaxStackSizeEv");
    }

    public int getIdAuxEnchanted(){
        return injector.setArgsTypes().getIntResult("_ZNK13ItemStackBase17getIdAuxEnchantedEv");
    }

    public int getAuxValue(){
        return injector.setArgsTypes().getIntResult("_ZNK13ItemStackBase11getAuxValueEv");
    }

    public int getRendererId(){
        return injector.setArgsTypes().getIntResult("_ZNK13ItemStackBase13getRendererIdEv");
    }

    public void setAuxValue(int value){
        injector.setArgsTypes().call("_ZN13ItemStackBase11setAuxValueEs", new Object[] {
            Parameter.getInt(value)
        });
    }
    

    public void setDamageValue(int value){
        injector.setArgsTypes().call("_ZN13ItemStackBase14setDamageValueEs", new Object[] {
            Parameter.getInt(value)
        });
    }

    public void set(int count){
        injector.setArgsTypes("int").getIntResult("_ZN13ItemStackBase3setEi", new Object[] {
            Parameter.getInt(count)
        });
    }

    public void add(int count){
        injector.setArgsTypes("int").getIntResult("_ZN13ItemStackBase3addEi", new Object[] {
            Parameter.getInt(count)
        });
    }

    public void remove(int count){
        injector.setArgsTypes("int").getIntResult("_ZN13ItemStackBase6removeEi", new Object[] {
            Parameter.getInt(count)
        });
    }

    public int getCount(){
        int count = injector.setLib("innercore").setArgsTypes().getIntResult("_ZNK13ItemStackBase8getCountEv");
        injector.setLib("mcpe");
        return count;
    }


    public Scriptable getItemInstance(){
        ScriptableObject object = new ScriptableObject() {
            @Override
            public String getClassName() {
                return "ItemInstance";
            }
        };
        object.put("id", object, id);
        object.put("data", object, data == 0 ? getAuxValue() : data);
        object.put("count", object, count);
        return object;
    }
}
