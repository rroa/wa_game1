#if _MSC_VER && _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

// C++ STL
#include <cassert>
#include <iostream>

// 
#include "App.hpp"
#include "Utilities.hpp"
#include "TransformationComponent.hpp"
#include "RigidBodyComponent.hpp"
#include "GameObject.hpp"

const int WIDTH = 1136;
const int HEIGHT = 640;

class Test : public Engine::Core::GameObject
{
public:
	Test(int t)
	{
		test = t;
	}

	int GetTest() { return test; }
private:
	int test;
};

int main(int argc, char* argv[])
{
#if _MSC_VER && _DEBUG
	// https://msdn.microsoft.com/en-us/library/x98tx3cf.aspx
	// This will help you detect leaks when using Visual C++
	// Uncomment this line to start getting reports!
	assert(_CrtCheckMemory());
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Create App
	//
	Engine::App* app = new Engine::App("Boiler Plate!", WIDTH, HEIGHT);

	// Initialize app
	//
	if(!app->Init())
	{
		std::cout << "App Init error!\n";
		return -1;
	}

	// Execute game
	//
	app->Execute();

	// Delete game object
	//
	delete app;

	//Engine::Core::Scene* scene = new Engine::Core::Scene(Engine::Math::Vector3(1.0f, 1.0f, 1.0f), WIDTH, HEIGHT);
	//Test* parent = new Test(22);
	//Engine::Core::GameObject* go1 = new Engine::Core::GameObject();
	//Engine::Core::GameObject* go2 = new Engine::Core::GameObject();
	//Engine::Components::RigidBodyComponent* pc = new Engine::Components::RigidBodyComponent();
	//Engine::Components::TransformationComponent* tc = new Engine::Components::TransformationComponent();

	////scene->AddGameObject(go1);
	//parent->AddChild(go1);
	//parent->AddChild(go2);
	//go1->AttachComponent(pc);
	//go1->AttachComponent(tc);

	//Engine::Components::RigidBodyComponent* rt = go1->GetComponent<Engine::Components::RigidBodyComponent>();
	//assert(rt);
	//if (rt)
	//{
	//	std::cout << rt->GetName() << std::endl;
	//	std::cout << rt->GetMass() << std::endl;
	//	std::cout << go1->id << std::endl;
	//	std::cout << go2->id << std::endl;
	//}

	//Test* wo = dynamic_cast<Test*>(go1->GetParent());
	//assert(wo);
	//if(wo)
	//{
	//	std::cout << wo->GetTest() << std::endl;
	//}

	//std::cin.get();

	//delete parent;
	
	//delete scene;

	return 0;
}