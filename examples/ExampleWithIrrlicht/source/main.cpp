#include "desteer/controller/SimpleSteeringController.hpp"
#include "desteer/factory/SimpleSteeringControllerFactory.hpp"
#include "irrlicht/irrlicht.h"
#include "IrrlichtMobileEntity.hpp"
#include "IrrlichtBaseEntity.hpp"
#include <boost/smart_ptr.hpp>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace desteer;
using namespace entity;
using namespace behavior;
using namespace controller;
using boost::shared_ptr;

class EventReceiver : public IEventReceiver
{
public:
        // This is the one method that we have to implement
        virtual bool OnEvent(const SEvent& event)
        {
                // Remember whether each key is down or up
                if (event.EventType == irr::EET_KEY_INPUT_EVENT)
                        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

                return false;
        }

        // This is used to check whether a key is being held down
        virtual bool IsKeyDown(EKEY_CODE keyCode) const
        {
                return KeyIsDown[keyCode];
        }

        EventReceiver()
        {
                for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                        KeyIsDown[i] = false;
        }

private:
        // We use this array to store the current state of each key
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main()
{
    EventReceiver eventReceiver;
	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, dimension2d<u32>(1024, 768), 32, false, false, true, &eventReceiver);
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();

	smgr->addCameraSceneNodeFPS();

    const s32 randLength = 1024;
    srand(device->getTimer()->getRealTime());


    //Creating the grid for unit measure, etc
    u32 tileNumber = 128;
	IAnimatedMesh* groundMesh = smgr->addHillPlaneMesh("", dimension2d<float>(8,8),dimension2d<u32>(tileNumber,tileNumber),0,0.0f,dimension2df(0,0),dimension2df(tileNumber,tileNumber));
    IAnimatedMeshSceneNode * groundNode = smgr->addAnimatedMeshSceneNode(groundMesh);
    groundNode->setMaterialTexture(0,driver->getTexture("../media/grid2.png"));
    groundNode->setMaterialFlag(EMF_LIGHTING,false);
    groundNode->setPosition(vector3df(0,-2,0));


    //obstacles for stuff
    shared_ptr<EntityGroup> obstacles(new EntityGroup());

    for(int i = 0; i < 20; i++)
    {
        ISceneNode* s = smgr->addSphereSceneNode(20);
        shared_ptr<IrrlichtBaseEntity> e(new IrrlichtBaseEntity(s));
        s->setPosition(vector3df(rand()%randLength - (randLength/2),0,rand()%randLength - (randLength/2)));
        obstacles->push_back(e);
    }

    //Nodes for vehicles
    ISceneNode * cube = smgr->addCubeSceneNode(4);
    ISceneNode * cube2 = smgr->addCubeSceneNode(4);
    cube->setMaterialFlag(EMF_LIGHTING,false);
    cube->setMaterialTexture(0,driver->getTexture("../media/v1-solid.png"));
    cube2->setMaterialFlag(EMF_LIGHTING,false);
    cube2->setMaterialTexture(0,driver->getTexture("../media/v2-solid.png"));

    //Creating the actual vehicles
    shared_ptr<IrrlichtMobileEntity> Entity1(new IrrlichtMobileEntity(cube ,vector3df(0,0,0), 1, 60, 150));
    shared_ptr<IrrlichtMobileEntity> Entity2(new IrrlichtMobileEntity(cube2,vector3df(0,0,300), 1, 200, 25));

    //Creating the steering conrollers, factory also sets steering on entity
    shared_ptr<SimpleSteeringController> Entity1Steering = SimpleSteeringControllerFactory::CreateController(Entity1);
    shared_ptr<SimpleSteeringController> Entity2Steering = SimpleSteeringControllerFactory::CreateController(Entity2);


    //Setting up other params for behaviors
    Entity1Steering->SetObstacles(obstacles);
    Entity1Steering->SetHideTarget(Entity2);
    Entity1Steering->SetBehaviorFlag(EBF_HIDE,true);
    Entity1Steering->SetBehaviorFlag(EBF_AVOID,true);

    Entity2Steering->SetObstacles(obstacles);
    Entity2Steering->SetPursuitTarget(Entity1);
    Entity2Steering->SetBehaviorFlag(EBF_PURSUIT,true);
    Entity2Steering->SetBehaviorFlag(EBF_AVOID,true);

    //vars for tracking time between frames. This allows framerate independent motion state updates.
    u32 then = device->getTimer()->getTime();
    float timeUpdate = 0;

    while(device->run())
	{

	    const u32 now = device->getTimer()->getTime();
        const float frameDeltaTime = (float)(now - then) / 1000.f; // Time in seconds
        then = now;
        timeUpdate += frameDeltaTime;

        if(timeUpdate > 1)
        {
            core::stringw str = L"desteer v0.0.1  FPS: ";
            str += (s32)driver->getFPS();
			device->setWindowCaption(str.c_str());
			timeUpdate = 0;
		}

        //Do behavior updates before the rendering.
        Entity1->Update(frameDeltaTime);
        Entity2->Update(frameDeltaTime);

        driver->beginScene(true, true, SColor(255,100,101,140));
            smgr->drawAll();
		driver->endScene();

	    if(eventReceiver.IsKeyDown(irr::KEY_ESCAPE)){
            device->closeDevice();
	    }
	}
    //Clean up irrlicht.
	device->drop();

	return 0;
}
