/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "btCompoundShape.h"


#include "btCollisionShape.h"


btCompoundShape::btCompoundShape()
:m_localAabbMin(btScalar(1e30),btScalar(1e30),btScalar(1e30)),
m_localAabbMax(btScalar(-1e30),btScalar(-1e30),btScalar(-1e30)),
m_aabbTree(0),
m_collisionMargin(btScalar(0.)),
m_localScaling(btScalar(1.),btScalar(1.),btScalar(1.))
{
}


btCompoundShape::~btCompoundShape()
{
}

void	btCompoundShape::addChildShape(const btTransform& localTransform,btCollisionShape* shape)
{
	//m_childTransforms.push_back(localTransform);
	//m_childShapes.push_back(shape);
	btCompoundShapeChild child;
	child.m_transform = localTransform;
	child.m_childShape = shape;
	child.m_childShapeType = shape->getShapeType();
	child.m_childMargin = shape->getMargin();

	m_children.push_back(child);

	//extend the local aabbMin/aabbMax
	btVector3 localAabbMin,localAabbMax;
	shape->getAabb(localTransform,localAabbMin,localAabbMax);
	for (int i=0;i<3;i++)
	{
		if (m_localAabbMin[i] > localAabbMin[i])
		{
			m_localAabbMin[i] = localAabbMin[i];
		}
		if (m_localAabbMax[i] < localAabbMax[i])
		{
			m_localAabbMax[i] = localAabbMax[i];
		}

	}
}

void btCompoundShape::removeChildShape(btCollisionShape* shape)
{
   bool done_removing;
   
   // Find the children containing the shape specified, and remove those children.
   do
   {
      done_removing = true;
      
      for(int i = 0; i < m_children.size(); i++)
      {
         if(m_children[i].m_childShape == shape)
         {
            m_children.remove(m_children[i]);
            done_removing = false;  // Do another iteration pass after removing from the vector
            break;
         }
      }
   }
   while (!done_removing);
   
   recalculateLocalAabb();
}

void btCompoundShape::recalculateLocalAabb()
{
   // Recalculate the local aabb
   // Brute force, it iterates over all the shapes left.
   m_localAabbMin = btVector3(btScalar(1e30),btScalar(1e30),btScalar(1e30));
   m_localAabbMax = btVector3(btScalar(-1e30),btScalar(-1e30),btScalar(-1e30));
   
   //extend the local aabbMin/aabbMax
   for (int j = 0; j < m_children.size(); j++)
   {
      btVector3 localAabbMin,localAabbMax;
      m_children[j].m_childShape->getAabb(m_children[j].m_transform, localAabbMin, localAabbMax);
      for (int i=0;i<3;i++)
      {
         if (m_localAabbMin[i] > localAabbMin[i])
             m_localAabbMin[i] = localAabbMin[i];
         if (m_localAabbMax[i] < localAabbMax[i])
             m_localAabbMax[i] = localAabbMax[i];
      }
   }
}
	
   ///getAabb's default implementation is brute force, expected derived classes to implement a fast dedicated version
void btCompoundShape::getAabb(const btTransform& trans,btVector3& aabbMin,btVector3& aabbMax) const
{
	btVector3 localHalfExtents = btScalar(0.5)*(m_localAabbMax-m_localAabbMin);
	localHalfExtents += btVector3(getMargin(),getMargin(),getMargin());
	btVector3 localCenter = btScalar(0.5)*(m_localAabbMax+m_localAabbMin);
	
	btMatrix3x3 abs_b = trans.getBasis().absolute();  

	btPoint3 center = trans(localCenter);

	btVector3 extent = btVector3(abs_b[0].dot(localHalfExtents),
		   abs_b[1].dot(localHalfExtents),
		  abs_b[2].dot(localHalfExtents));
	aabbMin = center-extent;
	aabbMax = center+extent;

}

void	btCompoundShape::calculateLocalInertia(btScalar mass,btVector3& inertia) const
{
	//approximation: take the inertia from the aabb for now
	btTransform ident;
	ident.setIdentity();
	btVector3 aabbMin,aabbMax;
	getAabb(ident,aabbMin,aabbMax);
	
	btVector3 halfExtents = (aabbMax-aabbMin)*btScalar(0.5);
	
	btScalar lx=btScalar(2.)*(halfExtents.x());
	btScalar ly=btScalar(2.)*(halfExtents.y());
	btScalar lz=btScalar(2.)*(halfExtents.z());

	inertia[0] = mass/(btScalar(12.0)) * (ly*ly + lz*lz);
	inertia[1] = mass/(btScalar(12.0)) * (lx*lx + lz*lz);
	inertia[2] = mass/(btScalar(12.0)) * (lx*lx + ly*ly);

}




void btCompoundShape::calculatePrincipalAxisTransform(btScalar* masses, btTransform& principal, btVector3& inertia) const
{
   int n = m_children.size();

   btScalar totalMass = 0;
   btVector3 center(0, 0, 0);
   for (int k = 0; k < n; k++)
   {
      center += m_children[k].m_transform.getOrigin() * masses[k];
      totalMass += masses[k];
   }
   center /= totalMass;
   principal.setOrigin(center);

   btMatrix3x3 tensor(0, 0, 0, 0, 0, 0, 0, 0, 0);
   for (int k = 0; k < n; k++)
   {
      btVector3 i;
      m_children[k].m_childShape->calculateLocalInertia(masses[k], i);

      const btTransform& t = m_children[k].m_transform;
      btVector3 o = t.getOrigin() - center;
      
      //compute inertia tensor in coordinate system of compound shape
      btMatrix3x3 j = t.getBasis().transpose();
      j[0] *= i[0];
      j[1] *= i[1];
      j[2] *= i[2];
      j = t.getBasis() * j;
      
      //add inertia tensor
      tensor[0] += j[0];
      tensor[1] += j[1];
      tensor[2] += j[2];

      //compute inertia tensor of pointmass at o
      btScalar o2 = o.length2();
      j[0].setValue(o2, 0, 0);
      j[1].setValue(0, o2, 0);
      j[2].setValue(0, 0, o2);
      j[0] += o * -o.x(); 
      j[1] += o * -o.y(); 
      j[2] += o * -o.z();

      //add inertia tensor of pointmass
      tensor[0] += masses[k] * j[0];
      tensor[1] += masses[k] * j[1];
      tensor[2] += masses[k] * j[2];
   }

   tensor.diagonalize(principal.getBasis(), btScalar(0.00001), 20);
   inertia.setValue(tensor[0][0], tensor[1][1], tensor[2][2]);
}


	
