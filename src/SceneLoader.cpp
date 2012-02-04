#include "SceneLoader.h"

#include "Graphics/CameraComponent.hpp"
#include "Graphics/MeshComponent.hpp"
#include "Graphics/LightComponent.hpp"

#include <OgreProcedural.h>

Scene* SceneLoader::LoadScene(string path)
{
    Scene* scene = nullptr;
    xml_document doc;
    xml_parse_result result = doc.load_file(path.c_str());
    cout << "Loading result: " << result.description() << endl;
    if(result)
    {
        scene = new Scene(path.c_str());
        OgreProcedural::Root::getInstance()->sceneManager = scene->GetSceneManager();

        xml_node root = doc.child(SL_SCENE);

        for(xml_node node = root.first_child(); node; node = node.next_sibling())
        {
            if(strcmp(node.name(), SL_CAMERA) == 0)
            {
                _LoadCamera(scene, node);
            }
            else if(strcmp(node.name(), SL_NODES) == 0)
            {
                for(xml_node mesh_node = node.first_child(); mesh_node; mesh_node = mesh_node.next_sibling())
                {
                    _LoadMesh(scene, mesh_node);
                }
            }
            else if(strcmp(node.name(), SL_LIGHT) == 0)
            {
                _LoadLight(scene, node);
            }
        }
    }

    return scene;
}

void SceneLoader::_LoadCamera(Scene* scene, const xml_node& node)
{
    if(node && scene)
    {
        Node* dt_node = scene->AddChildNode(new Node(node.attribute(SL_NAME).value()));
        dt_node->AddComponent<CameraComponent>(new CameraComponent(node.attribute(SL_NAME).value()));
        xml_node pos = node.child(SL_POS);
        xml_node rot = node.child(SL_ROT);

        dt_node->SetPosition(pos.attribute(SL_X).as_float(), pos.attribute(SL_Y).as_float(),
            pos.attribute(SL_Z).as_float());
        dt_node->SetRotation(Ogre::Quaternion(rot.attribute(SL_QW).as_float(), 
            rot.attribute(SL_QX).as_float(), rot.attribute(SL_QY).as_float(), rot.attribute(SL_QZ).as_float()));
    }
}

void SceneLoader::_LoadLight(Scene* scene, const xml_node& node)
{
    if(node && scene)
    {
        Node* dt_node = scene->AddChildNode(new Node(node.attribute(SL_NAME).value()));
        dt_node->AddComponent<LightComponent>(new LightComponent(node.attribute(SL_NAME).value()))->SetCastShadows(
            node.attribute(SL_CAST_SHADOWS).as_bool());
        xml_node pos = node.child(SL_POS);
        xml_node dir = node.child(SL_DIRECTION);

        dt_node->SetPosition(pos.attribute(SL_X).as_float(), pos.attribute(SL_Y).as_float(),
            pos.attribute(SL_Z).as_float());
        dt_node->SetDirection(Ogre::Vector3(dir.attribute(SL_X).as_float(), dir.attribute(SL_Y).as_float(),
            dir.attribute(SL_Z).as_float()));
    }
}

void SceneLoader::_LoadMesh(Scene* scene, const xml_node& node)
{
    if(node && scene)
    {
        Node* dt_node = scene->AddChildNode(new Node(node.attribute(SL_NAME).value()));
        xml_node pos = node.child(SL_POS);
        xml_node rot = node.child(SL_ROT);
        xml_node scale = node.child(SL_SCALE);

        dt_node->SetPosition(pos.attribute(SL_X).as_float(), pos.attribute(SL_Y).as_float(),
            pos.attribute(SL_Z).as_float());
        dt_node->SetRotation(Ogre::Quaternion(rot.attribute(SL_QW).as_float(), 
            rot.attribute(SL_QX).as_float(), rot.attribute(SL_QY).as_float(), rot.attribute(SL_QZ).as_float()));
        dt_node->SetScale(Ogre::Vector3(scale.attribute(SL_X).as_float(), scale.attribute(SL_Y).as_float(),
            scale.attribute(SL_Z).as_float()));

        //entity
        xml_node entity = node.child(SL_ENTITY);
        if(!entity.empty())
        {
            MeshComponent* mesh = dt_node->AddComponent<MeshComponent>(new MeshComponent(
                entity.attribute(SL_MESH_HANDLE).value(), "",
                entity.attribute(SL_NAME).value()));

            for(xml_node mat = entity.first_child(); mat; mat = mat.next_sibling())
            {
                auto material_handle = mat.attribute(SL_MATERIALNAME).value();
                //
                // Todo: Add the material loading logic here. Just fill it!!!!
                //
            }

            mesh->SetCastShadows(entity.attribute(SL_CAST_SHADOWS).as_bool());
        }

        //plane
        xml_node plane = node.child(SL_PLANE);
        if(!plane.empty())
        {
            //create mesh
            OgreProcedural::PlaneGenerator()
                .setSizeX(plane.attribute(SL_SIZEX).as_float())
                .setSizeY(plane.attribute(SL_SIZEY).as_float())
                .setEnableNormals(plane.attribute(SL_ENABLENORMALS).as_bool())
                .setNumSegX(plane.attribute(SL_SEGMENTSX).as_int())
                .setNumSegY(plane.attribute(SL_SEGMENTSY).as_int())
                //.setNumTexCoordSet(plane.attribute(SL_NUMTEXCOORD).as_int())
               // .setUTile(plane.attribute(SL_UTILE).as_float())
                //.setVTile(plane.attribute(SL_VTILE).as_float())
                .setNormal(Ogre::Vector3( plane.child(SL_NORMAL).attribute(SL_X).as_float(),
                                          plane.child(SL_NORMAL).attribute(SL_Y).as_float(),
                                          plane.child(SL_NORMAL).attribute(SL_Z).as_float() ))
                .realizeMesh(plane.attribute(SL_NAME).value());

            //add entity
            MeshComponent* mesh = dt_node->AddComponent<MeshComponent>(new MeshComponent(
                plane.attribute(SL_NAME).value(),
                plane.attribute(SL_MATERIAL).value(),
                plane.attribute(SL_NAME).value() ));
        }

        
    }
}