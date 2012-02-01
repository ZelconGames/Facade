#include "SceneLoaderTest.h"

#include "SceneLoader.h"

void Main::OnInitialize() {
dt::Scene* scene = nullptr;
    scene = SceneLoader::LoadScene("D:\\test.scene");
    if(scene)
        AddScene(scene);
}

void Main::UpdateStateFrame(double simulation_frame_time) {
}