//
//  Util.h
//  Ders 7
//
//  Created by Gurel Erceis on 4/15/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef Ders_7_Util_h
#define Ders_7_Util_h
#ifdef _WIN32
#include <GL/glew.h>
#include <GL/gl.h>
#else if __APPLE__
#include <OpenGL/gl.h>
#endif

#include <fstream>
#define fmax(a,b) (a>b)?a:b

const char* fileNameToPath(const char * filename){
    unsigned int const sz1  = strlen(filename);
#ifdef RESOURCE_PATH
    unsigned int const sz2  = strlen(RESOURCE_PATH);
#endif    
    char *concat            = (char*)malloc(sz1+sz2+1);
    
#ifdef RESOURCE_PATH
    memcpy( concat     , RESOURCE_PATH , sz2 );
    memcpy( concat+sz2         , filename  , sz1 );
    concat[sz1+sz2] = '\0';
#else
    memcpy( concat         , filename  , sz1 );
    concat[sz1] = '\0';
#endif    

    
    fprintf(stdout, "FILE:%s\n",concat);
    
    return concat;
}

/**
 file_path - shader file to load
 type - GL_VERTEX_SHADER || GL_FRAGMENT_SHADER
 **/
GLuint createShader(const char* file_path, GLuint type){
    
    
    GLuint ShaderID = glCreateShader(type);
    
    // Read the Vertex Shader code from the file
    std::string ShaderCode;
    std::ifstream ShaderStream(fileNameToPath(file_path), std::ifstream::in);
    if(ShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(ShaderStream, Line))
            ShaderCode += "\n" + Line;
        ShaderStream.close();
    }
    

    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    // Compile Shader
    char const * SourcePointer = ShaderCode.c_str();
    glShaderSource(ShaderID, 1, &SourcePointer , NULL);
    glCompileShader(ShaderID);
    
    // Check Shader
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
    if(!Result)
    {
        glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> ShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
        fprintf(stdout, "ERROR:%s\n%sShaderErrorMessage: %s\n",file_path,(type==GL_VERTEX_SHADER)?"Vertex":"Fragment", &ShaderErrorMessage[0]);
    }
    return ShaderID;
}

GLuint createProgram(const char * vertex_file_path,const char * fragment_file_path){
    
    // Create the shaders
    GLuint VertexShaderID = createShader(vertex_file_path, GL_VERTEX_SHADER);
    GLuint FragmentShaderID = createShader(fragment_file_path, GL_FRAGMENT_SHADER);
    
    if( VertexShaderID == 0 || FragmentShaderID == 0 ){
        return 0;
    }
    
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    // Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    
    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    if(!Result)
    {
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> ProgramErrorMessage( fmax(InfoLogLength, int(1)) );
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        fprintf(stdout, "ProgramErrorMessage: %s\n", &ProgramErrorMessage[0]);
    }
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    
    return ProgramID;
}

#endif
