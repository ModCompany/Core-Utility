/// <reference path="./core-engine.d.ts"/>

declare class ToolTip {
    static addToolTip(id: number, data: number, name: string): void;
    static addToolTips(id: number, data: number, name: string[]): void;
    static deletToolTip(id: number, data: number, name: string): void;
    static clearToolTip(id: number, data: number): void;
    static getToolTips(id: number, data: number): string[];
    static clearToolTips(): void;
}

declare class ConversionType {
    static ITEM: number
    static BLOCK: number
}

declare class NativeAPI {
    static dynamicToStatic(id: number, type?: number): number;           
    static staticToDynamic(id: number, type?: number): number;    
    static getActorID(ptr: number): number;
    static getXBlockPos(ptr: number): number;
    static getYBlockPos(ptr: number): number;
    static getZBlockPos(ptr: number): number;
    static getActorById(ptr: number): number;
}

declare class Injector {
    call(symbol): void;
    getInjector(): any;
}

declare class ItemsUtil {
    static getItemById(id: number): number;
}


declare interface CoreUtilityAPI {
    NativeAPI: NativeAPI,
    ConversionType: ConversionType,
    ToolTip: ToolTip,
    Injector: Injector,
    ItemsUtil: ItemsUtil,
    requireGlobal(cmd: string): any;
}

declare namespace ModAPI {
    export function addAPICallback(name: "CoreUtility", func: (api: CoreUtilityAPI) => void): void;
}