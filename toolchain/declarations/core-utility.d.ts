/// <reference path="./core-engine.d.ts"/>

declare interface ToolTip {
    addToolTip(id: number, data: number, name: string): void;
    addToolTips(id: number, data: number, name: string[]): void;
    deletToolTip(id: number, data: number, name: string): void;
    clearToolTip(id: number, data: number): void;
    getToolTips(id: number, data: number): string[];
    clearToolTips(): void;
}

declare interface ConversionType {
    ITEM: number
    BLOCK: number
}

declare interface NativeAPI {
    dynamicToStatic(id: number, type: number): number;           
    staticToDynamic(id: number, type: number): number;    
    getActorID(ptr: number): number;
    getXBlockPos(ptr: number): number;
    getYBlockPos(ptr: number): number;
    getZBlockPos(ptr: number): number;
    getActorById(ptr: number): number;
}

declare interface CoreUtilityAPI {
    NativeAPI: NativeAPI,
    ConversionType: ConversionType,
    ToolTip: ToolTip,
    requireGlobal(cmd: string): any;
}

declare namespace ModAPI {
    export function addAPICallback(name: "CoreUtility", func: (api: CoreUtilityAPI) => void): void;
}