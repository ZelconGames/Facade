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

#define SCENE "scene"
#define NODES "nodes"
#define NAME "name"
#define POS "position"
#define X "x"
#define Y "y"
#define Z "z"
#define ROT "rotation"
#define QW "qw"
#define QX "qx"
#define QY "qy"
#define QZ "qz"
#define SCALE "scale"
#define MESH "entity"
#define MESH_HANDLE "meshFile"
#define CAST_SHADOWS "castShadows"
#define MATERIAL "materialName"
#define CAMERA "camera"
#define LIGHT "light"

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
    static void _LoadNode(Scene* scene, const xml_node& node);
};

#endif