//
//  ShadedGeometry.h
//  Ders 7
//
//  Created by Gurel Erceis on 4/1/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef Ders_7_ShadedGeometry_h
#define Ders_7_ShadedGeometry_h

#include "Util.h"
#define BUFFER_OFFSET(i) ((void*)(i))

class ShadedGeometry: public Geometry{
public:
    ShadedGeometry(const char* filename, const char *vertexShaderFile, const char *fragmentShaderFile):Geometry(filename){
        programId = createProgram(vertexShaderFile, fragmentShaderFile);
    }
    virtual ~ShadedGeometry(){
        glDeleteProgram(programId);
    } 
protected:
    GLuint programId;
private:
};


#endif
