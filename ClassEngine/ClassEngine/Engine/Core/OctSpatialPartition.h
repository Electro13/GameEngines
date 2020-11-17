#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"

#define CHILDREN_NUMBER 8

enum class OctChildren {
	OCT_TLF, // Top left corner in the front of the cube
	OCT_BLF, // Bottom left corner in the front of the cube
	OCT_BRF, // Bottom right corner in the front of the cube
	OCT_TRF, // Top right corner in the front of the cube
	OCT_TLR, // Top left corner in the back of the cube
	OCT_BLR, // Bottom left corner in the back of the cube
	OCT_BRR, // Bottom right corner in the back of the cube
	OCT_TRR // Top right corner in the back of the cube
};

class OctNode {
public:
	OctNode(glm::vec3 position_, float size_, OctNode* parent_);
	~OctNode();
	void OnDestroy();
	void Octify(int depth_); // create all children and once it finishes creating a child, it will call istelf with depth -1
	OctNode* GetParent();
	OctNode* GetChild(OctChildren childPos_);
	void AddCollisionObject(GameObject* obj_);
	int GetObjectCount() const;
	bool IsLeaf() const; // leaf nodes are any nodes that have no children
	BoundingBox* GetBoundingBox() const;
	int GetChildCount() const; // not necessary, just to check children
private:
	friend class OctSpatialPartition;
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[CHILDREN_NUMBER];
	std::vector<GameObject*> objectList;
	float size;
	static int childNum;	
};

class OctSpatialPartition {

public:
	OctSpatialPartition(float worldSize_);
	~OctSpatialPartition();
	void OnDestroy();
	void AddObject(GameObject* obj_);
	GameObject* GetCollision(Ray ray_);
private:
	OctNode* root;
	std::vector<OctNode*> rayIntersectionList;
	void AddObjectToCell(OctNode* cell_, GameObject* obj_);
	void PrepareCollisionQuery(OctNode* cell_, Ray ray_);
};
#endif
