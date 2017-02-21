#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include "Scene.hpp"
#include "Ship.hpp"

namespace Asteroids
{
	class Game
	{
	public:
		/* =============================================================
		* CTOR
		* ============================================================= */
		Game(int width, int height);
		~Game();

		/* =============================================================
		* PUBLIC FUNCTIONS
		* ============================================================= */
		void Init();
		void Update(float delta) const;
		void Render() const;
	private:
		/* =============================================================
		* PRIVATE FUNCTIONS
		* ============================================================= */
		void HandleInput() const;
		void CreatePlayer();
		void CreateAsteroids(int amount) const;

		/* =============================================================
		* MEMBERS
		* ============================================================= */
		Entities::Scene* m_scene;
		int m_width;
		int m_height;		
		Entities::Ship* m_player;
		std::vector<Entities::Ship*> m_ships;
	};
}

#endif /* _GAME_H_ */