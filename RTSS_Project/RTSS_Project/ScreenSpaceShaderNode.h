//
//  Model.h
//  Ders 5
//
//  Created by Gurel Erceis on 3/11/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//
// Assimp kutuphanesini kullaniyoruz.

#ifndef ScreenSpaceShaderNode_h
#define ScreenSpaceShaderNode_h
#include "Camera.h"
#include "ShadedGeometry.h"

class ScreenSpaceShaderNode: public ShadedGeometry{
public:
    ScreenSpaceShaderNode(char *filename):
    ShadedGeometry(filename,
                   "screen_space_vert_shader.vert",
                   "screen_space_frag_shader.frag")
    {
        generateBuffers();    
    }
    ~ScreenSpaceShaderNode(){
        
    }
    void draw(SceneNode *camera){
        
        glUseProgram(programId);
        
        glm::mat4 MVPmatrix = ((Camera*)camera)->projectionMatrix * camera->getInverseModelMatrix() * getModelMatrix();
        
        glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVPmatrix[0][0]);
       
        
        // vertex bufferi bagla
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // indiceleri bagla
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);
        
        // Attributelari enable et
        glEnableVertexAttribArray(AttributePosition);
        
        // ciz
        glDrawElements(GL_TRIANGLES, int(faceArray.size()), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
        

        // baglantilari kopar
        glDisableVertexAttribArray(AttributePosition);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        
        glUseProgram(0);
    }
private:
    GLuint UniformMVP;
    GLuint AttributePosition;

    
    void generateBuffers(){
        
        UniformMVP = glGetUniformLocation(programId, "MVP");
        printf("UniformMVP: %d\n",UniformMVP);
        
        AttributePosition = glGetAttribLocation(programId, "Position");
        printf("Position Attribute: %d\n", AttributePosition);
        
    }
};

#endif
