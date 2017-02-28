#include "Game.hpp"

//
#include <iostream>
#include <algorithm>

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
		m_bullets.clear();
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
		CreateAsteroids(10, Entities::Asteroid::AsteroidSize::BIG);
	}

	void Game::Update(double deltaTime)
	{
		// Handle Input
		//
		HandleInput();

		// Update the scene
		//
		m_scene->Update(deltaTime);

		// Look for collisions
		//
		CheckCollisions();

		// Clean up dead bullets
		//
		CleanDeadUpBullets();
	}

	void Game::Render() const
	{
		// Render the game
		//
		m_scene->Render();
	}

	void Game::HandleInput()
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

		if (Engine::Input::InputManager::Instance().IsKeyReleased(' '))
		{
			// If ship is respawning ignore shoot command
			//
			if (m_player->IsRespawning()) return;

			// Shoot!
			//
			Entities::Bullet* pBullet = m_player->Shoot();

			// Store bullets in linked list
			//
			m_bullets.push_back(pBullet);

			// Add bullet to the scene
			//
			m_scene->AddChild(pBullet);
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

	void Game::CreateAsteroids(int amount, Entities::Asteroid::AsteroidSize::Size size, Engine::Math::Vector2 position) const
	{
		for (int i = 0; i < amount; ++i)
		{
			// Create new Asteroid
			Entities::Asteroid* pAsteroid =
				new Entities::Asteroid(size, position);

			// Add asteroid to the scene
			//
			m_scene->AddChild(pAsteroid);

			// If set on origin then move randomly around the 'world'
			if (position == Engine::Math::Vector2::Origin)
			{
				pAsteroid->ApplyRandomTranslation();
			}
		}
	}

	void Game::CreateDebris(Entities::Asteroid* currentAsteroid) const
	{
		// Retrieve current size
		//
		Entities::Asteroid::AsteroidSize::Size currentSize = currentAsteroid->GetSize();

		// Create resulting asteroids from collision depending on current asteroid size
		//
		if(currentSize == Entities::Asteroid::AsteroidSize::BIG)
		{
			CreateAsteroids(2, Entities::Asteroid::AsteroidSize::MEDIUM, currentAsteroid->GetPosition());
		}

		if (currentSize == Entities::Asteroid::AsteroidSize::MEDIUM)
		{
			CreateAsteroids(2, Entities::Asteroid::AsteroidSize::SMALL, currentAsteroid->GetPosition());
		}

		// Remove from scene
		//
		m_scene->RemoveChild(currentAsteroid);
	}

	void Game::CleanDeadUpBullets()
	{
		if (m_bullets.size() == 0) return;

		// Destroy one per update
		//
		auto iter = std::find_if(m_bullets.begin(), m_bullets.end(),
			[&](Entities::Bullet* bullet) { return bullet->ShouldBeDeleted() || bullet->IsColliding(); });
		if (iter != m_bullets.end())
		{
			DestroyBullet(*iter);
		}
	}

	void Game::CheckCollisions()
	{
		if (!m_player->CanCollide()) return;

		for(auto a :  m_scene->GetChildren())
		{
			Entities::Asteroid* pAsteroid = dynamic_cast<Entities::Asteroid*>(a);
			if (pAsteroid)
			{
				CheckCollisionWithPlayer(pAsteroid);
				CheckCollisionWithBullets(pAsteroid);
			}
		}
	}

	void Game::CheckCollisionWithPlayer(Entities::Asteroid * pAsteroid) const
	{
		if (m_player->IntersectsWith(pAsteroid))
		{
			// Create debris
			//
			CreateDebris(pAsteroid);

			//
			m_player->Respawn();
		}
	}

	void Game::CheckCollisionWithBullets(Entities::Asteroid * pAsteroid)
	{
		for(auto bullet : m_bullets)
		{
			if(bullet->IntersectsWith(pAsteroid))
			{
				// Create debris
				//
				CreateDebris(pAsteroid);
			}
		}
	}

	void Game::DestroyBullet(Entities::Bullet * bulletToDestroy)
	{
		// Remove bullet from the scene
		//
		m_scene->RemoveChild(bulletToDestroy);

		// Remove bullet from list
		//
		auto bulletResult = find(m_bullets.begin(), m_bullets.end(), bulletToDestroy);
		if (m_bullets.size() > 0 && bulletResult != m_bullets.end())
		{
			m_bullets.erase(bulletResult);
		}
	}
}
