#include "Node.h"

void Node::setBase(Vec3 pos, Vec3 rot)
{
    mBasePos = pos;
    mBaseRot = rot;

    mBaseMatrix = mBaseMatrix.translate(pos);
    mBaseMatrix = mBaseMatrix.rotate(rot);

    mLocalMatrix.set(mBaseMatrix);
    mWorldMatrix.set(mLocalMatrix);
}

void Node::updateMatrix()
{
    mLocalMatrix = mBaseMatrix;

    mLocalMatrix.translate(mCurrentPos);
    mLocalMatrix.rotate(mCurrentRot);

    if (mParent)
        mWorldMatrix = mParent->mWorldMatrix.multiply(mLocalMatrix);
    else
        mWorldMatrix = mLocalMatrix;

    if (mChild != nullptr)
        mChild->updateMatrix();
}

void Node::setParent(Node *parent)
{
    if(mParent == parent)
        return;

    if (mParent)
        mParent->setChild(nullptr);

    mParent = parent;

    updateMatrix();

    mParent->setChild(this);
}

void Node::setChild(Node *child)
{
    if(mChild == child)
        return;

    if(mChild)
        mChild->setParent(nullptr);

    mChild = child;

    mChild->updateMatrix();

    if (mChild->mParent != this)
        child->setParent(this);
}

Vec3 Node::getLocalPos()
{
    return mLocalMatrix.getPos();
}

Vec3 Node::getLocalPos(Mat4 rootInverseMatrix)
{
    return rootInverseMatrix.multiply(mWorldMatrix).getPos();
}

Vec3 Node::getWorldPos()
{
    return mWorldMatrix.getPos();
}

void Node::setBasePos(Vec3 pos)
{
    setBase(pos, mBaseRot);
}