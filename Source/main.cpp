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

	ICameraSceneNode * camera = smgr->addCameraSceneNode();

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

    vector3df target = vector3df(rand()%randLength - (randLength/2),0,rand()%randLength - (randLength/2));

    vector3df e2Position = vector3df(rand()%randLength - (randLength/2),0,rand()%randLength - (randLength/2));
    IrrlichtMobileEntity * Entity1 = new IrrlichtMobileEntity(cube,vector3df(0,0,0),1,50,50);
    IrrlichtMobileEntity * Entity2 = new IrrlichtMobileEntity(cube2,e2Position,1,100,100);

    SteeringBehaviors* Entity1Steering = new SteeringBehaviors(Entity1);
    Entity1->SetSteering(Entity1Steering);
    //Entity1Steering->PursuitOn(Entity2);
    Entity1Steering->SetTarget(vector3df(0,0,150));
    Entity1Steering->SetArriveTolerance(25);
    Entity1Steering->ToggleArrive();


    SteeringBehaviors * Entity2Steering = new SteeringBehaviors(Entity2);
    Entity2Steering->ToggleWander();
    Entity2Steering->EvadeOn(Entity1);
    Entity2->SetSteering(Entity2Steering);

    u32 then = device->getTimer()->getTime();

    srand(device->getTimer()->getRealTime());
    f32 timeUpdate = 0;

    EntityGroup obstacles;



    for(int i = 0; i < 1; i++)
    {
        ISceneNode* s = smgr->addSphereSceneNode(20);
        IrrlichtBaseEntity * e = new IrrlichtBaseEntity(s);

        //s->setPosition(vector3df(rand()%randLength - (randLength/2),0,rand()%randLength - (randLength/2)));
        s->setPosition(vector3df(0,0,100));
        //s->setDebugDataVisible(EDS_FULL);

        obstacles.push_back(e);
    }

    Entity1Steering->AvoidObstaclesOn(obstacles);
    Entity2Steering->AvoidObstaclesOn(obstacles);

/*
    printf("Radius Test \n");
    printf("Entity1 Radius: %f \n ",Entity1->Radius());


    printf("VectorTest \n");
    Entity1->SetPosition(vector3df(1,0,1));
    printf("Entity 1 current position is X: %f Z: %f \n",Entity1->Position().X,Entity1->Position().Z);
    Entity1->SetForwardVector(vector3df(0,0,1));
    vector3df worldOrigin = Entity1->transformWorldVectToLocal(vector3df(0,0,0));

    printf("Entity 1 current heading is X: %f Z: %f \n",Entity1->ForwardVector().X,Entity1->ForwardVector().Z);
    printf(" -- \n Origin should be 0,0 in worldspace, in localspace it should be -1,-1 \n");
    printf("Origin is actually X: %f Z: %f \n\n",worldOrigin.X,worldOrigin.Z);

    Entity1->SetForwardVector(vector3df(1,0,0));
    worldOrigin = Entity1->transformWorldVectToLocal(vector3df(0,0,0));
    printf("Changing Heading to (1,0,0) \n -- \n");
    printf("Origin should now be 0,0 in worldspace and in localspace shold be 1,-1 \n");
    printf("Origin is actually X: %f Z: %f \n\n",worldOrigin.X,worldOrigin.Z);

    Entity1->SetForwardVector(vector3df(0,0,-1));
    worldOrigin = Entity1->transformWorldVectToLocal(vector3df(0,0,0));
    printf("Changing Heading to (0,0,-1) \n -- \n");
    printf("Origin should now be 0,0 in worldspace and in localspace shold be 1,1 \n");
    printf("Origin is actually X: %f Z: %f \n\n",worldOrigin.X,worldOrigin.Z);

    Entity1->SetForwardVector(vector3df(-1,0,0));
    worldOrigin = Entity1->transformWorldVectToLocal(vector3df(0,0,0));
    printf("Changing Heading to (-1,0,0) \n -- \n");
    printf("Origin should now be 0,0 in worldspace and in localspace shold be -1,1 \n");
    printf("Origin is actually X: %f Z: %f \n\n",worldOrigin.X,worldOrigin.Z);

    */

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

	    camera->setTarget(Entity1->Position());
        camera->setPosition((Entity1->Position() - Entity1->ForwardVector()*100) + vector3df(0,100,0) );

        driver->beginScene(true, true, SColor(255,100,101,140));
            smgr->drawAll();
		driver->endScene();
	}

	device->drop();

	return 0;
}
