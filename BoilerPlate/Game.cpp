#include "Game.hpp"
#include "Configuration.hpp"

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
			if(entity != nullptr) delete entity;
		}

		// Clear list
		//
		m_ships.clear();
	}

	void Game::Init()
	{
		// Loading models
		//
		Asteroids::Utilities::Configuration config;
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

	void Game::Update(float delta) const
	{
		m_scene->Update(delta);
	}

	void Game::Render() const
	{
		m_scene->Render();
	}

}
