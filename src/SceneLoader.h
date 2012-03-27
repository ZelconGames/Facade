#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H
#pragma once


#include <Scene/Scene.hpp>
#include <Scene/Node.hpp>

#include <string>

#include <QtXml/QtXml>

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
#define SL_SOUND "sound"
#define SL_SOUNDNAME "soundFile"
#define SL_SOUNDVOL "volume"

class SceneLoader 
{
public:
    /**
      * Loads a scene.
      * @param path The path to the scene.
      * @returns A pointer to the scene or null when it fails.
      */
    static Scene* LoadScene(QString path);

protected:
    static Node::NodeSP _LoadElement(const QDomElement& og_element, Node::NodeSP dt_node = nullptr);

    static Node::NodeSP _LoadNode(const QDomElement& og_node, Node::NodeSP dt_parent);

    static Node::NodeSP _LoadMesh(const QDomElement& og_component, Node::NodeSP dt_node);

    static Node::NodeSP _LoadLight(const QDomElement& og_component, Node::NodeSP dt_node);
     
    static Node::NodeSP _LoadCamera(const QDomElement& og_component, Node::NodeSP dt_node);

    static Node* _LoadSound(const QDomElement& og_component, Node* dt_node);

    static Scene* mScene;
};

#endif
