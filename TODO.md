To add:
Onscreen timer - Time is kept track of in seperate timer thread
Ignore 180 degree direction change - Don't let them move down if they where moving up as they will crash into themselves

Bugs:
Fruit sometimes doesn't appear on screen. Might not be drawn or drawn off screen


Misc:
Code in detectSnakeCollision can be optimised - Iterates through the linked list twice
Move fruit to its own class which shares only some methods with the snake class.

