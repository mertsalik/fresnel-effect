//
//  DiffuseNode.h
//  Ders 7
//
//  Created by Gurel Erceis on 4/8/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef Ders_7_DiffuseNode_h
#define Ders_7_DiffuseNode_h

#include "ShadedGeometry.h"

class DiffusePerVertexNode: public ShadedGeometry{
public:
    DiffusePerVertexNode(const char *filename):
    ShadedGeometry(filename,
                   "diffuse_per_vertex_shader.vert",
                   "diffuse_per_vertex_shader.frag")
    {
        generateBuffers();    
    }
    ~DiffusePerVertexNode(){
        
    }
    void draw(SceneNode *camera){
        
        glUseProgram(programId);
        
        glm::mat4 MVPmatrix = ((Camera*)camera)->projectionMatrix * camera->getInverseModelMatrix() * getModelMatrix();
        glm::mat4 MVmatrix = getModelMatrix();
        
        glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVPmatrix[0][0]);
        glUniformMatrix4fv(UniformMV, 1, GL_FALSE, &MVmatrix[0][0]);
        
        
        // vertex bufferi bagla
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // normal buffer i bagla
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // indiceleri bagla
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);
        
        // Attributelari enable et
        glEnableVertexAttribArray(AttributePosition);
        glEnableVertexAttribArray(AttributeNormal);
        
        // ciz
        glDrawElements(GL_TRIANGLES, int(faceArray.size()), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
        
        
        // baglantilari kopar
        glDisableVertexAttribArray(AttributeNormal);
        glDisableVertexAttribArray(AttributePosition);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        
        glUseProgram(0);
    }
private:
    GLuint UniformMVP,UniformMV;
    GLuint AttributePosition,AttributeNormal;
    
    
    void generateBuffers(){
        
        UniformMVP = glGetUniformLocation(programId, "MVP");
        printf("UniformMVP: %d\n",UniformMVP);
        
        UniformMV = glGetUniformLocation(programId, "ModelView");
        printf("UniformMV: %d\n",UniformMV);
        
        AttributePosition = glGetAttribLocation(programId, "Position");
        printf("Position Attribute: %d\n", AttributePosition);
        
        AttributeNormal = glGetAttribLocation(programId, "Normal");
        printf("Normal Attribute: %d\n", AttributeNormal);
        
    }
};

#endif
