#include "GameScene.h"
#include "../../Engine/Rendering/3D/PhysicsComponent.h"
#include "../../Engine/Rendering/3D/GUIImageComponent.h"

GameScene::GameScene() : Scene() {

}

GameScene::~GameScene() {
	SceneGraph::GetInstance()->OnDestroy();
}

bool GameScene::OnCreate() {
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(3.0f, -1.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSources(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 0.5f));
	AudioHandler::GetInstance()->Initialize(CoreEngine::GetInstance()->GetCamera()->GetPosition(), glm::vec3(0), CoreEngine::GetInstance()->GetCamera()->GetForward(), CoreEngine::GetInstance()->GetCamera()->GetUp());
	emitter = new Emitter(100, "ParticleShader");
	//const AudioSource* audio = new AudioSource("Resources/OOF.mp3", true, false, true);

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	Model* model = new Model("./Resources/Models/Apple.obj",
		"./Resources/Materials/Apple.mtl", 
		ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model);

	Model* model1 = new Model("./Resources/Models/Dice.obj",
		"./Resources/Materials/Dice.mtl",
		ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model1);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(model1));

	GameObject* apple = new GameObject(model, glm::vec3(3.0f, -1.0f, 0.0f));
	apple->SetScale(glm::vec3(0.5f));
	apple->AddComponent<AudioSource>("OOF.mp3", false, false, true);
	apple->AddComponent<PhysicsComponent>();
	SceneGraph::GetInstance()->AddGameObject(apple, "apple");

	GUIObject* object = new GUIObject(glm::vec2(CoreEngine::GetInstance()->GetWindowSize().x / 2.0f, CoreEngine::GetInstance()->GetWindowSize().y / 2.0f));
	object->AddComponent<GUIImageComponent>();
	object->GetComponent<GUIImageComponent>()->OnCreate("WoodArrow");
	
	/*GUIImageComponent* imageComponent = object->GetComponent<GUIImageComponent>();
	if (imageComponent) {
		imageComponent->OnCreate("CheckerboardTexture");
	}*/
	SceneGraph::GetInstance()->AddGUIObject(object, "GUI");

	return true;
}

void GameScene::Update(const float deltaTime_) {
	SceneGraph::GetInstance()->Update(deltaTime_);
	AudioHandler::GetInstance()->Update();
	emitter->Update(deltaTime_);
}

void GameScene::Render() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	CoreEngine::GetInstance()->GetCamera()->GetFrustum();
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
	emitter->Render(CoreEngine::GetInstance()->GetCamera());
}

void GameScene::Draw() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//SceneGraph::GetInstance()->Draw(CoreEngine::GetInstance()->GetCamera()); GUI Image Draw Function
}
