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

Multiple types of collision can be tracked by our game, including player-to-player and player to boundaries.

_Menu_

Any keystroke on the splash screen will lead to the menu, where the user can choose between starting a single-player game, joining an online multiplayer game or exiting.

_Particles_

Game Box Online decided to keep the smoke trail feature that Ubisoft's API came with. It gives our ninjas an effervescent touch.

# Features

_Health Status Bar_

A health status bar depletes fractionally as players and enemies receive damage.

_Shuriken Projectiles_

All players in the game emit shurikens as their basic attack. 

_Goose Bomb Emitter_

The Goose Bomb Emitter is an attack that deals greater damage than simple shurikens in the form of a rotating goose. The player uses Spacebar to send a Goose which directs at the closest enemy in proximity. The Goose Bomb Emitter has a timed cooldown.

_Simple AI_

In the game's single-player mode, programmatically generated enemies attack toward the player.

