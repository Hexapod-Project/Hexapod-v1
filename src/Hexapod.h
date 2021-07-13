#ifndef HEXAPOD_H
#define HEXAPOD_H

#include "Leg.h"
#include "Gait.h"
#include "GaitGroup.h"
#include "Adafruit_PWMServoDriver.h"
#include "../includes/HexapodConstants.h"
#include "Wire.h"

class Hexapod
{
public:
    void setup();
    void update();

    int mInputGaitType = GAITTYPE::TRIPOD;

    void updateDirs(float moveDir = -1, float turnDir = -1, float transDir = -1, float rotDir = -1);
    void setMisc(uint8_t miscState);
    void calibrateMode(uint16_t hipAngle = 90, uint16_t femurAngle = 90, uint16_t tibiaAngle = 0);
    uint8_t getStanceMisc();
    uint8_t getGaitTypeMisc();

private:
    bool mCalibrateMode = false;

    Adafruit_PWMServoDriver mServoDriverR = Adafruit_PWMServoDriver(0x41),
                            mServoDriverL = Adafruit_PWMServoDriver(0x40);

    Mat4 mBaseMatrix, mBodyMatrix;
    Vec3 mBodyStartPos;
    Vec3 mBodyPos, mBodyRot;

    MOVETYPE mMoveTypeBtn = MOVETYPE::WALK;
    MOVETYPE mMoveType = MOVETYPE::WALK;

    MOVESTATE mMoveState = MOVESTATE::STOPPED;

    Leg mLegs[LEG_COUNT];

    Gait mGaits[4];
    GAITTYPE mGaitType = GAITTYPE::TRIPOD;
    LEG *mLegIndices;
    Gait *mCurrGait;
    int mGaitGrpIdx;
    int mGroupStoppedCount = 0;
    int mCurrGaitGrpSize;
    int mLegIndicesSize;
    float mStepTimeOffset;

    Vec3 mBodyStepStartPos;
    Vec3 mLegStepStartPos[LEG_COUNT];
    float mLegStepStartRot[LEG_COUNT];
    Vec3 mStepDist[LEG_COUNT];
    float mPrevStepHeight[LEG_COUNT];

    float mStepRotAngle;
    float mBodyStepStartYaw;

    unsigned long mStepStartTime;
    int mStepDuration;
    float mStepDistMulti;
    float mStepHeight;
    float mBaseStepHeight;

    BTDATA_MISC mStance = BTDATA_MISC::CROUCH;

    float mFaceDir = FORWARD, mTargetFaceDir = FORWARD;
    float mFaceDirDiff;
    float mMoveDir = 0;
    float mCosMoveDir, mSinMoveDir;
    float mTurnDir = 0;

    void initLegs();
    void setLegsPos();
    void initGaits();
    void updateLegs();    
    void calcMoveDir();
    void walk();
    void setNextStepRot();
    void setNextStep();
    void initStep();
    void setStance(float height, BTDATA_MISC stance);
    void transRotBody(float transDir, float rotDir);
};

#endif