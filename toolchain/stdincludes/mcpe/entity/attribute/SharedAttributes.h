#pragma once

class Attribute;

class SharedAttributes{
    public:

public:
    //Objects
    static Attribute  FALL_DAMAGE;
    static Attribute MOVEMENT_SPEED;
    static Attribute  HEALTH;
    static SharedAttributes * ABSORPTION;
    static Attribute ATTACK_DAMAGE;
    static SharedAttributes * FOLLOW_RANGE;
    static SharedAttributes * UNDERWATER_MOVEMENT_SPEED;
    static SharedAttributes * JUMP_STRENGTH;
    static SharedAttributes * KNOCKBACK_RESISTANCE;
    static SharedAttributes * LUCK;
};//SharedAttributes

