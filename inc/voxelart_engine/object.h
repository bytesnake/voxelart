#ifndef VOXELART_OBJECT_H
#define VOXELART_OBJECT_H

#include "vector.h"

using namespace vaEngine;
namespace vaEngine {
	class Object
	{
		public:
		    /**
		     * Position des Objekts
		     */
		    Vector position;
		    /**
		     * Rotation des Objekts
		     */
		    Vector rotation;
		    /**
		     * Geschwindigkeit des Objekts
		     */
		    Vector velocity;
		    
		    Object()
		       :position(0,0,0),
			rotation(0,0,0),
			velocity(0,0,0) {}
	    
	    	    virtual void render()=0;
	};
}

#endif
