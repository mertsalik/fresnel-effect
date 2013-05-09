//
//  Scene.h
//  Ders 7
//
//  Created by Gurel Erceis on 3/31/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef Ders_7_Scene_h
#define Ders_7_Scene_h
#include <vector>
#include "Camera.h"
#include "Light.h"
#include "Geometry.h"
#include "ShadedGeometry.h"
#include "Effect.h"

class Scene{
public:
    void addNode( SceneNode *child){
        children.push_back(child);
    }
    void setCamera( Camera *camera){
        this->camera = camera;
    }
    void addLight( Light *light){
        lights.push_back( light );
    }
    void addEffect( Effect *effect ){
        effects.push_back( effect );
    }
    void draw(){
        
        unsigned long len = lights.size();
        for(  unsigned long i = 0; i < len ; i++)
        {
            lights[i]->setId(i);
            lights[i]->draw(camera);
        }
        if(effects.size()>0)
        {
            effects[0]->enableBuffer();
        }
        glLoadIdentity();
        len = children.size();
        for(  unsigned long i = 0; i < len ; i++)
        {
            drawNode(children[i]);
        }
        if(effects.size()>0)
        {
            effects[0]->disableBuffer();
            effects[0]->draw();
        }
    }
    void resize(){
        if(effects.size()>0)
        {
            effects[0]->resize();
        }
    }
private:
    std::vector<SceneNode*> children;
    std::vector<Light*> lights;
    std::vector<Effect*> effects;
    Camera *camera;
    void drawNode(SceneNode *node){
        node->draw(camera); 
        
        unsigned long len = node->children.size();
        for(  unsigned long i = 0; i < len ; i++)
        {
            drawNode(node->children[i]);
        }    
    }
};


#endif
