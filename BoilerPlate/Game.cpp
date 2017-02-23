#include "Game.hpp"

//
#include <iostream>

//
#include "Configuration.hpp"
#include "InputManager.hpp"
#include "Asteroid.hpp"

namespace Asteroids
{
	Game::Game(int width, int height)
		: m_scene(nullptr)
		, m_width(width)
		, m_height(height)
		, m_player(nullptr)
	{}

	Game::~Game()
	{
		// Destroy the scene
		//
		delete m_scene;

		// Clear list
		//
		m_ships.clear();
	}

	void Game::Init()
	{
		// Create the scene
		//
		m_scene = new Entities::Scene(
			Engine::Math::Vector3(0.1f, 0.1f, 0.15f),
			m_width,
			m_height
		);

		// Adding the player (ship)
		//
		CreatePlayer();

		// Adding the enemies (asteroids)
		//
		CreateAsteroids(1, Entities::Asteroid::AsteroidSize::BIG);
	}

	void Game::Update(float delta) const
	{
		// Handle Input
		//
		HandleInput();

		// Update the scene
		//
		m_scene->Update(delta);

		// Look for collisions
		//
		CheckCollisions();
	}

	void Game::Render() const
	{
		// Render the game
		//
		m_scene->Render();
	}

	void Game::HandleInput() const
	{
		if (Engine::Input::InputManager::Instance().IsKeyPressed('w'))
		{
			m_player->MoveUp();
		}

		if (Engine::Input::InputManager::Instance().IsKeyPressed('a'))
		{
			m_player->MoveLeft();
		}

		if (Engine::Input::InputManager::Instance().IsKeyPressed('d'))
		{
			m_player->MoveRight();
		}

		if (Engine::Input::InputManager::Instance().IsKeyReleased('p'))
		{
			m_player->ChangeShip();
		}
	}

	void Game::CreatePlayer()
	{
		// Loading models
		//
		Utilities::Configuration config;
		m_player = new Entities::Ship(config.LoadModels());

		// Adding the player (ship)
		//		
		m_scene->AddChild(m_player);
	}

	void Game::CreateAsteroids(int amount, Entities::Asteroid::AsteroidSize::Size size) const
	{
		for (int i = 0; i < amount; ++i)
		{
			// Create new Asteroid
			Entities::Asteroid* pAsteroid =
				new Entities::Asteroid(size);

			// Add asteroid to the scene
			//
			m_scene->AddChild(pAsteroid);

			// Apply random translation to the new asteroid
			//
			pAsteroid->ApplyRandomTranslation();
		}
	}

	void Game::CreateDebris(Entities::Asteroid::AsteroidSize::Size previousSize) const
	{
		if(previousSize == Entities::Asteroid::AsteroidSize::BIG)
		{
			CreateAsteroids(2, Entities::Asteroid::AsteroidSize::MEDIUM);
		}

		if (previousSize == Entities::Asteroid::AsteroidSize::MEDIUM)
		{
			CreateAsteroids(2, Entities::Asteroid::AsteroidSize::SMALL);
		}
	}

	void Game::CheckCollisions() const
	{
		if (!m_player->CanCollide()) return;

		for(auto a :  m_scene->GetChildren())
		{
			Entities::Asteroid* pAsteroid = dynamic_cast<Entities::Asteroid*>(a);
			if (pAsteroid)
			{
				if(m_player->IsColliding(pAsteroid))
				{
					// Retrieve current size
					//
					Entities::Asteroid::AsteroidSize::Size currentSize = pAsteroid->GetSize();
					
					// Remove from scene
					//
					m_scene->RemoveChild(a);

					// Create debris
					//
					CreateDebris(currentSize);

					//
					m_player->Respawn();
				}
			}
		}

		/* =============================================================
		* ENUMERATORS
		* ============================================================= */
		/*struct EntityState
		{
			enum State
			{
				NORMAL = 0,
				COLLIDED = 1,
				DELETED = 2,
			};
		};*/
		//inline bool CouldCollide    ( ) { return m_state == EntityState::State::NORMAL; }
		/*for (std::list< Asteroids::Asteroid* >::iterator asteroid = m_asteroids.begin(); asteroid != m_asteroids.end(); ++asteroid)
		{
			if ((*asteroid)->CouldCollide() && m_player->CouldCollide())
			{
				if (m_player->DetectCollision((*asteroid)))
				{
					CreateDebris((*asteroid));
				}

				for (std::list< Asteroids::Bullet* >::iterator bullet = m_bullets.begin(); bullet != m_bullets.end(); ++bullet)
				{
					if ((*bullet)->CouldCollide() && (*asteroid)->CouldCollide())
					{
						if ((*asteroid)->DetectCollision((*bullet)))
						{
							UpdateScore(10);
							CreateDebris((*asteroid));
						}
					}
				}
			}
		}*/
	}
}
