package com.core.api.data;

public class Tier {
    public int uses;
    public int level;
    public int enchantment;
    public float attackDamage;
    public int speed;

    public Tier(int a,int b,float c, int d,int g){
        uses = a;
        level = b;
        attackDamage = c;
        enchantment = d;
        speed = g;
    }
}