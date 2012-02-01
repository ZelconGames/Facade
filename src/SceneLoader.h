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
#define SL_MESH "node"
#define SL_MESH_HANDLE "meshFile"
#define SL_CAST_SHADOWS "castShadows"
#define SL_MATERIAL "materialName"
#define SL_CAMERA "camera"
#define SL_LIGHT "light"
#define SL_DIRECTION "directionVector"
#define SL_ENTITY "entity"

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
    static void _LoadMesh(Scene* scene, const xml_node& node);

    static void _LoadLight(Scene* scene, const xml_node& node);

    static void _LoadCamera(Scene* scene, const xml_node& node);
};

#endif