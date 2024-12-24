#pragma once
#include <glm/glm.hpp>

enum class TrackMode
{
    LINEAR,
    CARDINAL_CUBIC,
    CUBIC_B_SPLINE,
};

enum class CameraStatus
{
    WORLD,
    TRAIN,
    TOP,
};

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

enum class TrainStatus
{
    RUN,
    STOP,
};

enum class ControlPointRotation
{
    NONE,
    X_PLUS,
    X_MINUS,
    Z_PLUS,
    Z_MINUS,
};

struct ControlData
{
    CameraStatus cameraStatus;
    TrainStatus trainStatus;
    TrackMode trackMode;
    float cardinalTension;
    float trainTime;
    ControlPointRotation pointRoation;
    bool isParameterization;
    float currentLength;
};

struct Wave
{
    glm::vec2 direction;
    float amplitude;
    float waveLength;
    glm::vec4 color;
};
