#include "Irrlicht/Irrlicht.h"
#include "DESteer/IrrlichtMobileEntity.hpp"
#include "DESteer/IrrlichtBaseEntity.hpp"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace desteer;

int main()
{

    const s32 randLength = 1024;

	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, dimension2d<u32>(1024, 768), 32, false, false, true, 0);
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();

	//ICameraSceneNode * camera = smgr->addCameraSceneNode();
	smgr->addCameraSceneNodeFPS();

    u32 tileNumber = 128;
	IAnimatedMesh* groundMesh = smgr->addHillPlaneMesh(
        "",
        dimension2d<f32>(8,8),
        dimension2d<u32>(tileNumber,tileNumber),
        0,
        0.0f,
        dimension2df(0,0),
        dimension2df(tileNumber,tileNumber)
        );

    IAnimatedMeshSceneNode * groundNode = smgr->addAnimatedMeshSceneNode(groundMesh);
    groundNode->setMaterialTexture(0,driver->getTexture("../media/grid2.png"));
    groundNode->setMaterialFlag(EMF_LIGHTING,false);
    groundNode->setPosition(vector3df(0,-2,0));
    ISceneNode * cube = smgr->addCubeSceneNode(4);
    ISceneNode * cube2 = smgr->addCubeSceneNode(4);

    cube->setMaterialFlag(EMF_LIGHTING,false);
    cube->setMaterialTexture(0,driver->getTexture("../media/v1-solid.png"));
    cube2->setMaterialFlag(EMF_LIGHTING,false);
    cube2->setMaterialTexture(0,driver->getTexture("../media/v2-solid.png"));




    IrrlichtMobileEntity * Entity1 = new IrrlichtMobileEntity(cube ,vector3df(0,0,0)  );
    IrrlichtMobileEntity * Entity2 = new IrrlichtMobileEntity(cube2,vector3df(0,0,300));

    SteeringBehaviors* Entity1Steering = new SteeringBehaviors(Entity1);
    Entity1->SetSteering(Entity1Steering);
    Entity1Steering->HideOn(Entity2);


    SteeringBehaviors * Entity2Steering = new SteeringBehaviors(Entity2);
    //Entity2Steering->PursuitOn(Entity1);
    Entity2->SetSteering(Entity2Steering);

    u32 then = device->getTimer()->getTime();

    srand(device->getTimer()->getRealTime());
    f32 timeUpdate = 0;

    EntityGroup obstacles;

    for(int i = 0; i < 20; i++)
    {
        ISceneNode* s = smgr->addSphereSceneNode(20);
        IrrlichtBaseEntity * e = new IrrlichtBaseEntity(s);

        s->setPosition(vector3df(rand()%randLength - (randLength/2),0,rand()%randLength - (randLength/2)));
    //    s->setPosition(vector3df(0,0,50));
        obstacles.push_back(e);
    }

    Entity1Steering->AvoidObstaclesOn(obstacles);
    Entity2Steering->AvoidObstaclesOn(obstacles);

    while(device->run())
	{
	    const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;
        timeUpdate += frameDeltaTime;

        if(timeUpdate > 3)
        {
            core::stringw str = L"DESteer v0.0.1 ";
			str += L" FPS: ";
			str += (s32)driver->getFPS();
			device->setWindowCaption(str.c_str());
			timeUpdate = 0;
		}

        Entity1->Update(frameDeltaTime);
        Entity2->Update(frameDeltaTime);

	    //camera->setTarget(Entity1->Position());
        //camera->setPosition((Entity1->Position() - Entity1->ForwardVector()*100) + vector3df(0,100,0) );

        driver->beginScene(true, true, SColor(255,100,101,140));
            smgr->drawAll();
		driver->endScene();
	}

	device->drop();

	return 0;
}
