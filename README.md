# Obstacle Avoidance

This is a dynamic obstacle avoidance library for AI navigation. Obstacles can be placed, moved, and resized in real-time and the AI will respond immediately to the changing environment.
Unlike A\*, it doesn't require lots of time and processing power; however, also not like A\* it does not find the optimal path.
Useful to use in conjunction with A\* when moving collidable objects unexpectedly block the AI's path during normal A\* navigation.
It works by using attractors and repellers. The goal node attracts the AI, creating a force vector from the AI to the goal. The obstacles repel the AI, creating force vectors pointing away from them. The closer the AI is to the obstacle, the larger the force vector. Then all forces are added together and normalized to get the direction that the AI will travel. The AI will also detect if it is not making progress and will mark the locations where it got stuck so that it will stay away from those places in future. It creates internal invisible obstacles that repel it from those locations where it got stuck as if there were obstacles there.

## Getting Started

This code was tested in Microsoft Visual Studio Community 2017. Open ObstacleAvoidance.sln and build with Obstacle Avoid Main as the startup project. It creates a Windows application. Double-click to create obstacles. Right-click and drag to resize obstacles. Left-click and drag to move any object.

## Points of Interest

* I implemented a lot of basic data structures that I use throughout the code. This was done as learning exercises for myself. In professional code, I would normally use the STL:
	* Dynamic Array
	* Hash Table
	* Linked List
	* Vector

* Note the approach I take to separate the platform-specific logic from the platform-independent. For example, Window is a platform independent representation of a window. It has a pointer to a window implementation, which handles the platform-specific implementation details of a window. This platform-specific implementation can be swapped out simply by linking in a different platform-specific library.

* This code includes a messaging system to allow different parts of the engine to communicate while keeping implementation details hidden. A common problem with messaging systems is that a single message may get sent to many listeners and one of those listeners may end up causing another listener to be destroyed. Then when the messaging system tries to send a message to the destroyed listener, the game crashes. My solution to this is to attach listeners to handles wich become invalidated when the listener is destroyed. The messaging system can then detect if the listener was destroyed before trying to send a message to it.

