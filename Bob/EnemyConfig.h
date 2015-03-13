#ifndef _ENEMY_CONFIG_H
#define _ENEMY_CONFIG_H

const int base_enemy_type_1 = 3;
const int base_enemy_type_2 = 6;
const int base_enemy_type_3 = 9;
const int base_enemy_type_4 = 12;
const int base_enemy_type_5 = 15;
const int base_enemy_type_6 = 18;

const int base_x_velocity = 60;
const int base_y_velocity = -200;

const int base_enemy_dmg_1 = 1;
const int base_enemy_dmg_2 = 2;
const int base_enemy_dmg_3 = 3;
const int base_enemy_dmg_4 = 4;
const int base_enemy_dmg_5 = 5;
const int base_enemy_dmg_6 = 6;
const int base_enemy_dmg_7 = 7;
const int base_enemy_dmg_8 = 8;
const int base_enemy_dmg_9 = 9;

#define WALK_SLOW 20
#define WALK_MED  30
#define WALK_FAST 60
#define WALK_MAX  80
//******************************
//*** CHAPTER 1 ENEMIES ********
//******************************

//****** NINJAS ******//

// Brown Ninja
#define ENEMY_BROWN_NINJA_ANIM_MOVE   0
#define ENEMY_BROWN_NINJA_ANIM_DAMAGE 1

const int enemy_brown_ninja_set_cur_life = 2;
const int enemy_brown_ninja_sprite = 9;
// End Brown Ninja

// Red Ninja
#define ENEMY_RED_NINJA_ANIM_ATTACK 2
#define ENEMY_RED_NINJA_ANIM_DAMAGE 3
#define ENEMY_RED_NINJA_ANIM_DEATH  4
 

const int enemy_red_ninja_set_cur_life = 1;
const int enemy_red_ninja_sprite = 11;
// End Red Ninja

// Blue Ninja
#define ENEMY_BLUE_NINJA_ANIM_MOVE         0
#define ENEMY_BLUE_NINJA_ANIM_SWORD_ATTACK 1
#define ENEMY_BLUE_NINJA_ANIM_STAR_ATTACK  2
#define ENEMY_BLUE_NINJA_ANIM_DAMAGE       3
#define ENEMY_BLUE_NINJA_ANIM_DEATH        4

const int enemy_blue_ninja_set_cur_life = 4;
const int enemy_blue_ninja_sprite = 8;
// End Blue Ninja

// Green Ninja
#define ENEMY_GREEN_NINJA_ANIM_MOVE   0
#define ENEMY_GREEN_NINJA_ANIM_ATTACK 1
#define ENEMY_GREEN_NINJA_ANIM_DAMAGE 3
#define ENEMY_GREEN_NINJA_ANIM_DEATH  4

const int enemy_green_ninja_set_cur_life = 3;
const int enemy_green_ninja_sprite = 10;
// End Green Ninja


// Elite Guard - Pistol
#define ENEMY_PISTOL_ELITE_GUARD_ANIM_MOVE          5
#define ENEMY_PISTOL_ELITE_GUARD_ANIM_PISTOL_ATTACK 1
#define ENEMY_PISTOL_ELITE_GUARD_ANIM_RIFLE_ATTACK  2
#define ENEMY_PISTOL_ELITE_GUARD_ANIM_BATON_ATTACK  3
#define ENEMY_PISTOL_ELITE_GUARD_ANIM_DEATH         4
#define ENEMY_PISTOL_ELITE_GUARD_ANIM_DAMAGE		7

const int enemy_pistol_elite_guard_cur_life = 5;
const int enemy_pistol_elite_guard_sprite = 9;
// End Elite Guard - Piston

// Elite Guard - Rifle
#define ENEMY_RIFLE_ELITE_GUARD_ANIM_MOVE          6
#define ENEMY_RIFLE_ELITE_GUARD_ANIM_PISTOL_ATTACK 1
#define ENEMY_RIFLE_ELITE_GUARD_ANIM_RIFLE_ATTACK  2
#define ENEMY_RIFLE_ELITE_GUARD_ANIM_BATON_ATTACK  3
#define ENEMY_RIFLE_ELITE_GUARD_ANIM_DEATH         4
#define ENEMY_RIFLE_ELITE_GUARD_ANIM_DAMAGE		   7

const int enemy_rifle_elite_guard_cur_life = 5;
const int enemy_rifle_elite_guard_sprite = 8;
// End Elite Guard - Rifle

// Elite Guard - Baton
#define ENEMY_BATON_ELITE_GUARD_ANIM_MOVE          0
#define ENEMY_BATON_ELITE_GUARD_ANIM_PISTOL_ATTACK 1
#define ENEMY_BATON_ELITE_GUARD_ANIM_RIFLE_ATTACK  2
#define ENEMY_BATON_ELITE_GUARD_ANIM_BATON_ATTACK  3
#define ENEMY_BATON_ELITE_GUARD_ANIM_DEATH         4
#define ENEMY_BATON_ELITE_GUARD_ANIM_DAMAGE		   7

const int enemy_baton_elite_guard_cur_life = 3;
const int enemy_baton_elite_guard_sprite = 9;
// Elite Guard - Baton

// Global Parameters
const int enemy_ninja_height = 45;
const int enemy_ninja_width = 15;
const int enemy_ninja_render_offset = 9;
const int enemy_ninja_max_walk_velocity = 60;
const int enemy_ninja_walk_acceleration = 30;
const int enemy_elite_guard_render_offset =9;

const int enemy_prisoner_height = 45;
const int enemy_prisoner_width = 15;
const int enemy_prisoner_render_offset = 9;
const int enemy_prisoner_max_walk_velocity = 70;
const int enemy_prisoner_walk_acceleration = 40;
//****** END NINJAS *****//

//****** MINOR ENEMIES *****//

// Land Mines
#define ENEMY_LAND_MINE_ANIM_FLASH   0
#define ENEMY_LAND_MINE_ANIM_EXPLODE 1
// End Land Mines

// Flying Sentry A
#define ENEMY_FLYING_SENTRY_A_ANIM_MOVE  0
#define ENEMY_FLYING_SENTRY_A_ANIM_DEATH 1
// End Flying Sentry A

// Flying Sentry B
#define ENEMY_FLYING_SENTRY_B_ANIM_MOVE  0
#define ENEMY_FLYING_SENTRY_B_ANIM_DEATH 1
// End Flying Sentry B

// Enemy Tower Bot
#define ENEMY_TOWER_BOT_ANIM_UP        0
#define ENEMY_TOWER_BOT_ANIM_DEATH     1
#define ENEMY_TOWER_BOT_ANIM_MOVE_DOWN 2
#define ENEMY_TOWER_BOT_ANIM_MOVE_UP   3
#define ENEMY_TOWER_BOT_ANIM_DOWN      4
// End Enemy Tower Bot

// Water Mine
#define ENEMY_WATER_MINE_ANIM_FLASH 1
#define ENEMY_WATER_MINE_ANIM_DEATH 0
// End Water Mine

// Flame Thrower
#define ENEMY_FLAME_THROW 0
#define ENEMY_ELECTRIC_FIELD 0

//****** END MINOR ENEMIES ******//

//****** ENEMY BOSSES ******//
#define ENEMY_MR_THOMAS_ANIM_SPEED_PREP 0
#define ENEMY_MR_THOMAS_ANIM_SPEED_ATTACK 1
#define ENEMY_MR_THOMAS_ANIM_DEATH 2
#define ENEMY_MR_THOMAS_ANIM_TAUNT 3
#define ENEMY_MR_THOMAS_ANIM_SWORD_ATTACK 4
#define ENEMY_MR_THOMAS_ANIM_BREATH 5
#define ENEMY_MR_THOMAS_ANIM_WALK 6

const int enemy_mr_thomas_set_cur_life = 40;
const int enemy_mr_thomas_set_cur_life_bars = 8;

#define ENEMY_AGM_ANIM_BACK_SPIKE_0 0
#define ENEMY_AGM_ANIM_STAND 1
#define ENEMY_AGM_ANIM_ATTACK_CLAW 2
#define ENEMY_AGM_ANIM_BACK_SPIKE_1 3
#define ENEMY_AGM_ANIM_MOVE 4
#define ENEMY_AGM_ANIM_JUMP 5
#define ENEMY_AGM_ANIM_DEATH 6
 
#define ENEMY_AGM_ANIM_STAND2 0
#define ENEMY_AGM_ANIM_ATTACK_CLAW2 1
#define ENEMY_AGM_ANIM_MOVE2 2
#define ENEMY_AGM_ANIM_JUMP2 3
#define ENEMY_AGM_ANIM_DEATH2 4

#define ENEMY_GAWAIN_ANIM_TELEPORT_1 0
#define ENEMY_GAWAIN_ANIM_STAND      1
#define ENEMY_GAWAIN_ANIM_WALK       2
#define ENEMY_GAWAIN_ANIM_JUMP_1     3
#define ENEMY_GAWAIN_ANIM_ATTACK_1   4
#define ENEMY_GAWAIN_ANIM_ATTACK_2   5
#define ENEMY_GAWAIN_ANIM_TELEPORT_2 6
#define ENEMY_GAWAIN_ANIM_TELEPORT_3 7
#define ENEMY_GAWAIN_ANIM_ATTACK_3   8
#define ENEMY_GAWAIN_ANIM_ATTACK_4   9
#define ENEMY_GAWAIN_ANIM_DEATH      10

#define ENEMY_CRASH_ANIM_INTRO    0
#define ENEMY_CRASH_ANIM_STAND    1
#define ENEMY_CRASH_ANIM_WALK     2
#define ENEMY_CRASH_ANIM_ATTACK_1 3
#define ENEMY_CRASH_ANIM_ATTACK_2 4
#define ENEMY_CRASH_ANIM_ATTACK_3 5
#define ENEMY_CRASH_ANIM_ATTACK_4 6
#define ENEMY_CRASH_ANIM_JUMP     7
#define ENEMY_CRASH_ANIM_DAMAGE   8
#define ENEMY_CRASH_ANIM_DEATH    9  

#define ENEMY_JACOB_ANIM_STAND 0
#define ENEMY_JACOB_ANIM_CROUCH_TRANSITION 1
#define ENEMY_JACOB_ANIM_CROUCH 2
#define ENEMY_JACOB_ANIM_WALK 3
#define ENEMY_JACOB_ANIM_JUMP 4
#define ENEMY_JACOB_ANIM_ATTACK_0 5
#define ENEMY_JACOB_ANIM_QUAKE_ATTACK 6
#define ENEMY_JACOB_ANIM_INTRO 7
#define ENEMY_JACOB_ANIM_SPIKE 8
#define ENEMY_JACOB_ANIM_FLAME 9
#define ENEMY_JACOB_ANIM_QUAKE_2 10
#define ENEMY_JACOB_ANIM_DEATH 11


//****** END ENEMY BOSSES ******//

//******************************
//*** CHAPTER 2 ENEMIES ********
//******************************

//****** ENEMY MONSTERS ****** //
#define ENEMY_SMALL_MONSTER_JUMP 0
#define ENEMY_SMALL_MONSTER_STAND 0
#define ENEMY_SMALL_MONSTER_DEATH 0
const int enemy_gmonstersmall_height = 30;
const int enemy_gmonstersmall_width = 15;
const int enemy_gmonstersmall_render_offset = 9;
const int enemy_gmonstersmall_max_walk_velocity = 70;
const int enemy_gmonstersmall_walk_acceleration = 40;
const int enemy_gmonstersmall_cur_life = 10;

#define ENEMY_FIRE_MONSTER_ATTACK 0
#define ENEMY_FIRE_MONSTER_DEATH  1

#define ENEMY_SPIT_MONSTER_ATTACK 0
#define ENEMY_SPIT_MONSTER_DEATH  1

#define ENEMY_LARGE_MONSTER_STAND 0
#define ENEMY_LARGE_MONSTER_MOVE  1
#define ENEMY_LARGE_MONSTER_ROLL_PREP 2
#define ENEMY_LARGE_MONSTER_ROLL 3
#define ENEMY_LARGE_MONSTER_DEATH 4

//****** END ENEMY MONSTERS ****** //

//****** ENEMY LAB SCIENTIST ******//
#define ENEMY_LAB_SCIENTIST_MOVE       0
#define ENEMY_LAB_SCIENTIST_MOVE_FLAME 1
#define ENEMY_LAB_SCIENTIST_DEATH      2
#define ENEMY_LAB_SCIENTIST_ATTACK     3

const int enemy_lab_scientist_height = 45;
const int enemy_lab_scientist_width = 15;
const int enemy_lab_scientist_render_offset = 9;
const int enemy_lab_scientist_max_walk_velocity = 60;
const int enemy_lab_scientist_walk_acceleration = 30;
const int enemy_lab_scientist_cur_life = 6;
const int enemy_lab_scientist_cur_life_bars = 4;
//****** END LAB SCIENTIST ******//

//****** GENETIC MONSTERS ******//
#define ENEMY_G_MONSTER_SMALL_ANIM_JUMP 0
#define ENEMY_G_MONSTER_SMALL_ANIM_STAND 1
#define ENEMY_G_MONSTER_SMALL_ANIM_DEATH 2
//****** END GENETIC MONSTERS ******//

//****** PRISONERS *****//
#define ENEMY_PRISONER_ANIM_MOVE   0
#define ENEMY_PRISONER_ANIM_THROW  1
#define ENEMY_PRISONER_ANIM_PUNCH  2
#define ENEMY_PRISONER_ANIM_DEATH  3
#define ENEMY_PRISONER_ANIM_DAMAGE 4
const int enemy_prisoner_sprite = 10;
const int enemy_prisoner_cur_life = 5;

//****** END PRISONERS *****//


// ENEMY PRISONER - ZOMBIE
#define ENEMY_PRISONER_ZOMBIE_ANIM_MOVE   0
#define ENEMY_PRISONER_ZOMBIE_ANIM_ATTACK 1

const int enemy_prisoner_zombie_height = 45;
const int enemy_prisoner_zombie_width = 15;
const int enemy_prisoner_zombie_render_offset = 9;
const int enemy_prisoner_zombie_max_walk_velocity = 60;
const int enemy_prisoner_zombie_walk_acceleration = 30;
const int enemy_prisoner_zombie_cur_life = 3;
const int enemy_prisoner_zombie_cur_life_bars = 4;

//******************************
//*** CHAPTER 3 ENEMIES ********
//******************************

// ENEMY JUNKBOT - WALKING
#define ENEMY_JUNKBOT_WALKING_MOVE   0
#define ENEMY_JUNKBOT_WALKING_ATTACK 1
#define ENEMY_JUNKBOT_WALKING_DEATH  2

const int enemy_junkbot_walking_height = 45;
const int enemy_junkbot_walking_width = 15;
const int enemy_junkbot_walking_render_offset = 9;
const int enemy_junkbot_walking_max_walk_velocity = 60;
const int enemy_junkbot_walking_walk_acceleration = 30;
const int enemy_junkbot_walking_cur_life = 6;
const int enemy_junkbot_walking_cur_life_bars = 4;

// ENEMY JUNKBOT - FLYING
#define ENEMY_JUNKBOT_FLYING_MOVE   0
#define ENEMY_JUNKBOT_FLYING_DEATH  1

// ENEMY JUNKBOT - TRACK
#define ENEMY_JUNKBOT_TRACK_MOVE   0
#define ENEMY_JUNKBOT_TRACK_DEATH  1

const int enemy_junkbot_track_height = 45;
const int enemy_junkbot_track_width = 15;
const int enemy_junkbot_track_render_offset = 9;
const int enemy_junkbot_track_max_walk_velocity = 60;
const int enemy_junkbot_track_walk_acceleration = 30;
const int enemy_junkbot_track_cur_life = 6;
const int enemy_junkbot_track_cur_life_bars = 4;

// ENEMY JUNKBOT - LARGE
#define ENEMY_JUNKBOT_LARGE_STAND  0
#define ENEMY_JUNKBOT_LARGE_ATTACK 1
#define ENEMY_JUNKBOT_LARGE_DEATH  2

const int enemy_junkbot_large_height = 45;
const int enemy_junkbot_large_width = 15;
const int enemy_junkbot_large_render_offset = 9;
const int enemy_junkbot_large_max_walk_velocity = 60;
const int enemy_junkbot_large_walk_acceleration = 30;
const int enemy_junkbot_large_cur_life = 6;
const int enemy_junkbot_large_cur_life_bars = 4;

// ENEMY JUNKBOT - TOWER
#define ENEMY_JUNKBOT_FLYING_MOVE_UP   0
#define ENEMY_JUNKBOT_FLYING_MOVE_DOWN 1

// ENEMY BEAR
#define ENEMY_BEAR_STAND  0
#define ENEMY_BEAR_ATTACK 1
#define ENEMY_BEAR_DEATH  2

// ENEMY WOLF - BROWN
// ENEMY WOLF - GREY
#define ENEMY_WOLF_MOVE 0
#define ENEMY_WOLF_DEATH 1

// ENEMY BIRD - BROWN 
// ENEMY BIRD - GREEN
#define ENEMY_BIRD_STAND 0
#define ENEMY_BIRD_MOVE  1
#define ENEMY_BIRD_DEATH 2

// ENEMY JUNKBOT - WALKING - FOREST
// ENEMY JUNKBOT - FLYING - FOREST


//******************************
//*** CHAPTER 4 ENEMIES ********
//******************************

// ENEMY DOCK WORKER
#define ENEMY_DOCK_WORKER_ANIM_MOVE   0
#define ENEMY_DOCK_WORKER_ANIM_ATTACK 1
#define ENEMY_DOCK_WORKER_ANIM_DEATH  2

// ENEMY DOCK WORKER - ROPE
#define ENEMY_DOCK_WORKER_ROPE_ANIM_MOVE   0
#define ENEMY_DOCK_WORKER_ROPE_ANIM_ATTACK 1
#define ENEMY_DOCK_WORKER_ROPE_ANIM_DEATH  2

// ENEMY DOCK WORKER - WRECH THROW
#define ENEMY_DOCK_WORKER_WRECH_ANIM_ATTACK 0
#define ENEMY_DOCK_WORKER_WRECH_ANIM_DEATH  1

// ENEMY BASEBALL PUNK
#define ENEMY_BASEBALL_PUNK_ANIM_MOVE          0
#define ENEMY_BASEBALL_PUNK_ANIM_BATON_ATTACK  1
#define ENEMY_BASEBALL_PUNK_ANIM_DEATH         2

// ENEMY KNIFE PUNK
#define ENEMY_KNIFE_PUNK_ANIM_ATTACK 0
#define ENEMY_KNIFE_PUNK_ANIM_DEATH  1

// ENEMY MOHAWK PUNK
#define ENEMY_MOHAWK_PUNK_ANIM_MOVE   0
#define ENEMY_MOHAWK_PUNK_PUNCH  1
#define ENEMY_MOHAWK_PUNK_DEATH  2

// ENEMY PUNK
#define ENEMY_PUNK_ANIM_STAND 0
#define ENEMY_PUNK_ANIM_JUMP  1
#define ENEMY_PUNK_ANIM_DEATH 2

//const int enemy_baton_elite_guard_cur_life = 3;
//const int enemy_baton_elite_guard_sprite = 9;

//******************************
//*** CHAPTER 5 ENEMIES ********
//******************************

#endif
