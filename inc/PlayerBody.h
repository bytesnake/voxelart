#ifndef PlayerBody_H
#define PlayerBody_H

#include <iostream>
#include <vector>

class PlayerBody 
{
	private:
	struct Bone {
		int x1,y1,z1,x2,y2,z2;
		std::vector<Bone*> childs;
		Bone* parent;
	
	};	

	public:
	Bone* addBone(Bone* root, int x1, int y1, int z1, int x2, int y2, int z2);
	
			
};
#endif
