//
//  SceneNode.h
//  Ders 7
//
//  Created by Gurel Erceis on 3/31/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef Ders_7_SceneNode_h
#define Ders_7_SceneNode_h
#ifdef _WIN32
#include <GL/glew.h>
#include <GL/gl.h>
#else if __APPLE__
#include <OpenGL/gl.h>
#endif
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <vector>

class SceneNode{
public:
    std::vector<SceneNode*> children;
    SceneNode *parent;
  
    SceneNode():_translationMatrix(glm::mat4x4(1.0f)),
                _rotationMatrix(glm::mat4x4(1.0f)),
                _scaleMatrix(glm::mat4x4(1.0f)),
                parent(NULL)
    {
        
    }
    virtual ~SceneNode(){
            
    }
    SceneNode* translate(float x, float y, float z){
        _translationMatrix = glm::translate(_translationMatrix, x,y,z);
        return this;
    }
    SceneNode* rotate(float angle, float x, float y, float z){
        _rotationMatrix = glm::rotate(_rotationMatrix, angle, x, y, z);
        return this;
    }
    SceneNode* scale(float x, float y, float z){
        _scaleMatrix = glm::scale(_scaleMatrix, x, y, z);
        return this;
    }
    SceneNode* identity(){
        _scaleMatrix = glm::mat4x4(1.0f);
        _translationMatrix = glm::mat4x4(1.0f);
        _rotationMatrix = glm::mat4x4(1.0f);
        return this;
    }
    glm::vec3 getLocalPosition(){
        glm::mat4 matrix = _translationMatrix;
        return glm::vec3(matrix[3][0],matrix[3][1],matrix[3][2]);
    }
    glm::vec3 getGlobalPosition(){
        glm::mat4 matrix = getModelMatrix();
        return glm::vec3(matrix[3][0],matrix[3][1],matrix[3][2]);
    }
    glm::vec3 getInverseLocalPosition(){
        glm::mat4 matrix = glm::inverse(_translationMatrix);
        return glm::vec3(matrix[3][0],matrix[3][1],matrix[3][2]);
    }
    glm::vec3 getInverseGlobalPosition(){
        glm::mat4 matrix = glm::inverse(getModelMatrix());
        return glm::vec3(matrix[3][0],matrix[3][1],matrix[3][2]);
    }
    
    glm::mat4 getModelMatrix(){
        glm::mat4 result =  _translationMatrix*_scaleMatrix*_rotationMatrix;
        SceneNode* temp = parent;
        while( temp != NULL ){
            result =  temp->getModelMatrix() * result;
            temp = temp->parent;
        }
        return result;
    }
    glm::mat4 getInverseModelMatrix(){ return glm::inverse(getModelMatrix()); }
    SceneNode* addNode( SceneNode *child){
        children.push_back(child); 
        child->parent = this;
        return child;
    }
    virtual void draw(SceneNode *camera){}
protected:
    glm::mat4 _translationMatrix;
    glm::mat4 _rotationMatrix;
    glm::mat4 _scaleMatrix;
    
};


#endif
