#include "Game.hpp"

//
#include <iostream>

//
#include "Configuration.hpp"
#include "InputSystem.hpp"
#include "Asteroid.hpp"

namespace Engine {namespace Systems {
	class InputSystem;
}
}

namespace Asteroids
{
	Game::Game(int width, int height)
		: m_scene(nullptr)
		, m_width(width)
		, m_height(height)
		, m_currentIndex(0)
		, m_currentShip(nullptr)
	{}

	Game::~Game()
	{
		// Destroy the scene
		//
		delete m_scene;

		// Delete models
		//
		for (auto entity : m_ships)
		{
			//
			if (entity->id == m_currentShip->id) continue;
			
			delete entity;
		}

		// Clear list
		//
		m_ships.clear();
	}

	void Game::Init()
	{
		// Loading models
		//
		Utilities::Configuration config;
		m_ships = config.LoadModels();
		m_currentShip = m_ships[m_currentIndex];

		// Create the scene
		//
		m_scene = new Entities::Scene(
			Engine::Math::Vector3(0.1f, 0.1f, 0.15f),
			m_width,
			m_height
		);

		// Adding the player (ship)
		//		
		m_scene->AddChild(m_currentShip);
		
		// Adding the enemies (asteroids)
		//
		CreateAsteroids(10);
	}

	void Game::Update(float delta)
	{
		// Handle Input
		//
		HandleInput();

		// Update the scene
		//
		m_scene->Update(delta);
	}

	void Game::Render() const
	{
		// Render the game
		//
		m_scene->Render();
	}

	void Game::HandleInput()
	{
		if (Engine::Systems::InputSystem::Instance().IsKeyDown('w'))
		{
			m_ships[m_currentIndex]->MoveUp();
		}

		if (Engine::Systems::InputSystem::Instance().IsKeyDown('a'))
		{
			m_ships[m_currentIndex]->MoveLeft();
		}

		if (Engine::Systems::InputSystem::Instance().IsKeyDown('d'))
		{
			m_ships[m_currentIndex]->MoveRight();
		}

		if (Engine::Systems::InputSystem::Instance().IsKeyDown('p'))
		{
			m_currentIndex++;
			if (m_currentIndex > (m_ships.size() - 1))
			{
				m_currentIndex = 0;
			}

			// Point to the new ship
			//
			/*m_scene->RemoveChild(m_currentShip);
			m_currentShip = m_ships[m_currentIndex];
			m_scene->AddChild(m_currentShip);*/

			std::cout << "Current Id " << m_currentShip->id << std::endl;
			std::cout << "Current Index " << m_currentIndex << std::endl;
		}
	}
	void Game::CreateAsteroids(int amount) const
	{
		for (int i = 0; i < amount; ++i)
		{
			// Create new Asteroid
			Entities::Asteroid* pAsteroid = 
				new Entities::Asteroid(Entities::Asteroid::AsteroidSize::BIG);

			// Add asteroid to the scene
			//
			m_scene->AddChild(pAsteroid);

			// Apply random translation to the new asteroid
			//
			pAsteroid->ApplyRandomTranslation();
		}
	}
}
