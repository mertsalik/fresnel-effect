//
//  ColorFillNode.h
//  Ders 7
//
//  Created by Gurel Erceis on 4/1/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef Ders_7_ColorFillNode_h
#define Ders_7_ColorFillNode_h

#include "ShadedGeometry.h"


class ColorFillNode: public ShadedGeometry{
public:
	GLuint frameCount;
    
    ColorFillNode(char* filename):ShadedGeometry(
                                                 filename,
                                                 "ColorFill_vert_shader.vert",
                                                 "ColorFill_frag_shader.frag"),frameCount(0){
        generateBuffers(); 
    }
    
    void draw(SceneNode *camera){
        frameCount++;
        
        glUseProgram(programId);
        
        glm::mat4 MVPmatrix = ((Camera*)camera)->projectionMatrix * camera->getInverseModelMatrix() * getModelMatrix();
        
        glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVPmatrix[0][0]);
        
        glUniform1f(UniformColor, frameCount/1000.f );
        
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
    GLuint UniformColor;
    GLuint AttributePosition;
    
    
    void generateBuffers(){
        
        UniformMVP = glGetUniformLocation(programId, "modelViewProjectionMatrix");
        printf("UniformMVP: %d\n",UniformMVP);
        
        UniformColor = glGetUniformLocation(programId, "color");
        printf("UniformColor: %d\n",UniformColor);
        
        AttributePosition = glGetAttribLocation(programId, "Position");
        printf("Position Attribute: %d\n", AttributePosition);
        
    }

};


#endif
