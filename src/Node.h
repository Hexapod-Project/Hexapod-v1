#ifndef NODE_H
#define NODE_H

#include "Datatypes.h"

class Node
{
public:
    virtual void setBase(Vec3 pos, Vec3 rot);
    virtual void setParent(Node *parent);
    virtual void setChild(Node *child);
    virtual void updateMatrix();
    virtual Vec3 getLocalPos();
    virtual Vec3 getLocalPos(Mat4 rootInverseMatrix);
    virtual Vec3 getWorldPos();
    virtual void setBasePos(Vec3 pos);

    Vec3 mBasePos;
    Vec3 mBaseRot;

    //Used to track the translated position
    Vec3 mCurrentPos;
    //Used to track the rotations
    Vec3 mCurrentRot;

    Mat4 mBaseMatrix;
    Mat4 mLocalMatrix;
    Mat4 mWorldMatrix;

    Node *mParent = nullptr;
    Node *mChild = nullptr;
};

#endif