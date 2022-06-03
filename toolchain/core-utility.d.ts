/// <reference path="./core-engine.d.ts"/>

declare interface IToolTip {
    /**
     * add tool tip item
     * @param id - id item
     * @param data - data item
     * @param name - add Tool tip
     */
    addToolTip(id: number, data: number, name: string): void;
    /**
     * add tool tips item
     * @param id - id item
     * @param data - data item
     * @param names - add Tool tips
     */
    addToolTips(id: number, data: number, names: string[]): void;
    /**
     * delete tool tip item
     * @param id - id item
     * @param data - data item
     * @param name - delete tool tip
     */
    deletToolTip(id: number, data: number, name: string): void;
    /**
     * will delete all tool tip items
     * @param id - id item
     * @param data - data item
     */
    clearToolTip(id: number, data: number): void;
    /**
     * will return all tool tip of the item
     * @param id - id item
     * @param data - data item
     */
    getToolTips(id: number, data: number): string[];
    /**
     * clear all tool tip
     */
    clearToolTips(): void;
}
declare var ToolTip: IToolTip;

/**
 * types of id conversion
 */
declare interface IConversionType {
    ITEM: number
    BLOCK: number
}
declare var ConversionType: IConversionType;

declare interface INativeAPI {
    /**
     * convert dynamic to static
     * @param id - dynamic id
     * @param type = type conversion
     */
    dynamicToStatic(id: number, type?: number): number;  
    /**
     * convert static to dynamic
     * @param id - dynamic id
     * @param type = type conversion
     */         
    staticToDynamic(id: number, type?: number): number;  
    /**
     * returns a unique identifier
     * @param ptr - pointer Actor
     */  
    getActorID(ptr: number): number;
    /**
     * returns x from BlockPos
     * @param ptr - pointer BlockPos
     */
    getXBlockPos(ptr: number): number;
    /**
     * returns y from BlockPos
     * @param ptr - pointer BlockPos
     */
    getYBlockPos(ptr: number): number;
    /**
     * returns z from BlockPos
     * @param ptr - pointer BlockPos
     */
    getZBlockPos(ptr: number): number;
    /**
     * returns Actor to unique identifier
     * @param ent - unique identifier
     */
    getActorById(ent: number): number;
}
declare var NativeAPI: INativeAPI;

declare class Injector {
    /**
     * create Injector
     * @param ptr - pointer c++ class
     */
    constructor(ptr: number);
    /**
     * call c++ methot
     * @param symbol - methot symbol
     */
    call(symbol): void;
    /**
     * return Java Injector
     */
    getInjector(): any;
    /**
     * call c++ methot, return result int
     * @param symbol - methot symbol
     */
    getIntResult(symbol: string): number;
    /**
     * call c++ methot, return result float
     * @param symbol - methot symbol
     */
    getFloatResult(symbol: string): number;
    /**
     * call c++ methot, return result bool
     * @param symbol - methot symbol
     */
    getBoolResult(symbol: string): Boolean;
    /**
     * call c++ methot, return result string
     * @param symbol - methot symbol
     */
    getStringResult(symbol: string): string;
    /**
     * call c++ methot, return result pointer to class
     * @param symbol - methot symbol
     */
    getPointerResult(symbol: string): number;
}

declare interface IItemsUtil {
    /**
     * return pointer Item
     * @param id - item id
     */
    getItemById(id: number): number;
}
declare var ItemsUtil: IItemsUtil;

declare interface ICustomEntity {
    /**
     * add handler tick entity
     * @param name - string id entity (minecraft:zombie<>)
     * @param func 
     */
    setHandlerTick(name: string, func: (entity: number) => void);
}
declare var CustomEntity: ICustomEntity;

declare interface CoreUtilityAPI {
    NativeAPI: INativeAPI,
    ConversionType: IConversionType,
    ToolTip: IToolTip,
    Injector: Injector,
    ItemsUtil: IItemsUtil,
    CustomEntity: ICustomEntity,
    requireGlobal(cmd: string): any;
}

declare namespace ModAPI {
    export function addAPICallback(name: "CoreUtility", func: (api: CoreUtilityAPI) => void): void;
}