#include "AnimationToolkit-basecode.h"
#include "AFramework.h"
#include "ASkeletonDrawer.h"
#include "AGLObjects.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <string>
#include <ode/ode.h>

class APhysicsViewer : public AFramework
{
public:
   APhysicsViewer() : AFramework(AFramework::Perspective) {}
   virtual ~APhysicsViewer() 
   {
      shutdownSimulation();
      dCloseODE();
   }

   void shutdownSimulation()
   {
      dJointGroupDestroy(_contacts);
      for (unsigned int i = 0; i < _kinematicBodies.size(); i++)
      {
         dBodyDestroy(_kinematicBodies[i].rigidBody);
      }
      _kinematicBodies.clear();
      for (unsigned int i = 0; i < _dynamicBodies.size(); i++)
      {
         dBodyDestroy(_dynamicBodies[i].rigidBody);
      }
      _dynamicBodies.clear();
      dWorldDestroy(_world);
      dSpaceDestroy(_space);
   }

   void setupSimulation()
   {
      _time = 0;
      _world = dWorldCreate();
      _space = dSweepAndPruneSpaceCreate(0, dSAP_AXES_XYZ);
      _ground = dCreatePlane(_space, 0,1,0,0);
      _contacts = dJointGroupCreate(0);

      dWorldSetGravity(_world, 0, -10, 0);
      dMassSetSphere(&_sphereMass, 5, 2);
      createKinematicBodies(_sphereMass);

      _boxSize = 50.0;
      dMassSetBox (&_boxMass,1,_boxSize,_boxSize,_boxSize);
      dMassAdjust (&_boxMass, 1);
      createWall(_boxSize, _boxMass);
   }

   void setup()
   {
      _drawPhysics = false;

      ABVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _motion);
      _motion.update(_skeleton, 0);

      dInitODE2(0);
      setupSimulation();
   }

   void createWall(double boxSize, const dMass& boxMass)
   {
      // Create a wall for the character to crash into
      // Use the given box size and mass to initialize dynamic rigid bodies
      // create a DynamicRigidBody to represent each object and 
      //   save the result in _dynamicBodies
      // See the ODE documentation for 
      //     dCreateBox
      //     dBodyCreate
      //     dBodySetPosition
      //     dBodySetMass
      //     dBodySetBody
   }

   void createKinematicBodies(const dMass& mass)
   {
      // for each joint, create a spherical kinematic body
      // You should initialize the body with the joint's current position
      //   and the given mass. 
      // The kinematic body, geometry, and character limb are stored 
      //   together in KinematicRigidBody
      // Create a KinematicRigidBody for your new objects and save the 
      //   result in _kinematicBodies
      // See the ODE documentation for 
      //     dCreateSphere
      //     dBodyCreate
      //     dBodySetPosition
      //     dBodySetMass
      //     dBodySetBody
      //     dBodySetKinematic

   }

   void updateKinematicBodies()
   {
      // for each joint, update its corresponding kinematic body
      // See the ODE documentation for 
      //     dBodySetPosition
   }

   void update()
   {
      _time += 0.5*dt();
      if (_time < _motion.getDuration()) _motion.update(_skeleton, _time);

      updateKinematicBodies();
      dSpaceCollide(_space, this, collideCb);
      dWorldStep(_world, 0.01);
      dJointGroupEmpty(_contacts);
   }

   void draw()
   {  
      if (_drawPhysics)
      {
         for (unsigned int i = 0; i < _kinematicBodies.size(); i++)
         {
            const dReal* pos = dBodyGetPosition(_kinematicBodies[i].rigidBody); 
            ASetMaterial(AVector3(0,0,1));
            ADrawEllipse(AVector3(pos[0], pos[1], pos[2]), 5*AVector3(1,1,1));
         }
      }
      else
      {
        _drawer.draw(_skeleton);
      }

      for (unsigned int i = 0; i < _dynamicBodies.size(); i++)
      {
         const dReal* pos = dBodyGetPosition(_dynamicBodies[i].rigidBody); 
         const dReal* ori = dBodyGetRotation(_dynamicBodies[i].rigidBody); 
         ASetMaterial(AVector3(0,1,1));
         AVector3 boxPos(pos[0], pos[1], pos[2]);
         AMatrix3 boxOri(ori[0], ori[1], ori[2],
                         ori[4], ori[5], ori[6],
                         ori[8], ori[9], ori[10]);
         ADrawCube(boxPos, boxOri, _boxSize*AVector3(1,1,1));
      }
   }

   void keyPress(unsigned char key, int specialKey, int x, int y) 
   {
      if (key == ' ') 
      {
         shutdownSimulation();
         setupSimulation();
      }
      else if (key == 'd') _drawPhysics = !_drawPhysics;
   }

   static void collideCb(void* data, dGeomID o1, dGeomID o2)
   {
      ((APhysicsViewer*)data)->collide(o1, o2);
   }

   void collide(dGeomID o1, dGeomID o2)
   {
      int i,n;

      dBodyID b1 = dGeomGetBody(o1);
      dBodyID b2 = dGeomGetBody(o2);
      if (b1 && b2 && dAreConnected(b1, b2))
         return;

      const int N = 4;
      dContact contact[N];
      n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
      if (n > 0) 
      { 
         for (i=0; i<n; i++) 
         {
            contact[i].surface.mode = dContactBounce;

            contact[i].surface.mu = dInfinity;
            contact[i].surface.slip1 = 0.0;
            contact[i].surface.slip2 = 0.0;
            contact[i].surface.soft_erp = 0.8;
            contact[i].surface.soft_cfm = 0.01;

            dJointID c = dJointCreateContact (_world,_contacts,contact+i);
            dJointAttach (c,dGeomGetBody(o1),dGeomGetBody(o2));
         }
      }
   }

   ASkeletonDrawer _drawer;
   ASkeleton _skeleton;
   AMotion _motion;
   dSpaceID _space;
   dWorldID _world;
   dGeomID _ground;
   dJointGroupID _contacts;

   struct KinematicRigidBody
   {
      dGeomID sphere;
      dBodyID rigidBody;
      AJoint* joint;
   };
   dMass _sphereMass;
   std::vector<KinematicRigidBody> _kinematicBodies;

   struct DynamicRigidBody
   {
      dGeomID geom;
      dBodyID rigidBody;
   };
   std::vector<DynamicRigidBody> _dynamicBodies;
   double _boxSize;
   dMass _boxMass;

   bool _drawPhysics;
   double _time;
};

int main(int argc, char** argv)
{
   APhysicsViewer viewer;
   viewer.init(argc, argv);
   viewer.run();
   return 0;
}

