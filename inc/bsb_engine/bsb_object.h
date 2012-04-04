#ifndef BSB_OBJECT_H
#define BSB_OBJECT_H
#include "bsb_vector.h"
class Bsb_Object
{
	public:
    /**
     * Position des Objekts
     */
    Bsb_Vector* position;
    /**
     * Rotation des Objekts
     */
    Bsb_Vector* rotation;
    /**
     * Geschwindigkeit des Objekts
     */
    Bsb_Vector* velocity;
    
    Bsb_Object(){
        position=new Bsb_Vector(0,0,0);
        rotation=new Bsb_Vector(0,0,0);
        velocity=new Bsb_Vector(0,0,0);
    }
    
    virtual void render()=0;
};
#endif
