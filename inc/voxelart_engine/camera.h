#ifndef VOXELART_CAMERA_H
#define VOXELART_CAMERA_H

#include "vector.h"

using namespace vaEngine;
namespace vaEngine {
	class Camera{
		public:
			Vector position;
			Vector lookAt;
			Vector upVector;
			Camera();
			virtual void lookThrough();
	};
}

#endif
