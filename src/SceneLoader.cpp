#include "SceneLoader.h"

#include "Graphics/CameraComponent.hpp"
#include "Graphics/MeshComponent.hpp"
#include "Graphics/LightComponent.hpp"

Scene* SceneLoader::LoadScene(string path)
{
    Scene* scene = nullptr;
    xml_document doc;
    xml_parse_result result = doc.load_file(path.c_str());
    cout << "Loading result: " << result.description() << endl;
    if(result)
    {
        scene = new Scene(path.c_str());
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
        xml_node entity = node.child(SL_ENTITY);

        dt_node->SetPosition(pos.attribute(SL_X).as_float(), pos.attribute(SL_Y).as_float(),
            pos.attribute(SL_Z).as_float());
        dt_node->SetRotation(Ogre::Quaternion(rot.attribute(SL_QW).as_float(), 
            rot.attribute(SL_QX).as_float(), rot.attribute(SL_QY).as_float(), rot.attribute(SL_QZ).as_float()));
        dt_node->SetScale(Ogre::Vector3(scale.attribute(SL_X).as_float(), scale.attribute(SL_Y).as_float(),
            scale.attribute(SL_Z).as_float()));

        MeshComponent* mesh = dt_node->AddComponent<MeshComponent>(new MeshComponent(
            entity.attribute(SL_MESH_HANDLE).value(), entity.first_child().attribute(SL_MATERIAL).value(),
            entity.attribute(SL_NAME).value()));

        mesh->SetCastShadows(entity.attribute(SL_CAST_SHADOWS).as_bool());
    }
}