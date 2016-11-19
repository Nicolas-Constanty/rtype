# Weapons
| Weapon | Direction | Type | Transperce | Comment |
|:-:|:-:|:-:|:-:|:-:|
| Basic | straight line | simple | true (loaded) | loading => powerful shot |
| Laser | bouncing | triple | false | 3 lasers -45°, 0°, 45° |
| Spirals | straight line | propeller | true | |
| Fireballs | lick the walls | double (top, bottom) | true | 2 x 6 fireballs |

> - The basic weapon shot at the same time as temporary weapons.
> - The loaded shot remains the same.
> - When a new weapon is take, it replace the other.

# Bonus
> Bonus are cumulative

| Object | Type | Comment |
|:-:|:-:|:-:|:-:|
| Missiles | weapon | target-tracking (other button) |
| Protective ball | guard | 2 max (top / bototm), indestructible |
| Speed Bonus | bonus | 4 times cumulative |


# Nacelle
- Obtaining
    - with first tempory weapon
    - raise with tempory weapon (2 = max)
- Property
    - Weapon
    - Guard
    - Indestructible
    - Stop firing enemies
- Actions
    - Touch ennemi => it explodes (except the coriaces)
    - cling to front or back
    - eject from spaceship and throw on ennemis => can't use tempory weapon

> #### All items are recovered on monsters except the Nacelle that arrive at the same time as the first temporary weapon.
> #### :warning: Only the Nacelle can be launched, ejected, ...

# Ennemis
> Some enemies are indestructible

# Sounds
## Weapons
| Weapon | Take | Fire | Touch Ennemi | Comment |
|:-:|:-:|:-:|:-:|:-:|
| Basic | None | fire_basic | touch_basic | None |
| Basic Loaded | None | fire_basic_loaded | touch_basic_loaded | None |
| Laser | take_laser | fire_laser | touch_laser | None |
| Spirals | take_spirals | fire_spirals | touch_spirals | None |
| Fireballs | take_fireballs | fire_fireballs | touch_fireballs | None |

## Monster
| Action | Sound | Comment |
|:-:|:-:|:-:|
| Fire | fire\_monster\_{{name}} | None |
| Touched | touched\_monster\_{{name}} | None |
| Explosed | explosed\_monster\_{{name}} | None |

## Player
| Action | Sound | Comment |
|:-:|:-:|:-:|
| Touched | touched_player | None |
| Explosed | explosed_player | None |

## Bonus
| Object | Take | Launch | Touch Ennemi | Comment |
|:-:|:-:|:-:|:-:|
| Missiles | take_missiles | launch_missiles | touch_missiles | None |
| Protective ball | take_protective_ball | None | touched_protective_ball | None |
| Speed Bonus | take_speed | None | None | None |

## Nacelle
| Action | Sound | Comment |
|:-:|:-:|:-:|
| Fire | fire_nacelle | None |
| Upgraded | upgraded_nacelle | None |
| Touched | touched_nacelle | None |
| Ejected | ejected_nacelle | None |
| Launched | launched_nacelle | None |
