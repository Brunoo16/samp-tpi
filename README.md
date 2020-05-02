# samp-tpi
TogglePlayerInvisibility - Make players invisible.

I deleted this repository previously, I'm just bringing it back. I won't be updating/maintaining this.

# Installation

Simply install to your project:

```sampctl package install BrunoBM16/samp-tpi```

# Functions
 
```pawn
TogglePlayerInvisibility(const playerid, bool:toggle);
bool:IsPlayerInvisible(const playerid);
```

# If you are willing to use this include:

* Invisible players won't send updates inside vehicles. This means, you won't see the vehicle being driven or so.
* Even though OnPlayerGiveDamage and OnPlayerWeaponShot are called by invisible players, they can't do any damage, unless you are using weapon-config.

Despite the above points, everything works as intended. Also, as said previously, this won't be updated anymore, so it is unlikely I will do anything about the points mentioned.
