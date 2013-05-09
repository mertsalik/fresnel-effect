//
//  Camera.h
//  Ders 6
//
//  Created by Gurel Erceis on 3/17/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef Ders_6_Camera_h
#define Ders_6_Camera_h
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "SceneNode.h"

class Camera: public SceneNode{
public:
    Camera():SceneNode(){
        projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.f);
    };
    glm::mat4 projectionMatrix;
};


#endif
