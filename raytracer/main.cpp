#include "world/World.hpp"
#include "cameras/Camera.hpp"

int main(){
    World world;
    world.build();
    world.camera_ptr->render_scene(world);

    return 0;
}