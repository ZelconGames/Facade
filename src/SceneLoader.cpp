#include "SceneLoader.h"

#include "Graphics/CameraComponent.hpp"
#include "Graphics/MeshComponent.hpp"
#include "Graphics/LightComponent.hpp"

#include <QtXml/QtXml>
#include <OgreProcedural.h>

Scene* SceneLoader::LoadScene(QString path)
{
    Scene* scene = nullptr;
    QFile file(path);
    QDomDocument doc;
    if(!file.open(QIODevice::ReadOnly)) {
        dt::Logger::Get().Error("Couldn't open file " + path);
        return nullptr;
    }
    cout << "Loading result: " << endl;
    if(doc.setContent(&file))
    {
        scene = new Scene(path);
        OgreProcedural::Root::getInstance()->sceneManager = scene->GetSceneManager();

        QDomElement root = doc.documentElement();

        for(QDomElement node = root.firstChildElement(); !node.isNull(); node = node.nextSiblingElement())
        {
            if(node.nodeName() == SL_CAMERA)
            {
                _LoadCamera(scene, node);
            }
            else if(node.nodeName() == SL_NODES)
            {
                for(QDomElement mesh_node = node.firstChildElement(); !mesh_node.isNull(); mesh_node = mesh_node.nextSiblingElement())
                {
                    _LoadMesh(scene, mesh_node);
                }
            }
            else if(node.nodeName() == SL_LIGHT)
            {
                _LoadLight(scene, node);
            }
        }
    }

    return scene;
}

void SceneLoader::_LoadCamera(Scene* scene, const QDomElement& node)
{
    if(!node.isNull() && scene)
    {
        //Node* dt_node = scene->AddChildNode(new Node(node.attribute(SL_NAME)));
        Node* dt_node = scene->AddChildNode(new Node(node.attribute(SL_NAME)));
        dt_node->AddComponent<CameraComponent>(new CameraComponent(node.attribute(SL_NAME)));
        QDomElement pos = node.firstChildElement(SL_POS);
        QDomElement rot = node.firstChildElement(SL_ROT);

        dt_node->SetPosition(pos.attribute(SL_X).toFloat(), pos.attribute(SL_Y).toFloat(),
            pos.attribute(SL_Z).toFloat());
        dt_node->SetRotation(Ogre::Quaternion(rot.attribute(SL_QW).toFloat(),
            rot.attribute(SL_QX).toFloat(), rot.attribute(SL_QY).toFloat(), rot.attribute(SL_QZ).toFloat()));
    }
}

void SceneLoader::_LoadLight(Scene* scene, const QDomElement& node)
{
    if(!node.isNull() && scene)
    {
        Node* dt_node = scene->AddChildNode(new Node(node.attribute(SL_NAME)));
        dt_node->AddComponent<LightComponent>(new LightComponent(node.attribute(SL_NAME)))->SetCastShadows(
            node.attribute(SL_CAST_SHADOWS).toInt());
        QDomElement pos = node.firstChildElement(SL_POS);
        QDomElement dir = node.firstChildElement(SL_DIRECTION);

        dt_node->SetPosition(pos.attribute(SL_X).toFloat(), pos.attribute(SL_Y).toFloat(),
            pos.attribute(SL_Z).toFloat());
        dt_node->SetDirection(Ogre::Vector3(dir.attribute(SL_X).toFloat(), dir.attribute(SL_Y).toFloat(),
            dir.attribute(SL_Z).toFloat()));
    }
}

void SceneLoader::_LoadMesh(Scene* scene, const QDomElement& node)
{
    if(!node.isNull() && scene)
    {
        Node* dt_node = scene->AddChildNode(new Node(node.attribute(SL_NAME)));
        QDomElement pos = node.firstChildElement(SL_POS);
        QDomElement rot = node.firstChildElement(SL_ROT);
        QDomElement scale = node.firstChildElement(SL_SCALE);

        dt_node->SetPosition(pos.attribute(SL_X).toFloat(), pos.attribute(SL_Y).toFloat(),
            pos.attribute(SL_Z).toFloat());
        dt_node->SetRotation(Ogre::Quaternion(rot.attribute(SL_QW).toFloat(),
            rot.attribute(SL_QX).toFloat(), rot.attribute(SL_QY).toFloat(), rot.attribute(SL_QZ).toFloat()));
        dt_node->SetScale(Ogre::Vector3(scale.attribute(SL_X).toFloat(), scale.attribute(SL_Y).toFloat(),
            scale.attribute(SL_Z).toFloat()));

        //entity
        QDomElement entity = node.firstChildElement(SL_ENTITY);
        if(entity.hasChildNodes())
        {
            MeshComponent* mesh = dt_node->AddComponent<MeshComponent>(new MeshComponent(
                entity.attribute(SL_MESH_HANDLE), "",
                entity.attribute(SL_NAME)));

            for(QDomElement mat = entity.firstChildElement(); !mat.isNull(); mat = mat.nextSiblingElement())
            {
                //auto material_handle = mat.attribute(SL_MATERIALNAME);
                //
                // Todo: Add the material loading logic here. Just fill it!!!!
                //
            }

            mesh->SetCastShadows(entity.attribute(SL_CAST_SHADOWS).toInt());
        }

        //plane
        QDomElement plane = node.firstChildElement(SL_PLANE);
        if(plane.hasChildNodes())
        {
            //create mesh
            OgreProcedural::PlaneGenerator()
                .setSizeX(plane.attribute(SL_SIZEX).toFloat())
                .setSizeY(plane.attribute(SL_SIZEY).toFloat())
                .setEnableNormals(plane.attribute(SL_ENABLENORMALS).toInt())
                .setNumSegX(plane.attribute(SL_SEGMENTSX).toInt())
                .setNumSegY(plane.attribute(SL_SEGMENTSY).toInt())
                //.setNumTexCoordSet(plane.attribute(SL_NUMTEXCOORD).toInt())
               // .setUTile(plane.attribute(SL_UTILE).toFloat())
                //.setVTile(plane.attribute(SL_VTILE).toFloat())
                .setNormal(Ogre::Vector3( plane.firstChildElement(SL_NORMAL).attribute(SL_X).toFloat(),
                                          plane.firstChildElement(SL_NORMAL).attribute(SL_Y).toFloat(),
                                          plane.firstChildElement(SL_NORMAL).attribute(SL_Z).toFloat() ))
                .realizeMesh(plane.attribute(SL_NAME).toStdString());

            //add entity
            //MeshComponent* mesh =
            dt_node->AddComponent<MeshComponent>(new MeshComponent(
                plane.attribute(SL_NAME),
                plane.attribute(SL_MATERIAL),
                plane.attribute(SL_NAME)));
        }

        
    }
}
