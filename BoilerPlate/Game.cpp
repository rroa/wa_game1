#include "Game.hpp"
#include "Configuration.hpp"
#include "InputSystem.hpp"
#include <iostream>

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
			// TODO: RR: Let this leak, for now
			// TODO: RR: Make the destructor for the GO's add a nullptr value to allocs
			//if(entity != nullptr) delete entity;
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

		/*m_currentIndex++;
		if (m_currentIndex > (m_entities.size() - 1))
		{
			m_currentIndex = 0;
		}*/

		// Create the scene
		//
		m_scene = new Entities::Scene(
			Engine::Math::Vector3(0.1f, 0.1f, 0.15f),
			m_width,
			m_height
		);

		// TODO:: RR: Add the other objects here!
		m_scene->AddChild(m_ships[m_currentIndex]);
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

	}
}
