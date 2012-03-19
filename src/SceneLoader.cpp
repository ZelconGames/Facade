#include "SceneLoader.h"

#include "Graphics/CameraComponent.hpp"
#include "Graphics/MeshComponent.hpp"
#include "Graphics/LightComponent.hpp"
#include "Audio/SoundComponent.hpp"
#include "Core/ResourceManager.hpp"

#include <QtXml/QtXml>
#include <OgreProcedural.h>
#include <OGRE/OgreSubEntity.h>

#include <cstdint>

Scene* SceneLoader::mScene = nullptr;

Scene* SceneLoader::LoadScene(QString path)
{
    mScene = nullptr;
    QFile file(path);
    QDomDocument doc;
    if(!file.open(QIODevice::ReadOnly))
    {
        dt::Logger::Get().Error("Couldn't open file " + path);
        return nullptr;
    }
    cout << "Loading result: " << endl;
    if(doc.setContent(&file))
    {
        mScene = new Scene(path);
        OgreProcedural::Root::getInstance()->sceneManager = mScene->GetSceneManager();

        QDomElement root = doc.documentElement();

        for(QDomElement scene_child = root.firstChildElement(); !scene_child.isNull(); scene_child = scene_child.nextSiblingElement())
        {
            if(scene_child.nodeName() != SL_NODES) //For free components(not including free mesh components).
            {
                _LoadElement(scene_child);
            }
            else //For nodes and free mesh components.
            {
                for(QDomElement nodes_child = scene_child.firstChildElement(); !nodes_child.isNull(); nodes_child = nodes_child.nextSiblingElement())
                {
                    _LoadElement(nodes_child);
                }
            }
        }
    }

    return mScene;
}

Node* SceneLoader::_LoadElement(const QDomElement& og_element, Node* dt_node)
{    
    QString name = og_element.nodeName();
    Node* node = nullptr;

    if(name == SL_LIGHT)
    {
        node = _LoadLight(og_element, dt_node);                   //Light
    }
    else if(name == SL_CAMERA)
    {
        node = _LoadCamera(og_element, dt_node);                  //Camera
    }
    else if(name == SL_SOUND)
    {
        node = _LoadSound(og_element, dt_node);                   //Sound
    }
    else if(name == SL_NODE)
    {
        if(og_element.firstChildElement(SL_ENTITY).isNull() && og_element.firstChildElement(SL_PLANE).isNull())
        {
            node = _LoadNode(og_element, dt_node);                //Node
        }
        else
        {
            node = _LoadMesh(og_element, dt_node);                //Mesh
        }
    }
    return node;
}

Node* SceneLoader::_LoadNode(const QDomElement& og_node, Node* dt_parent)
{
    Node* node = nullptr;

    if(!og_node.isNull())
    {
        node = new Node(og_node.attribute(SL_NAME));

        if(dt_parent)
        {
            dt_parent->AddChildNode(node);
        } else {
            mScene->AddChildNode(node);
        }

        QDomElement pos = og_node.firstChildElement(SL_POS);
        QDomElement rot = og_node.firstChildElement(SL_ROT);
        QDomElement scale = og_node.firstChildElement(SL_SCALE);

        node->SetPosition(pos.attribute(SL_X).toFloat(), pos.attribute(SL_Y).toFloat(),
            pos.attribute(SL_Z).toFloat());
        node->SetRotation(Ogre::Quaternion(rot.attribute(SL_QW).toFloat(),
            rot.attribute(SL_QX).toFloat(), rot.attribute(SL_QY).toFloat(), rot.attribute(SL_QZ).toFloat()));
        node->SetScale(Ogre::Vector3(scale.attribute(SL_X).toFloat(), scale.attribute(SL_Y).toFloat(),
            scale.attribute(SL_Z).toFloat()));

        for(QDomElement node_child = scale.nextSiblingElement(); !node_child.isNull(); node_child = node_child.nextSiblingElement())
        {
            _LoadElement(node_child, node);
        }
    }

    return node;
}

Node* SceneLoader::_LoadCamera(const QDomElement& og_component, Node* dt_node)
{
    Node* node = dt_node;

    if(!og_component.isNull())
    {
        QString name = og_component.attribute(SL_NAME);

        if(node == nullptr)
        {
            node = mScene->AddChildNode(new Node(name + "_node"));

            QDomElement pos = og_component.firstChildElement(SL_POS);
            QDomElement rot = og_component.firstChildElement(SL_ROT);

            node->SetPosition(pos.attribute(SL_X).toFloat(), pos.attribute(SL_Y).toFloat(),
                pos.attribute(SL_Z).toFloat());
            node->SetRotation(Ogre::Quaternion(rot.attribute(SL_QW).toFloat(),
                rot.attribute(SL_QX).toFloat(), rot.attribute(SL_QY).toFloat(), rot.attribute(SL_QZ).toFloat()));
        }

        node->AddComponent<CameraComponent>(new CameraComponent(name));
    }

    return node;
}

Node* SceneLoader::_LoadLight(const QDomElement& og_component, Node* dt_node)
{
    Node* node = dt_node;

    if(!og_component.isNull())
    {
        QString name = og_component.attribute(SL_NAME);

        if(node == nullptr)
        {
            node = mScene->AddChildNode(new Node(name + "_node"));

            QDomElement pos = og_component.firstChildElement(SL_POS);
            QDomElement dir = og_component.firstChildElement(SL_DIRECTION);

            node->SetPosition(pos.attribute(SL_X).toFloat(), pos.attribute(SL_Y).toFloat(),
                pos.attribute(SL_Z).toFloat());
            node->SetDirection(Ogre::Vector3(dir.attribute(SL_X).toFloat(), dir.attribute(SL_Y).toFloat(),
                dir.attribute(SL_Z).toFloat()));
        }

            node->AddComponent<LightComponent>(new LightComponent(name))->SetCastShadows(
                og_component.attribute(SL_CAST_SHADOWS).toInt());
    }

    return node;
}

Node* SceneLoader::_LoadMesh(const QDomElement& og_component, Node* dt_node)
{
    Node* node = dt_node;

    if(!og_component.isNull())
    {
        QString name = og_component.attribute(SL_NAME);

        if(node == nullptr)
        {
            node = mScene->AddChildNode(new Node(name + "_node"));

            QDomElement pos = og_component.firstChildElement(SL_POS);
            QDomElement rot = og_component.firstChildElement(SL_ROT);
            QDomElement scale = og_component.firstChildElement(SL_SCALE);

            node->SetPosition(pos.attribute(SL_X).toFloat(), pos.attribute(SL_Y).toFloat(),
                pos.attribute(SL_Z).toFloat());
            node->SetRotation(Ogre::Quaternion(rot.attribute(SL_QW).toFloat(),
                rot.attribute(SL_QX).toFloat(), rot.attribute(SL_QY).toFloat(), rot.attribute(SL_QZ).toFloat()));
            node->SetScale(Ogre::Vector3(scale.attribute(SL_X).toFloat(), scale.attribute(SL_Y).toFloat(),
                scale.attribute(SL_Z).toFloat()));
        }        

        //entity
        QDomElement unknown_mesh = og_component.firstChildElement(SL_SCALE).nextSiblingElement();
        if(unknown_mesh.nodeName() == SL_ENTITY)
        {
            const QDomElement& entity = unknown_mesh;

            MeshComponent* mesh = node->AddComponent<MeshComponent>(new MeshComponent(
                entity.attribute(SL_MESH_HANDLE), "",
                entity.attribute(SL_NAME)));

            for(QDomElement mat = entity.firstChildElement(); !mat.isNull(); mat = mat.nextSiblingElement())
            {
                QString material_handle = mat.attribute(SL_MATERIALNAME);
                uint32_t index = mat.attribute(SL_INDEX).toUInt();

                mesh->GetOgreEntity()->getSubEntity(index)->setMaterialName(material_handle.toStdString());
            }

            mesh->SetCastShadows(entity.attribute(SL_CAST_SHADOWS).toInt());
        }
        else if(unknown_mesh.nodeName() == SL_PLANE)
        {
            //plane
            const QDomElement& plane = unknown_mesh;
            if(!plane.isNull())
            {
                //create mesh
                OgreProcedural::PlaneGenerator()
                    .setSizeX(plane.attribute(SL_SIZEX).toFloat())
                    .setSizeY(plane.attribute(SL_SIZEY).toFloat())
                    .setEnableNormals(plane.attribute(SL_ENABLENORMALS).toInt())
                    .setNumSegX(plane.attribute(SL_SEGMENTSX).toInt())
                    .setNumSegY(plane.attribute(SL_SEGMENTSY).toInt())
                    .setNumTexCoordSet(plane.attribute(SL_NUMTEXCOORD).toInt())
                    .setUTile(plane.attribute(SL_UTILE).toFloat())
                    .setVTile(plane.attribute(SL_VTILE).toFloat())
                    .setNormal(Ogre::Vector3( plane.firstChildElement(SL_NORMAL).attribute(SL_X).toFloat(),
                    plane.firstChildElement(SL_NORMAL).attribute(SL_Y).toFloat(),
                    plane.firstChildElement(SL_NORMAL).attribute(SL_Z).toFloat()))
                    .realizeMesh(plane.attribute(SL_NAME).toStdString());

                //add entity
                node->AddComponent<MeshComponent>(new MeshComponent(
                    plane.attribute(SL_NAME),
                    plane.attribute(SL_MATERIAL),
                    plane.attribute(SL_NAME)));
            }
        }
    }

    return node;
}

Node* SceneLoader::_LoadSound(const QDomElement& og_component, Node* dt_node)
{
    Node* node = dt_node;

    if(!og_component.isNull())
    {
        QString name = og_component.attribute(SL_NAME);

        if(node == nullptr)
        {
            node = mScene->AddChildNode(new Node(name + "_node"));

            QDomElement pos = og_component.firstChildElement(SL_POS);

            node->SetPosition(pos.attribute(SL_X).toFloat(), pos.attribute(SL_Y).toFloat(),
                pos.attribute(SL_Z).toFloat());
        }

        SoundComponent* s = node->AddComponent<SoundComponent>(new SoundComponent(og_component.attribute(SL_SOUNDNAME), name));
        s->SetVolume(og_component.attribute(SL_SOUNDVOL).toFloat());
    }

    return node;
}