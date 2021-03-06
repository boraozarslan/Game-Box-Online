# Game-Box-Online
This game was built using the Ubisoft Hackers Nest API.

# Networking Layer
Game Box Online can be played on offline single-player or online multi-player, thanks to our in-house networking layer.

# Components

_Movement_

Use arrow keys to move around and W A S D to shoot.

_Camera_

We utilized the Ubisoft API's camera system to follow the main player.

_Collision_

Multiple types of collision can be tracked by our game, including player-to-player, player-to-projectiles and player-to-boundaries.

_Menu_

Any keystroke on the splash screen will lead to the menu, where the user can choose between starting a single-player game, joining an online multiplayer game or exiting.

_Particles_

Game Box Online decided to keep the smoke trail feature that Ubisoft's API came with. It gives our ninjas an effervescent touch. Similar logic to particles were used to implement projectiles.

# Features

_Health Status Bar_

A health status bar depletes fractionally as players and enemies receive damage.

_Shuriken Projectiles_

All players in the game emit shurikens as their basic attack. The single-player mode gives the player a different Shuriken base attack versus the computer-controlled ninjas.

_Goose Bomb Emitter_

The Goose Bomb Emitter is an attack that deals greater damage than simple shurikens in the form of a goose. The player uses Spacebar to send a Goose which directs at the closest enemy in proximity. The Goose Bomb Emitter has a timed cooldown as well as a greater projectile lifespan (how long it stays rendered) than regular shurikens.

_Score Keeping_

Score is kept at the bottom-right of the screen and updates dynamically as the player accumulates knock-outs on the enemy ninjas.

_Simple AI_

In the game's single-player mode, programmatically generated enemies which spawn in random places on the map attack toward the player. They also have the ability to hurt each other.

_Simple Fog of War_

There is the preliminary workings of a fog of war - a safe area of the map where the players do not take damage over time. Currently, a shrinking circle is spawned on the map. In the future, damage to players outside of the circle can be added.

# Challenges

_Development Setup_

The out-of-the-box API on Mac OS did not work. Unfortunately, all of our team members were on Mac laptops. We had to spend some time to manipulate project set-up code (like packages) to enable SFML and the API on Mac (specifically Xcode).

_Networking_

The additional networking layer we added provided a lot of challenge, as it was difficult to coordinate the updating of clients and hosts to sync game data with no built-in support from the API.

_Adding and Removing Entities_

We had lots of different logic that prompted entities to be added and removed in the game. The out-of-the-box API staggered these requests, resulting in some conflicts when multiple behaviours of an Entity request the same remove entity action. We addressed this by adding more robust guards to the removal process.

_Ideation_

Unfortunately, our team was made only a day before the competition started so we had little time to brainstorm ideas. To counteract this, we spent some of the first few hours of the Hackathon to flesh out an idea, as well as designate tasks.
