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
		CreateAsteroids(10);
	}

	void Game::Update(float delta) const
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
