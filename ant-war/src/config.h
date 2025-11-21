#pragma once

struct Config{
      // Mode
	 static constexpr bool cible_MODE = true;

     // window
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        // Boid
		static constexpr int NUM_BOIDS = 100;  // number of boids
        static constexpr float BOID_SIZE = 8.0f;  
        static constexpr float MAX_SPEED = 4.0f;

		// weights for boid rules
        static constexpr float K_COHESION = 0.01f; 
        static constexpr float K_ALIGNMENT = 0.2f;
        static constexpr float K_SEPARATION = 0.7f;
        static constexpr float K_TARGET = 0.9f;

		// distance thresholds
		static constexpr float NEIGHBOR_RADIUS = 100.0f; 
		static constexpr float SEPARATION_RADIUS = 23.0f;  // si dis(A, b) < SEPARATION_RADIUS, alors force de s¨¦paration s'applique

        // Target:  nid 
		static  float TARGET_X;  //default = 100.0f;
        static  float TARGET_Y ; //default = 100.0f;
		static constexpr float NID_SIZE = 200.0f;
		static constexpr bool DRAG_NID = false; // if true, user can drag the nid with mouse


};