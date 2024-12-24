/* --- Track.h --- */

/* ------------------------------------------
Author: User
Date: 11/19/2024
------------------------------------------ */

#ifndef TRACK_H
#define TRACK_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "DataStructure.h"

class ControlPoint;
class ShaderProgram;
class Model;

class Track
{
public:
    Track();
    ~Track();

    void Render(ShaderProgram *program);
    void RenderID(ShaderProgram *program);
    void RenderSleeper(ShaderProgram *program);

    void setTrackMode(const TrackMode &newTrackMode);
    void setNewTension(const float &tension);

    void setSelectedPointIndex(const int &index);

    const float getTrackLength() const { return trackLength; }

    void setControlPointPosition(const glm::vec3 &position);
    void addControlPointRotation(ControlPointRotation rotationType);
    void createNewPoint();
    const glm::mat4 getTrainMatrix(float time);
    const glm::mat4 getTrainMatrixParam(float length);
    const glm::vec3 &getTrainPosition() const { return current.position; }
    const glm::vec3 &getTrainOrientation() const { return current.orientation; }
    const glm::vec3 &getTrainUp() const { return currentUp; }

    void setIsParam(bool isParam) { this->isParam = isParam; }
    const bool getIsParam() const { return isParam; }

private:
    struct TrackNode
    {
        glm::vec3 position;
        glm::vec3 orientation;
    };

    struct TrackObject
    {
        GLuint VAO;
        GLuint VBO;
        glm::mat4 model;
    };

    std::vector<TrackNode> m_nodes;
    std::vector<ControlPoint> m_controlPoints;
    TrackObject m_trackObject;
    TrackMode trackMode;
    Model *m_sleeper;

    TrackNode current;
    glm::vec3 currentUp;

    float m_tension;
    float m_duration;

    int selectedPointIndex;

    float trackLength;

    std::vector<float> pointAtLength;

    bool isParam;

private:
    void updateTrack();
    void createLinearTrack();
    void createBezierTrack();
    void createBSplineTrack();
    void createCarinalTrack();
    void createTrackObject();

    void computeBSplineBasis(TrackNode &B0, TrackNode &B1, TrackNode &B2, TrackNode &B3);
    void computeCarinalBasis(TrackNode &B0, TrackNode &B1, TrackNode &B2, TrackNode &B3);
    void createPartBazier(TrackNode &startNode, TrackNode &ctrl0, TrackNode &ctrl1, TrackNode &endNode);

    int searchPositionIndex(float length);
};

#endif // TRACK_H
