#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H
#pragma once

#include "3rdParty/pugixml/pugixml.hpp"

#include <Scene/Scene.hpp>
#include <Scene/Node.hpp>

#include <string>

using namespace pugi;
using namespace std;
using namespace dt;

#define SL_SCENE "scene"
#define SL_NODES "nodes"
#define SL_NAME "name"
#define SL_POS "position"
#define SL_X "x"
#define SL_Y "y"
#define SL_Z "z"
#define SL_ROT "rotation"
#define SL_QW "qw"
#define SL_QX "qx"
#define SL_QY "qy"
#define SL_QZ "qz"
#define SL_SCALE "scale"
#define SL_NODE "node"
#define SL_MESH_HANDLE "meshFile"
#define SL_CAST_SHADOWS "castShadows"
#define SL_MATERIALNAME "materialName"
#define SL_MATERIAL "material"
#define SL_CAMERA "camera"
#define SL_LIGHT "light"
#define SL_DIRECTION "directionVector"
#define SL_ENTITY "entity"
#define SL_PLANE "plane"
#define SL_SIZEX "height"
#define SL_SIZEY "width"
#define SL_NORMAL "normal"
#define SL_ENABLENORMALS "hasNormals"
#define SL_SEGMENTSX "xSegments"
#define SL_SEGMENTSY "ySegments"
#define SL_NUMTEXCOORD "numTexCoordSets"
#define SL_UTILE "uTile"
#define SL_VTILE "vTile"
#define SL_INDEX "index"
#define SL_BEGIN "terrain"

class SceneLoader 
{
public:
    /**
      * Loads a scene.
      * @param path The path to the scene.
      * @returns A pointer to the scene or null when it fails.
      */
    static Scene* LoadScene(string path);

protected:
    static Node* _LoadElement(const xml_node& og_element, Node* dt_node = nullptr);

    static Node* _LoadNode(const xml_node& og_node, Node* dt_parent);

    static Node* _LoadMesh(const xml_node& og_component, Node* dt_node);

    static Node* _LoadLight(const xml_node& og_component, Node* dt_node);
     
    static Node* _LoadCamera(const xml_node& og_component, Node* dt_node);

    static Scene* mScene;
};

#endif