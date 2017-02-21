#pragma once

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <vector>

//
#include "IUpdate.hpp"
#include "IRender.hpp"
#include "UniqueID.hpp"

namespace Engine
{
	namespace Core
	{
		class Component;
		class Scene;
		class GameObject : public IUpdate, public IRender, public UniqueID
		{
		public:
			/* =============================================================
			* CTOR FUNCTIONS
			* ============================================================= */
			GameObject();
			~GameObject();

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void AttachComponent(Component*);
			void RemoveComponent(Component*);
			void AddChild(GameObject*);
			void RemoveChild(GameObject*);
			void Update(float deltaTime) override;
			void Render() override;

			/* =============================================================
			* GETTER FUNCTIONS
			* ============================================================= */
			std::vector<Component*>GetComponents() const { return m_components; }

			template<typename T>
			T* GetComponent()
			{
				std::vector< Component* >::iterator comp = m_components.begin();
				for (; comp != m_components.end(); ++comp)
				{
					T* theComponent = dynamic_cast<T*>(*comp);
					if (theComponent)
					{
						return theComponent;
					}
				}

				return nullptr;
			}
		protected:
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			std::vector<Component*>	m_components;
			Scene* m_scene;
			std::vector<GameObject*> m_children;
		};
	}
}

#endif // !_GAMEOBJECT_H_