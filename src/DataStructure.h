#pragma once

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