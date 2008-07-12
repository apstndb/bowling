#ifndef CONSTANT_H
#define CONSTANT_H
const bool FullScreen = true;
const float Factor = 10.0f;
//const unsigned int ResX = 1600, ResY = 1200;
//const unsigned int ResX = 1280, ResY = 1024;
const float DistanceToHeadPin = Factor*18.29f;
const unsigned int DefaultNumberOfFrames = 5;
const float LimitOfBallPosition = Factor*-6.0f;
const float PinsTriangleRadius = Factor*0.4f;
const float PinsHeight = Factor* 0.381f;
const float PinsRadius = Factor*0.121f/2;
const float PinsMass = 1.6f;
const float LaneLength = Factor*23.72f;
const float LaneWidth = Factor*1.05f;
const float LaneThick = Factor*0.2f;
const float LaneMargin = Factor*4.5f;
const float BallRadius = Factor*0.218f/2;
const float Pound = 0.5f;
const float BallMass = Pound*10;
const float BallSpeed = Factor*10.0f;
const float Gravity = Factor*9.8f;
const float Spin = 31.4f;
const unsigned int ArrowTimeForWay = 1000;
const unsigned int TimeUp = 4500;
const unsigned int LogoTime = 3000;
const unsigned int TitleTime = 4000;
#endif
