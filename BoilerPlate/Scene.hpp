#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>

//
#include "Vector3.hpp"
#include "IUpdate.hpp"
#include "IRender.hpp"
#include "GameObject.hpp"

namespace  Engine
{
	namespace Core
	{
		class Scene : public IUpdate, public IRender
		{
		public:
			/* =============================================================
			* CTOR
			* ============================================================= */
			Scene(Math::Vector3 background);
			~Scene();

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void Update(float deltaTime) override;
			void Render() override;
			void AddGameObject(GameObject* go);
			void RemoveGameObject(GameObject* go);
		protected:
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			Math::Vector3 m_background;
			std::vector<GameObject*> m_gameObjects;

		};
	}
}

#endif // !_SCENE_H_