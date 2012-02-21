#include "SceneLoader.h"

#include "Graphics/CameraComponent.hpp"
#include "Graphics/MeshComponent.hpp"
#include "Graphics/LightComponent.hpp"
#include "Audio/SoundComponent.hpp"

#include <OgreProcedural.h>
#include <OGRE/OgreSubEntity.h>

#include <cstdint>

Scene* SceneLoader::mScene = nullptr;

Scene* SceneLoader::LoadScene(string path)
{
    mScene = nullptr;
    xml_document doc;
    xml_parse_result result = doc.load_file(path.c_str());
    
    cout << "Loading result: " << result.description() << endl;
    
    if(result)
    {
        mScene = new Scene(path.c_str());
        OgreProcedural::Root::getInstance()->sceneManager = mScene->GetSceneManager();

        xml_node root = doc.child(SL_SCENE);

        for(xml_node scene_child = root.child(SL_BEGIN).next_sibling(); 
            scene_child; scene_child = scene_child.next_sibling())
        {
            if(strcmp(scene_child.name(), SL_NODES) != 0) //For free components(not including free mesh components).
            {
                _LoadElement(scene_child);
            }
            else                                    //For nodes and free mesh components.
            {
                for(xml_node nodes_child = scene_child.first_child(); nodes_child; 
                    nodes_child = nodes_child.next_sibling())
                {
                    _LoadElement(nodes_child);
                }
            }
        }
    }

    return mScene;
}

Node* SceneLoader::_LoadElement(const xml_node& og_element, Node* dt_node)
{    
    auto name = og_element.name();
    Node* node = nullptr;

    if(strcmp(name, SL_LIGHT) == 0)
        node = _LoadLight(og_element, dt_node);                   //Light
    else if(strcmp(name, SL_CAMERA) == 0)
        node = _LoadCamera(og_element, dt_node);                  //Camera
    else if(strcmp(name, SL_SOUND) == 0)
        node = _LoadSound(og_element, dt_node);                   //Sound
    else if(strcmp(name, SL_NODE) == 0)
        if(og_element.child(SL_ENTITY).empty() && og_element.child(SL_PLANE).empty())
            node = _LoadNode(og_element, dt_node);                //Node
        else
            node = _LoadMesh(og_element, dt_node);                //Mesh

    return node;
}

Node* SceneLoader::_LoadNode(const xml_node& og_node, Node* dt_parent)
{
    Node* node = nullptr;

    if(og_node)
    {
        node = new Node(og_node.attribute(SL_NAME).value());

        if(dt_parent)
            dt_parent->AddChildNode(node);
        else
            mScene->AddChildNode(node);

        xml_node pos = og_node.child(SL_POS);
        xml_node rot = og_node.child(SL_ROT);
        xml_node scale = og_node.child(SL_SCALE);

        node->SetPosition(pos.attribute(SL_X).as_float(), pos.attribute(SL_Y).as_float(),
            pos.attribute(SL_Z).as_float());
        node->SetRotation(Ogre::Quaternion(rot.attribute(SL_QW).as_float(), 
            rot.attribute(SL_QX).as_float(), rot.attribute(SL_QY).as_float(), rot.attribute(SL_QZ).as_float()));
        node->SetScale(Ogre::Vector3(scale.attribute(SL_X).as_float(), scale.attribute(SL_Y).as_float(),
            scale.attribute(SL_Z).as_float()));

        for(xml_node node_child = scale.next_sibling(); node_child; node_child = node_child.next_sibling())
            _LoadElement(node_child, node);
    }

    return node;
}

Node* SceneLoader::_LoadCamera(const xml_node& og_component, Node* dt_node)
{
    Node* node = dt_node;

    if(og_component)
    {
        QString name = og_component.attribute(SL_NAME).value();

        if(node == nullptr)
        {
            node = mScene->AddChildNode(new Node(name + "_node"));

            xml_node pos = og_component.child(SL_POS);
            xml_node rot = og_component.child(SL_ROT);

            node->SetPosition(pos.attribute(SL_X).as_float(), pos.attribute(SL_Y).as_float(),
                pos.attribute(SL_Z).as_float());
            node->SetRotation(Ogre::Quaternion(rot.attribute(SL_QW).as_float(), 
                rot.attribute(SL_QX).as_float(), rot.attribute(SL_QY).as_float(), rot.attribute(SL_QZ).as_float()));
        }

        node->AddComponent<CameraComponent>(new CameraComponent(name));
    }

    return node;
}

Node* SceneLoader::_LoadLight(const xml_node& og_component, Node* dt_node)
{
    Node* node = dt_node;

    if(og_component)
    {
        QString name = og_component.attribute(SL_NAME).value();

        if(node == nullptr)
        {
            node = mScene->AddChildNode(new Node(name + "_node"));

            xml_node pos = og_component.child(SL_POS);
            xml_node dir = og_component.child(SL_DIRECTION);

            node->SetPosition(pos.attribute(SL_X).as_float(), pos.attribute(SL_Y).as_float(),
                pos.attribute(SL_Z).as_float());
            node->SetDirection(Ogre::Vector3(dir.attribute(SL_X).as_float(), dir.attribute(SL_Y).as_float(),
                dir.attribute(SL_Z).as_float()));
        }

            node->AddComponent<LightComponent>(new LightComponent(name))->SetCastShadows(
                og_component.attribute(SL_CAST_SHADOWS).as_bool());
    }

    return node;
}

Node* SceneLoader::_LoadSound(const xml_node& og_component, Node* dt_node)
{
    Node* node = dt_node;

    if(og_component)
    {
        QString name = og_component.attribute(SL_NAME).value();

        if(node == nullptr)
        {
            node = mScene->AddChildNode(new Node(name + "_node"));

            xml_node pos = og_component.child(SL_POS);

            node->SetPosition(pos.attribute(SL_X).as_float(), pos.attribute(SL_Y).as_float(),
                pos.attribute(SL_Z).as_float());
        }

        SoundComponent* s = node->AddComponent<SoundComponent>(new SoundComponent(og_component.attribute(SL_SOUNDNAME).value(), name));
        s->SetVolume(og_component.attribute(SL_SOUNDVOL).as_float());
    }

    return node;
}

Node* SceneLoader::_LoadMesh(const xml_node& og_component, Node* dt_node)
{
    Node* node = dt_node;

    if(og_component)
    {
        QString name = og_component.attribute(SL_NAME).value();

        if(node == nullptr)
        {
            node = mScene->AddChildNode(new Node(name + "_node"));

            xml_node pos = og_component.child(SL_POS);
            xml_node rot = og_component.child(SL_ROT);
            xml_node scale = og_component.child(SL_SCALE);

            node->SetPosition(pos.attribute(SL_X).as_float(), pos.attribute(SL_Y).as_float(),
                pos.attribute(SL_Z).as_float());
            node->SetRotation(Ogre::Quaternion(rot.attribute(SL_QW).as_float(), 
                rot.attribute(SL_QX).as_float(), rot.attribute(SL_QY).as_float(), rot.attribute(SL_QZ).as_float()));
            node->SetScale(Ogre::Vector3(scale.attribute(SL_X).as_float(), scale.attribute(SL_Y).as_float(),
                scale.attribute(SL_Z).as_float()));
        }        

        //entity
        xml_node unknown_mesh = og_component.child(SL_SCALE).next_sibling();
        if(strcmp(unknown_mesh.name(), SL_ENTITY) == 0)
        {
            const xml_node& entity = unknown_mesh;

            MeshComponent* mesh = node->AddComponent<MeshComponent>(new MeshComponent(
                entity.attribute(SL_MESH_HANDLE).value(), "",
                entity.attribute(SL_NAME).value()));

            for(xml_node mat = entity.first_child(); mat; mat = mat.next_sibling())
            {
                auto material_handle = mat.attribute(SL_MATERIALNAME).value();
                uint32_t index = mat.attribute(SL_INDEX).as_uint();

                mesh->GetOgreEntity()->getSubEntity(index)->setMaterialName(material_handle);
            }

            mesh->SetCastShadows(entity.attribute(SL_CAST_SHADOWS).as_bool());
        }
        else if(strcmp(unknown_mesh.name(), SL_PLANE) == 0)
        {
            //plane
            const xml_node& plane = unknown_mesh;
            if(!plane.empty())
            {
                //create mesh
                OgreProcedural::PlaneGenerator()
                    .setSizeX(plane.attribute(SL_SIZEX).as_float())
                    .setSizeY(plane.attribute(SL_SIZEY).as_float())
                    .setEnableNormals(plane.attribute(SL_ENABLENORMALS).as_bool())
                    .setNumSegX(plane.attribute(SL_SEGMENTSX).as_int())
                    .setNumSegY(plane.attribute(SL_SEGMENTSY).as_int())
                    .setNumTexCoordSet(plane.attribute(SL_NUMTEXCOORD).as_int())
                    .setUTile(plane.attribute(SL_UTILE).as_float())
                    .setVTile(plane.attribute(SL_VTILE).as_float())
                    .setNormal(Ogre::Vector3( plane.child(SL_NORMAL).attribute(SL_X).as_float(),
                    plane.child(SL_NORMAL).attribute(SL_Y).as_float(),
                    plane.child(SL_NORMAL).attribute(SL_Z).as_float() ))
                    .realizeMesh(plane.attribute(SL_NAME).value());

                //add entity
                MeshComponent* mesh = node->AddComponent<MeshComponent>(new MeshComponent(
                    plane.attribute(SL_NAME).value(),
                    plane.attribute(SL_MATERIAL).value(),
                    plane.attribute(SL_NAME).value() ));
            }
        }
    }

    return node;
}