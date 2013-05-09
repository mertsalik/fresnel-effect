//
//  Geometry.h
//  Ders 7
//
//  Created by Gurel Erceis on 3/31/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef Ders_7_Geometry_h
#define Ders_7_Geometry_h

#include "Util.h"

#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/vector3.h>
#include <vector>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Geometry: public SceneNode{
public:
    Geometry(const char* filename){
        geometryFileName = fileNameToPath(filename);
        loadGeometry(); 
        generateBuffers();
    }
    virtual ~Geometry(){
        glDeleteBuffers(1, &vertexBufferID);
        glDeleteBuffers(1, &normalBufferID);
        glDeleteBuffers(1, &indiceBufferID);
    }
protected:
    GLuint vertexBufferID,normalBufferID,indiceBufferID;
    std::vector<GLuint> faceArray;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
	int numFaces;
private:
    const char* geometryFileName;
    
    void generateBuffers(){
        
        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        
        glGenBuffers(1, &normalBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
        
        glGenBuffers(1, &indiceBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, faceArray.size() * sizeof(GLuint), &faceArray[0], GL_STATIC_DRAW);
        
        printf("VertexBufferID:%d\n NormalBufferID:%d\n IndiceBufferID:%d\n", vertexBufferID, normalBufferID, indiceBufferID);
    }
    bool loadGeometry(){
        Assimp::Importer Importer;
        const aiScene *pScene = NULL;
        const aiMesh *pMesh = NULL;
        // Assimp e dosyayi yuklemesini soyluyoruz.
        pScene = Importer.ReadFile(geometryFileName, aiProcess_Triangulate| aiProcess_ValidateDataStructure | aiProcess_FindInvalidData);
        
        if (!pScene)
        {
            printf("Error parsing '%s': '%s'\n", geometryFileName, Importer.GetErrorString());
            return false;
        }
        
        pMesh = pScene->mMeshes[0];
        if (!pMesh)
        {
            printf("Error Finding Model In file.  Did you export an empty scene?");
            return false;
        }
        
        readScene(pScene);
        return true;
    }
    void readScene(const struct aiScene *sc) {
        faceArray.clear();
        vertices.clear();
        normals.clear();
        
        int currentIndex = 0;
        
        // For each mesh
        for (unsigned int n = 0; n < sc->mNumMeshes; ++n)
        {
            const struct aiMesh* mesh = sc->mMeshes[n];
            
            // create array with faces
            // have to convert from Assimp format to array
            
            for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
                const struct aiFace* face = &mesh->mFaces[t];
                
                faceArray.push_back(face->mIndices[0]+currentIndex);
                faceArray.push_back(face->mIndices[1]+currentIndex);
                faceArray.push_back(face->mIndices[2]+currentIndex);
            }
            numFaces = mesh->mNumFaces;
            
            // buffer for vertex positions
            if (mesh->HasPositions()) {
                
                for( unsigned int t = 0; t < mesh->mNumVertices; t++)
                {
                    const aiVector3D* vertex = &mesh->mVertices[t];
                    vertices.push_back(glm::vec3(vertex->x,vertex->y,vertex->z));
                    if (mesh->HasNormals()) {
                        vertex = &mesh->mNormals[t];
                        normals.push_back(glm::vec3(vertex->x,vertex->y,vertex->z));
                    }
                        
                }
                currentIndex += mesh->mNumVertices;
                // buffer for normals
                if (!mesh->HasNormals()){
                    normals.resize(mesh->mNumVertices);
                    // calculate normals if no normal is found for mesh
                    for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
                        const struct aiFace* face = &mesh->mFaces[t];
                        
                        aiVector3D p1 = mesh->mVertices[face->mIndices[0]];
                        aiVector3D p2 = mesh->mVertices[face->mIndices[1]];
                        aiVector3D p3 = mesh->mVertices[face->mIndices[2]];
                        
                        glm::vec3 a = glm::vec3(p2.x-p1.x,p2.y-p1.y,p2.z-p1.z);
                        glm::vec3 b = glm::vec3(p3.x-p1.x,p3.y-p1.y,p3.z-p1.z);
                        
                        glm::vec3 n = glm::cross(a,b);
                        glm::normalize(n);
                        
                        normals[face->mIndices[0]] = n;
                        normals[face->mIndices[1]] = n;
                        normals[face->mIndices[2]] = n;
                    }
                }
            } 
            
            
        }
    }
};


#endif
