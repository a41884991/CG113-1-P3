/* --- Track.cpp --- */

/* ------------------------------------------
author: User
date: 11/19/2024
------------------------------------------ */

#include "Track.h"
#include "ControlPoint/ControlPoint.h"
#include "ShaderProgram/ShaderProgram.h"
#include "Model/Model.h"
#include <iostream>

#define NODES_PER_LINE 25
#define SLEEPER_DISTANCE 0.2f
#define TRACK_WIDTH 0.1f
Track::Track()
{
    // Constructor
    m_controlPoints.push_back(ControlPoint(glm::vec3(0.0, 2.0, 2.0), 0));
    m_controlPoints.push_back(ControlPoint(glm::vec3(2.0, 2.0, 0.0), 1));
    m_controlPoints.push_back(ControlPoint(glm::vec3(0.0, 2.0, -2.0), 2));
    m_controlPoints.push_back(ControlPoint(glm::vec3(-2.0, 2.0, 0.0), 3));

    //
    glGenVertexArrays(1, &m_trackObject.VAO);
    glGenBuffers(1, &m_trackObject.VBO);
    glBindVertexArray(m_trackObject.VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    m_trackObject.model = glm::mat4(1.0f);

    m_sleeper = new Model("./resource/wooden_plank/Wooden_plank.obj");

    m_duration = 1.0f;
    selectedPointIndex = -1;

    trackLength = 0.0f;
    isParam = false;

    trackMode = TrackMode::LINEAR;
    updateTrack();
}

Track::~Track()
{
    // Destructor
}

void Track::Render(ShaderProgram *program)
{
    program->SetVec3("ourColor", glm::vec3(1.0f, 1.0f, 1.0f));
    program->SetMat4("model", m_trackObject.model);

    glLineWidth(5.0f);
    glBindVertexArray(m_trackObject.VAO);
    glDrawArrays(GL_LINES, 0, (m_nodes.size() - 1) * 2 * 2);
    glBindVertexArray(0);

    for (auto &point : m_controlPoints)
    {
        point.Render(program);
    }
}

void Track::RenderID(ShaderProgram *program)
{
    for (auto &point : m_controlPoints)
    {
        point.RenderID(program);
    }
}

void Track::RenderSleeper(ShaderProgram *program)
{
    float sleeperCount = static_cast<float>(trackLength / SLEEPER_DISTANCE);

    for (int i = 0; i < sleeperCount; ++i)
    {
        auto index = searchPositionIndex(i * SLEEPER_DISTANCE);
        auto node1 = m_nodes[index];
        auto node2 = m_nodes[(index + 1) % m_nodes.size()];

        glm::vec3 u = glm::normalize(node2.position - node1.position);
        glm::vec3 w = glm::normalize(glm::cross(u, node1.orientation));
        glm::vec3 v = glm::normalize(glm::cross(w, u));

        glm::mat4 rotation = glm::mat4(glm::vec4(u, 0.0f), glm::vec4(v, 0.0f), glm::vec4(w, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, node1.position + v * 0.01f);
        model *= rotation;
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

        program->SetMat4("model", model);
        m_sleeper->Render(program);
    }
    // for (int i = 0; i < m_nodes.size(); ++i)
    // {
    //     // if (trackMode != TrackMode::CUBIC_B_SPLINE && i % NODES_PER_LINE == 0)
    //     //     continue;

    //     auto node1 = m_nodes[i];
    //     auto node2 = m_nodes[(i + 1) % m_nodes.size()];

    //     glm::vec3 u = glm::normalize(node2.position - node1.position);
    //     glm::vec3 w = glm::normalize(glm::cross(u, node1.orientation));
    //     glm::vec3 v = glm::normalize(glm::cross(w, u));

    //     glm::mat4 rotation = glm::mat4(glm::vec4(u, 0.0f), glm::vec4(v, 0.0f), glm::vec4(w, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    //     glm::mat4 model = glm::mat4(1.0f);
    //     model = glm::translate(model, node1.position + v * 0.01f);
    //     model *= rotation;
    //     model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

    //     program->SetMat4("model", model);
    //     m_sleeper->Render(program);
    // }
}

void Track::setTrackMode(const TrackMode &newTrackMode)
{
    if (trackMode == newTrackMode)
        return;

    trackMode = newTrackMode;
    updateTrack();
}

void Track::setNewTension(const float &tension)
{
    if (m_tension == tension)
        return;

    m_tension = tension;

    if (trackMode == TrackMode::CARDINAL_CUBIC)
        updateTrack();
}

void Track::setSelectedPointIndex(const int &index)
{
    selectedPointIndex = index;
    m_controlPoints[0].setSelectedIndex(index);
}

void Track::setControlPointPosition(const glm::vec3 &position)
{
    if (selectedPointIndex == -1)
        return;

    m_controlPoints[selectedPointIndex].setPosition(position);

    updateTrack();
}

void Track::addControlPointRotation(ControlPointRotation rotationType)
{
    if (selectedPointIndex == -1 || rotationType == ControlPointRotation::NONE)
        return;

    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    float radian45 = glm::radians(45.0f);
    switch (rotationType)
    {
    case ControlPointRotation::X_PLUS:
        rotation.x = radian45;
        break;
    case ControlPointRotation::X_MINUS:
        rotation.x = -radian45;
        break;
    case ControlPointRotation::Z_PLUS:
        rotation.z = radian45;
        break;
    case ControlPointRotation::Z_MINUS:
        rotation.z = -radian45;
        break;

    default:
        break;
    }
    m_controlPoints[selectedPointIndex].addRoation(rotation);

    updateTrack();
}

void Track::createNewPoint()
{
    glm::vec3 position = (m_controlPoints.back().getPosition() + m_controlPoints.front().getPosition()) / 2.0f;

    m_controlPoints.push_back(ControlPoint(position, m_controlPoints.size()));
}

const glm::mat4 Track::getTrainMatrix(float time)
{
    glm::mat4 model = glm::mat4(1.0f);

    // 计算时间对应的节点索引和插值比例
    float alpha = (time / m_duration) * (m_nodes.size() - 1);
    int index = static_cast<int>(alpha);
    float t = alpha - index;

    // 获取当前节点和下一节点
    auto node1 = m_nodes[index];
    auto node2 = m_nodes[(index + 1) % m_nodes.size()];

    // 位置插值
    glm::vec3 position = (1.0f - t) * node1.position + t * node2.position;

    // 方向插值（线性插值）
    glm::vec3 orientation = glm::normalize((1.0f - t) * node1.orientation + t * node2.orientation);

    // 构建正交基
    glm::vec3 u = glm::normalize(node2.position - node1.position); // 轨道方向
    glm::vec3 w = glm::normalize(glm::cross(u, orientation));      // 法线
    glm::vec3 v = glm::normalize(glm::cross(w, u));                // 上方向

    TrackNode newNode = {position + v * 0.4f - u * 0.1f, u};
    current = newNode;
    currentUp = v;

    // 旋转矩阵
    glm::mat4 rotation = glm::mat4(
        glm::vec4(u, 0.0f),
        glm::vec4(v, 0.0f),
        glm::vec4(w, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    // 应用平移和旋转
    model = glm::translate(model, position);
    model *= rotation;

    return model;
}

const glm::mat4 Track::getTrainMatrixParam(float length)
{
    glm::mat4 model = glm::mat4(1.0f);

    int index = searchPositionIndex(length);
    float t = length - pointAtLength[index];

    auto node1 = m_nodes[index];
    auto node2 = m_nodes[(index + 1) % m_nodes.size()];
    // 位置插值
    glm::vec3 position = (1.0f - t) * node1.position + t * node2.position;

    // 方向插值（线性插值）
    glm::vec3 orientation = glm::normalize((1.0f - t) * node1.orientation + t * node2.orientation);

    // 构建正交基
    glm::vec3 u = glm::normalize(node2.position - node1.position); // 轨道方向
    glm::vec3 w = glm::normalize(glm::cross(u, orientation));      // 法线
    glm::vec3 v = glm::normalize(glm::cross(w, u));                // 上方向

    TrackNode newNode = {position + v * 0.4f - u * 0.1f, u};
    current = newNode;
    currentUp = v;

    // 旋转矩阵
    glm::mat4 rotation = glm::mat4(
        glm::vec4(u, 0.0f),
        glm::vec4(v, 0.0f),
        glm::vec4(w, 0.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    // 应用平移和旋转
    model = glm::translate(model, position);
    model *= rotation;

    return model;
}

void Track::updateTrack()
{
    switch (trackMode)
    {
    case TrackMode::LINEAR: // linear
        createLinearTrack();
        break;
    case TrackMode::CUBIC_B_SPLINE: // cubic_b_spline
        createBSplineTrack();
        break;
    case TrackMode::CARDINAL_CUBIC: // carinal
        createCarinalTrack();
        break;
    default:
        break;
    }
    createTrackObject();
}

void Track::createLinearTrack()
{
    m_nodes.clear();
    m_nodes.reserve(m_controlPoints.size() * NODES_PER_LINE + 1);
    pointAtLength.clear();
    pointAtLength.reserve(m_controlPoints.size() * NODES_PER_LINE + 1);

    trackLength = 0;

    std::vector<TrackNode> controlNodes;
    controlNodes.reserve(m_controlPoints.size());
    for (auto &point : m_controlPoints)
    {
        controlNodes.push_back({point.getPosition(), point.getOrientation()});
    }
    const float PERCENT = 1.0f / NODES_PER_LINE;

    for (int i = 0; i < controlNodes.size(); ++i)
    {
        TrackNode startPoint = controlNodes[i];
        TrackNode endPoint = controlNodes[(i + 1) % controlNodes.size()];

        for (int j = 0; j < NODES_PER_LINE; ++j)
        {
            TrackNode currentNode;

            float t = j * PERCENT;

            currentNode.position = (1 - t) * startPoint.position + t * endPoint.position;
            currentNode.orientation = (1 - t) * startPoint.orientation + t * endPoint.orientation;

            if (!m_nodes.empty())
            {
                trackLength += glm::length(currentNode.position - m_nodes.back().position);
            }
            else
            {
                trackLength = 0;
            }
            pointAtLength.push_back(trackLength);

            m_nodes.push_back(currentNode);
        }
    }

    trackLength += glm::length(m_nodes.back().position - m_nodes.front().position);
    m_nodes.push_back(m_nodes[0]);
}

void Track::createBezierTrack()
{
    m_nodes.clear();
    m_nodes.reserve(m_controlPoints.size() * NODES_PER_LINE + 1);

    TrackNode mid0 = {(m_controlPoints[0].getPosition() + m_controlPoints[1].getPosition()) / 2.0f, (m_controlPoints[0].getRotation() + m_controlPoints[1].getRotation()) / 2.0f};

    for (int i = 1; i < m_controlPoints.size() - 1; ++i)
    {
        TrackNode p0 = {m_controlPoints[i].getPosition(), m_controlPoints[i].getRotation()};
        TrackNode p1 = {m_controlPoints[i + 1].getPosition(), m_controlPoints[i + 1].getRotation()};
        TrackNode mid1 = {(p0.position + p1.position) / 2.0f, (p0.orientation + p1.orientation) / 2.0f};

        TrackNode ctrl0 = {(p0.position + mid0.position) / 2.0f, (p0.orientation + mid0.orientation) / 2.0f};
        TrackNode ctrl1 = {(p0.position + mid1.position) / 2.0f, (p0.orientation + mid1.orientation) / 2.0f};

        createPartBazier(mid0, ctrl0, ctrl1, mid1);

        mid0 = mid1;
    }

    TrackNode p0 = {m_controlPoints.back().getPosition(), m_controlPoints.back().getRotation()};
    TrackNode p1 = {m_controlPoints[0].getPosition(), m_controlPoints[0].getRotation()};
    TrackNode mid1 = {(p0.position + p1.position) / 2.0f, (p0.orientation + p1.orientation) / 2.0f};

    TrackNode ctrl0 = {(p0.position + mid0.position) / 2.0f, (p0.orientation + mid0.orientation) / 2.0f};
    TrackNode ctrl1 = {(p0.position + mid1.position) / 2.0f, (p0.orientation + mid1.orientation) / 2.0f};

    createPartBazier(mid0, ctrl0, ctrl1, mid1);

    mid0 = mid1;
    p0 = {m_controlPoints[0].getPosition(), m_controlPoints[0].getRotation()};
    p1 = {m_controlPoints[1].getPosition(), m_controlPoints[1].getRotation()};
    mid1 = {(p0.position + p1.position) / 2.0f, (p0.orientation + p1.orientation) / 2.0f};

    ctrl0 = {(p0.position + mid0.position) / 2.0f, (p0.orientation + mid0.orientation) / 2.0f};
    ctrl1 = {(p0.position + mid1.position) / 2.0f, (p0.orientation + mid1.orientation) / 2.0f};

    createPartBazier(mid0, ctrl0, ctrl1, mid1);

    m_nodes.push_back(mid1);
}

void Track::createBSplineTrack()
{
    m_nodes.clear();
    m_nodes.reserve(m_controlPoints.size() * NODES_PER_LINE + 1);
    pointAtLength.clear();
    pointAtLength.reserve(m_controlPoints.size() * NODES_PER_LINE + 1);
    trackLength = 0;

    std::vector<TrackNode> controlNodes;
    controlNodes.reserve(m_controlPoints.size());
    for (auto &point : m_controlPoints)
    {
        controlNodes.push_back({point.getPosition(), point.getOrientation()});
    }

    for (int i = 0; i < controlNodes.size(); ++i)
    {
        TrackNode B0 = controlNodes[(i + controlNodes.size() - 1) % controlNodes.size()];
        TrackNode B1 = controlNodes[i];
        TrackNode B2 = controlNodes[(i + 1) % controlNodes.size()];
        TrackNode B3 = controlNodes[(i + 2) % controlNodes.size()];

        computeBSplineBasis(B0, B1, B2, B3);
    }

    trackLength += glm::length(m_nodes.back().position - m_nodes.front().position);
    pointAtLength.push_back(trackLength);
    m_nodes.push_back(m_nodes[0]);
}

void Track::createCarinalTrack()
{
    m_nodes.clear();
    m_nodes.reserve(m_controlPoints.size() * NODES_PER_LINE + 1);
    pointAtLength.clear();
    pointAtLength.reserve(m_controlPoints.size() * NODES_PER_LINE + 1);
    trackLength = 0;

    std::vector<TrackNode> controlNodes;
    controlNodes.reserve(m_controlPoints.size());
    for (auto &point : m_controlPoints)
    {
        controlNodes.push_back({point.getPosition(), point.getOrientation()});
    }

    for (int i = 0; i < controlNodes.size(); ++i)
    {
        TrackNode B0 = controlNodes[(i + controlNodes.size() - 1) % controlNodes.size()];
        TrackNode B1 = controlNodes[i];
        TrackNode B2 = controlNodes[(i + 1) % controlNodes.size()];
        TrackNode B3 = controlNodes[(i + 2) % controlNodes.size()];

        computeCarinalBasis(B0, B1, B2, B3);
    }

    trackLength += glm::length(m_nodes.back().position - m_nodes.front().position);
    pointAtLength.push_back(trackLength);
    m_nodes.push_back(m_nodes[0]);
}

void Track::computeBSplineBasis(TrackNode &B0, TrackNode &B1, TrackNode &B2, TrackNode &B3)
{
    const float PERCENT = 1.0f / NODES_PER_LINE;
    for (int i = 0; i < NODES_PER_LINE; ++i)
    {
        float t = i * PERCENT;
        float t_2 = t * t;
        float t_3 = t_2 * t;

        TrackNode currentNode;

        currentNode.position = ((-t_3 + 3 * t_2 - 3 * t + 1) * B0.position + (3 * t_3 - 6 * t_2 + 4) * B1.position + (-3 * t_3 + 3 * t_2 + 3 * t + 1) * B2.position + (t_3)*B3.position) / 6.0f;
        currentNode.orientation = ((-t_3 + 3 * t_2 - 3 * t + 1) * B0.orientation + (3 * t_3 - 6 * t_2 + 4) * B1.orientation + (-3 * t_3 + 3 * t_2 + 3 * t + 1) * B2.orientation + (t_3)*B3.orientation) / 6.0f;

        if (!m_nodes.empty())
        {
            trackLength += glm::length(currentNode.position - m_nodes.back().position);
        }
        else
        {
            trackLength = 0;
        }
        pointAtLength.push_back(trackLength);

        m_nodes.push_back(currentNode);
    }
}

void Track::computeCarinalBasis(TrackNode &B0, TrackNode &B1, TrackNode &B2, TrackNode &B3)
{
    const float PERCENT = 1.0f / NODES_PER_LINE;
    float s = 0.5f * (1.0f - m_tension);
    for (int i = 0; i < NODES_PER_LINE; ++i)
    {
        float t = i * PERCENT;
        float t_2 = t * t;
        float t_3 = t_2 * t;

        float b0Constant = s * (-t_3 + 2 * t_2 - t);
        float b1Constant = s * (-t_3 + t_2) + (2 * t_3 - 3 * t_2 + 1);
        float b2Constant = s * (t_3 - 2 * t_2 + t) + (-2 * t_3 + 3 * t_2);
        float b3Constant = s * (t_3 - t_2);

        TrackNode currentNode;

        currentNode.position = b0Constant * B0.position + b1Constant * B1.position + b2Constant * B2.position + b3Constant * B3.position;
        currentNode.orientation = b0Constant * B0.orientation + b1Constant * B1.orientation + b2Constant * B2.orientation + b3Constant * B3.orientation;

        if (!m_nodes.empty())
        {
            trackLength += glm::length(currentNode.position - m_nodes.back().position);
        }
        else
        {
            trackLength = 0;
        }
        pointAtLength.push_back(trackLength);
        m_nodes.push_back(currentNode);
    }
}

void Track::createTrackObject()
{
    if (m_nodes.empty())
        return;

    std::vector<float> allVertices;
    allVertices.reserve(m_nodes.size() * 6);

    TrackNode startNode = m_nodes[0];
    for (size_t i = 1; i < m_nodes.size(); ++i)
    {
        TrackNode endNode = m_nodes[i];

        glm::vec3 u = glm::normalize(endNode.position - startNode.position);
        glm::vec3 w = glm::normalize(glm::cross(u, startNode.orientation));
        glm::vec3 v = glm::normalize(glm::cross(w, u));

        allVertices.push_back(startNode.position.x + w.x * 0.5f * TRACK_WIDTH);
        allVertices.push_back(startNode.position.y + w.y * 0.5f * TRACK_WIDTH);
        allVertices.push_back(startNode.position.z + w.z * 0.5f * TRACK_WIDTH);
        allVertices.push_back(v.x);
        allVertices.push_back(v.y);
        allVertices.push_back(v.z);
        allVertices.push_back(endNode.position.x + w.x * 0.5f * TRACK_WIDTH);
        allVertices.push_back(endNode.position.y + w.y * 0.5f * TRACK_WIDTH);
        allVertices.push_back(endNode.position.z + w.z * 0.5f * TRACK_WIDTH);
        allVertices.push_back(v.x);
        allVertices.push_back(v.y);
        allVertices.push_back(v.z);
        allVertices.push_back(startNode.position.x - w.x * 0.5f * TRACK_WIDTH);
        allVertices.push_back(startNode.position.y - w.y * 0.5f * TRACK_WIDTH);
        allVertices.push_back(startNode.position.z - w.z * 0.5f * TRACK_WIDTH);
        allVertices.push_back(v.x);
        allVertices.push_back(v.y);
        allVertices.push_back(v.z);
        allVertices.push_back(endNode.position.x - w.x * 0.5f * TRACK_WIDTH);
        allVertices.push_back(endNode.position.y - w.y * 0.5f * TRACK_WIDTH);
        allVertices.push_back(endNode.position.z - w.z * 0.5f * TRACK_WIDTH);
        allVertices.push_back(v.x);
        allVertices.push_back(v.y);
        allVertices.push_back(v.z);

        startNode = endNode;
    }

    glBindVertexArray(m_trackObject.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_trackObject.VBO);
    glBufferData(GL_ARRAY_BUFFER, allVertices.size() * sizeof(float), allVertices.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Track::createPartBazier(TrackNode &startNode, TrackNode &ctrl0, TrackNode &ctrl1, TrackNode &endNode)
{
    const float PERCENT = 1.0f / NODES_PER_LINE;
    for (int j = 0; j < NODES_PER_LINE; ++j)
    {
        float t = j * PERCENT;
        float u = 1.0f - t;

        TrackNode currentNode;

        currentNode.position = (float)pow(u, 3) * startNode.position + 3 * (float)pow(u, 2) * t * ctrl0.position + 3 * u * (float)pow(t, 2) * ctrl1.position + (float)pow(t, 3) * endNode.position;
        currentNode.orientation = (float)pow(u, 3) * startNode.orientation + 3 * (float)pow(u, 2) * t * ctrl0.orientation + 3 * u * (float)pow(t, 2) * ctrl1.orientation + (float)pow(t, 3) * endNode.orientation;

        m_nodes.push_back(currentNode);
    }
}

int Track::searchPositionIndex(float length)
{

    for (int i = 0; i < pointAtLength.size(); ++i)
    {

        if (pointAtLength[i] > length)
        {
            return i - 1;
        }
    }
    return 0;
}
