#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() {
	currentMaterial = Material();
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel() {

}

void LoadOBJModel::LoadModel(const std::string& objFilePath_,
	const std::string& mtlFilePath_) {
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

void LoadOBJModel::LoadModel(const std::string& filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + filePath_,
			"LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;
	float tmpNum = 0;
	while (std::getline(in, line)) {
		//VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));

			if (tmpNum == 0) {
				box.minVert.x = x;
				box.minVert.y = y;
				box.minVert.z = z;
			}

			if (box.minVert.x > x) {
				box.minVert.x = x;
			}

			if (box.minVert.y > y) {
				box.minVert.y = y;
			}

			if (box.minVert.z > z) {
				box.minVert.z = z;
			}

			if (box.maxVert.x < x) {
				box.maxVert.x = x;
			}

			if (box.maxVert.y < y) {
				box.maxVert.y = y;
			}

			if (box.maxVert.z < z) {
				box.maxVert.z = z;
			}
			tmpNum = 1;
		}

		//NORMAL DATA
		else if (line.substr(0, 3) == "vn ")
		{
			std::stringstream vn(line.substr(2));
			//glm::vec3 normal;
			float x, y, z;
			vn >> x >> y >> z;
			normals.push_back(glm::vec3(x,y,z));
		}

		//Texture Data
		else if (line.substr(0, 3) == "vt ")
		{
			std::stringstream vt(line.substr(2));
			//glm::vec2 textureCoords;
			float x, y;
			vt >> x >> y;
			textureCoords.push_back(glm::vec2(x,y));
		}

		//FACE DATA
		else if (line.substr(0, 2) == "f ") {
			std::string data = line.substr(2);
			int currentEndPos = 0;
			while ((currentEndPos = data.find(' ')) != std::string::npos) {
				std::string chunk = data.substr(0, currentEndPos);
				int subEndPos = 0;
				int vector = 0;


				for (int i = 0; i < 3; i++) {
					int pushBack;
					if ((subEndPos = chunk.find('/')) != std::string::npos) {

						pushBack = std::stoi(chunk.substr(0, subEndPos));

						chunk.erase(0, subEndPos + 1);
					}
					else {
						pushBack = std::stoi(chunk);
					}

					pushBack--;

					switch (i) {
					default:
					case 0:
						indices.push_back(pushBack);
						break;
					case 1:
						textureIndices.push_back(pushBack);
						break;
					case 2:
						normalIndices.push_back(pushBack);
						break;
					}
				}
				vector = 0;
				data.erase(0, currentEndPos + 1);
			}
		}
		//NEW MESH
		else if (line.substr(0, 7) == "usemtl ") { 
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

std::vector<Vertex> LoadOBJModel::GetVerts() {
	return meshVertices;
}

std::vector<int> LoadOBJModel::GetIndices() {
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes() {
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() {
	return box;
}

void LoadOBJModel::OnDestroy() {
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::PostProcessing() {
	for (int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh subMesh;
	subMesh.vertexList = meshVertices;
	subMesh.meshIndices = indices;
	subMesh.material = currentMaterial;

	subMeshes.push_back(subMesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_) {
	MaterialLoader::LoadMaterial(matFilePath_);
}