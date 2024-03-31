type JavaPlayerScale = {
	setValue(value: number): void;
	getValue(): number;
	reset(): void;
	getType(): JavaScale;
}

type JavaScale = {
	setDisplay(v: boolean);
	isDisplay(): boolean;
	getScaleDescription(): ScaleDescription;
	isReset(): boolean;
}

interface ScaleDescription {
	name: string,
	isLeft: boolean,
	isReset: boolean,
	isDisplay?: boolean
}

type JavaScales = {
	getPlayers(): string[];
	getScales(): string[];
	getScaleByName(name: string): JavaScale;
	getScaleByPlayer(player: number | string, name: string): JavaPlayerScale;
	register(description: ScaleDescription): JavaScale;

	setServerMode(value: boolean);
}

type PacketScalesSetValue = {
	player: string,
	name: string,
	value: number
}

type PacketScalesSetServerMode = {
	mode: boolean
}

type SaveScope = {
	players: {[player: string]: {[scale_name: string]: number}}
}

if(Game.isDedicatedServer())
	var ScalesJava: JavaScales = WRAP_JAVA("com.core.api.module_server.Scales")
else
	var ScalesJava: JavaScales = WRAP_JAVA("com.core.api.module.Scales");


Network.addClientPacket("scales.setValue", function(data: PacketScalesSetValue){
	ScalesJava.getScaleByPlayer(data.player, data.name).setValue(data.value);
}); 

Network.addClientPacket("scales.setMode", function(data: PacketScalesSetServerMode){
	ScalesJava.setServerMode(data.mode);
}); 


Callback.addCallback("EntityDeath", (entity) => {
	let players: any = Network.getConnectedPlayers();
	if(players.indexOf(entity) != -1){
		let scales = ScalesJava.getScales();
		for(let i in scales){
			let name = scales[i];
			if(ScalesJava.getScaleByName(name).isReset())
				ScalesJava.getScaleByPlayer(entity, name).reset();
		}
	}
});

Callback.addCallback("ServerPlayerLoaded", (player) => {
	let scales = ScalesJava.getScales();
	let client = Network.getClientForPlayer(player);

	if(client){
		for(let i in scales)
			Scales.getScaleByPlayer(player, scales[i]).send();
		let packet: PacketScalesSetServerMode = {mode: Game.isDedicatedServer()};
		client.send("scales.setMode", packet)
	};
	
});

class PlayerScale {
	private java_class: JavaPlayerScale;
	private player: number;
	private name: string;

	constructor(java_class: JavaPlayerScale, player: number, name: string){
		this.java_class = java_class;
		this.player = player;
		this.name = name;
	}

	public getValue(): number {
		return this.java_class.getValue();
	}

	public send(value: number = this.getValue(), client: NetworkClient = Network.getClientForPlayer(this.player)): void {
		let packet: PacketScalesSetValue = {//конвертация типов java в js 
			player: Entity.getNameTag(this.player),
			name: String(this.name),
			value: Number(value)
		}
		client && client.send("scales.setValue", packet);
	}

	public setValue(value: number): void {
		this.send(value);
		this.java_class.setValue(value);
	}

	public addValue(v: number): void {
		this.setValue(this.getValue() + v);
	}

	public reset(): void {
		this.java_class.reset();
	}

	public getType(): JavaScale {
		return this.java_class.getType();
	}
}

class Scale {
	private java_class: JavaScale;

	constructor(java_class: JavaScale){
		this.java_class = java_class;
	}

	public setDisplay(v: boolean): Scale {
		this.java_class.setDisplay(v);
		return this;
	}

	public isDisplay(): boolean {
		return this.java_class.isDisplay();
	}
}

namespace Scales {
	export function register(obj: ScaleDescription): Scale {
		return new Scale(ScalesJava.register(obj));
	} 

	export function getScaleByPlayer(player: number, name: string){
		return new PlayerScale(ScalesJava.getScaleByPlayer(player, name), player, name);
	}

	export function isCreative(player: number, name: string): boolean {
		return new PlayerActor(player).getGameMode() == 0;
	}
}

Saver.addSavesScope("lib.scales", (scope: SaveScope) => {
    let players = Object.keys(scope.players || {});
		
	for(let i in players){
		let player = players[i];
		let scales = Object.keys(scope.players[player]);

		for(let j in scales){
			let scale = scales[j];
			ScalesJava.getScaleByPlayer(player, scale).setValue(scope.players[player][scale]);
		}
	}
}, () => {
    let obj = {};
	let players = ScalesJava.getPlayers();

	for(let i in players){
		let player = players[i];
		let scales = ScalesJava.getScales();
		let data_save = obj[player] = {};

		for(let j in scales){
			let scale = scales[j];
			data_save[scale] = ScalesJava.getScaleByPlayer(player, scale).getValue();
		}
	}

	alert(JSON.stringify(obj))
    return {
        players: obj,
    }
});