#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels =
std::map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects =
std::map<std::string, GameObject*>();

SceneGraph::SceneGraph() {

}

SceneGraph::~SceneGraph() {

}

SceneGraph* SceneGraph::GetInstance() {
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}

void SceneGraph::OnDestroy() {
	if (sceneGameObjects.size() > 0) {
		for (auto go : sceneGameObjects) {
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}

	if (sceneModels.size() > 0) {
		for (auto entry : sceneModels) {
			if (entry.second.size() > 0) {
				for (auto m : entry.second) {
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
	}
}

void SceneGraph::AddModel(Model* model_) {
	if (sceneModels.find(model_->GetShaderProgram()) == sceneModels.end()) {
		std::vector<Model*> tmp = std::vector<Model*>();
		tmp.reserve(10);
		tmp.push_back(model_);
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(
			model_->GetShaderProgram(), tmp));
	}
	else {
		sceneModels[model_->GetShaderProgram()].push_back(model_);
	}
}

void SceneGraph::AddGameObject(GameObject* go_, std::string tag_) {
	if (tag_ == "") {
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) {
		go_->SetTag(tag_);
		sceneGameObjects[tag_] = go_;
	}
	else {
		Debug::Error("Trying to add a GameObject with a tag " + tag_ +
			" that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	CollisionHandler::GetInstance()->AddObject(go_);
}

GameObject* SceneGraph::GetGameObject(std::string tag_) {
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) {
		return sceneGameObjects[tag_];
	}
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_) {
	for (auto go : sceneGameObjects) {
		go.second->SetRotation(glm::vec3(0.0f, 5.0f, 0.0f));
		go.second->Update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_) {
	for (auto entry : sceneModels) {
		glUseProgram(entry.first);
		for (auto m : entry.second) {
			if (!ObjectIsCulled(m->GetPosition())) {
				m->Render(camera_);
			}
			else {
				// If the object is outside the frustum, it will keep printing this message until it's back
				// inside the frustum
				std::cout << "Object is not rendered" << std::endl;
			}
			
		}
	}
}

// This function will check and see if the object is inside of the frustum. Otherwise, It will return false
bool SceneGraph::ObjectIsCulled(glm::vec3 point_) {
	if (CoreEngine::GetInstance()->GetCamera()->front.x * point_.x +
		CoreEngine::GetInstance()->GetCamera()->front.y * point_.y +
		CoreEngine::GetInstance()->GetCamera()->front.z * point_.z +
		CoreEngine::GetInstance()->GetCamera()->front.w <= 0.0f) {
		return true;
	}

	if (CoreEngine::GetInstance()->GetCamera()->back.x * point_.x +
		CoreEngine::GetInstance()->GetCamera()->back.y * point_.y +
		CoreEngine::GetInstance()->GetCamera()->back.z * point_.z +
		CoreEngine::GetInstance()->GetCamera()->back.w <= 0.0f) {
		return true;
	}

	if (CoreEngine::GetInstance()->GetCamera()->top.x * point_.x +
		CoreEngine::GetInstance()->GetCamera()->top.y * point_.y +
		CoreEngine::GetInstance()->GetCamera()->top.z * point_.z +
		CoreEngine::GetInstance()->GetCamera()->top.w <= 0.0f) {
		return true;
	}

	if (CoreEngine::GetInstance()->GetCamera()->bottom.x * point_.x +
		CoreEngine::GetInstance()->GetCamera()->bottom.y * point_.y +
		CoreEngine::GetInstance()->GetCamera()->bottom.z * point_.z +
		CoreEngine::GetInstance()->GetCamera()->bottom.w <= 0.0f) {
		return true;
	}

	if (CoreEngine::GetInstance()->GetCamera()->left.x * point_.x +
		CoreEngine::GetInstance()->GetCamera()->left.y * point_.y +
		CoreEngine::GetInstance()->GetCamera()->left.z * point_.z +
		CoreEngine::GetInstance()->GetCamera()->left.w <= 0.0f) {
		return true;
	}

	if (CoreEngine::GetInstance()->GetCamera()->otherLeft.x * point_.x +
		CoreEngine::GetInstance()->GetCamera()->otherLeft.y * point_.y +
		CoreEngine::GetInstance()->GetCamera()->otherLeft.z * point_.z +
		CoreEngine::GetInstance()->GetCamera()->otherLeft.w <= 0.0f) {
		return true;
	}
	// If we get here, the object isn't in the frustum
	return false;
}