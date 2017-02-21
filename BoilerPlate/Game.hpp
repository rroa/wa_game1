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
		void Update(float delta);
		void Render() const;
	private:
		/* =============================================================
		* PRIVATE FUNCTIONS
		* ============================================================= */
		void HandleInput();
		void CreateAsteroids(int amount) const;

		/* =============================================================
		* MEMBERS
		* ============================================================= */
		Entities::Scene* m_scene;
		int m_width;
		int m_height;
		int	m_currentIndex;
		Entities::Ship* m_currentShip;
		std::vector<Entities::Ship*> m_ships;
	};
}

#endif /* _GAME_H_ */