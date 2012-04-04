#include <iostream>
#include "../inc/PlayerBody.h"
/*
struct PlayerBody::bone {
	int x1,y1,z1,x2,y2,z2;
};*/

PlayerBody::Bone* PlayerBody::addBone(Bone* root, int x1, int y1, int z1, int x2, int y2, int z2) {
	Bone* child = new Bone();
	
	if(!root) {
		child->parent = NULL;
	}
	else {
		child->parent = root;
		root->childs.push_back(child);
	}
	
	child->x1 = x1;
	child->x2 = x2;
	child->y1 = y1;
	child->y2 = y2;
	child->z1 = z1;
	child->z2 = z2;

	return child;
}
