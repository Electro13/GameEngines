#include "../../../Engine/Core/CoreEngine.h"
#include "../../../Game/Game1.h"
#include "../../../Resources/rapidxml.hpp"

int main(int argc, char* argv[]) {
	CoreEngine::GetInstance()->SetGameInterface(new Game1);

	if (!CoreEngine::GetInstance()->OnCreate("GAME258 Engine", 900, 700)) {
		std::cout << "Engine failed to be created" << std::endl;
		return 0;
	}

	std::ifstream file("./Engine/Engine.xml");
	rapidxml::xml_document <> doc;
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	rapidxml::xml_node <>* root = doc.first_node();
	int id = atoi(root->first_node("person")->first_attribute("id")->value());
	std::string title = root->first_node("person")->first_node("name")->first_node("GameTitle")->value();
	std::string groupMembers = root->first_node("person")->first_node("name")->first_node("groupMembers")->value();
	std::string Engine = root->first_node("person")->first_node("name")->first_node("Engine")->value();
	std::string Roles = root->first_node("person")->first_node("name")->first_node("Roles")->value();

	std::cout << title << std::endl;
	std::cout << groupMembers << std::endl;
	std::cout << Engine << std::endl;
	std::cout << Roles << std::endl;

	CoreEngine::GetInstance()->Run();
	
	return 0;
}