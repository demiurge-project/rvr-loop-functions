/**
 * @file <BigForagingTwoSpotsLoopFunc.cpp>
 *
 * @author Miquel Kegeleirs - <Miquel.kegeleirs@ulb.be>
 *
 * @license MIT License
 */

#include "BigForagingTwoSpotsLoopFunc.h"

/****************************************/
/****************************************/

BigForagingTwoSpotsLoopFunction::BigForagingTwoSpotsLoopFunction()
{
  m_fRadius = 0.265;
  m_fNestLimit = -0.63;
  m_cCoordSpot1 = CVector2(0.8, 0);
  m_cCoordSpot2 = CVector2(-0.8, 0);
  m_fObjectiveFunction = 0;
}

/****************************************/
/****************************************/

BigForagingTwoSpotsLoopFunction::BigForagingTwoSpotsLoopFunction(const BigForagingTwoSpotsLoopFunction &orig)
{
}

/****************************************/
/****************************************/

void BigForagingTwoSpotsLoopFunction::Init(TConfigurationNode &t_tree)
{
  RVRCoreLoopFunctions::Init(t_tree);
}

/****************************************/
/****************************************/

BigForagingTwoSpotsLoopFunction::~BigForagingTwoSpotsLoopFunction()
{
}

/****************************************/
/****************************************/

void BigForagingTwoSpotsLoopFunction::Destroy() {}

/****************************************/
/****************************************/

argos::CColor BigForagingTwoSpotsLoopFunction::GetFloorColor(const argos::CVector2 &c_position_on_plane)
{
  CVector2 vCurrentPoint(c_position_on_plane.GetX(), c_position_on_plane.GetY());
  Real d = (m_cCoordSpot1 - vCurrentPoint).Length();
  if (d <= m_fRadius)
  {
    return CColor::BLACK;
  }

  d = (m_cCoordSpot2 - vCurrentPoint).Length();
  if (d <= m_fRadius)
  {
    return CColor::BLACK;
  }

  // if (vCurrentPoint.GetY() > m_fNestLimit)
  //   return CColor::GRAY50;
  // else
  //   return CColor::WHITE;
  if (vCurrentPoint.GetY() < m_fNestLimit)
  {
    Real fMaxDim = 1.305;
    Real fLengthWall = 0.7;
    Real fWidthWall = 0.01;
    Real fPI = 3.14159265;
    CVector2 cCenter(0, m_fNestLimit);
    CVector2 cTop(1.131 + fWidthWall, m_fNestLimit);
    CVector2 cBottom(-1.131 - fWidthWall, m_fNestLimit);
    CVector2 cAngle1(1.131 - ARGOS_COS(60 * fPI / 180.0f) * fLengthWall / 2 + fWidthWall, m_fNestLimit - (ARGOS_SIN(60 * fPI / 180.0f) * fLengthWall / 2) - fWidthWall);
    CVector2 cAngle2(fLengthWall / 2 + fWidthWall, -fMaxDim);
    CVector2 cAngle3(-(fLengthWall / 2 + fWidthWall), -fMaxDim);
    CVector2 cAngle4(-1.131 + ARGOS_COS(60 * fPI / 180.0f) * fLengthWall / 2 - fWidthWall, m_fNestLimit - (ARGOS_SIN(60 * fPI / 180.0f) * fLengthWall / 2) - fWidthWall);
    if ((IsWithinTriangle(vCurrentPoint, cCenter, cTop, cAngle1)) ||
        (IsWithinTriangle(vCurrentPoint, cCenter, cAngle2, cAngle3)) ||
        (IsWithinTriangle(vCurrentPoint, cCenter, cAngle1, cAngle2)) ||
        (IsWithinTriangle(vCurrentPoint, cCenter, cAngle3, cAngle4)) ||
        (IsWithinTriangle(vCurrentPoint, cCenter, cAngle4, cBottom)))
    {
      return CColor::WHITE;
    }
    else
    {
      return CColor::GRAY50;
    }
  }
  else
  {
    return CColor::GRAY50;
  }
}

/****************************************/
/****************************************/

Real BigForagingTwoSpotsLoopFunction::AreaTriangle(CVector2 &c_point_a, CVector2 &c_point_b, CVector2 &c_point_c)
{
  Real fArea = Abs(c_point_a.GetX() * (c_point_b.GetY() - c_point_c.GetY()) + c_point_b.GetX() * (c_point_c.GetY() - c_point_a.GetY()) + c_point_c.GetX() * (c_point_a.GetY() - c_point_b.GetY())) / 2;
  return fArea;
}

/****************************************/
/****************************************/

bool BigForagingTwoSpotsLoopFunction::IsWithinTriangle(CVector2 &c_point_q, CVector2 &c_point_a, CVector2 &c_point_b, CVector2 &c_point_c)
{
  Real fAreaTriangle = AreaTriangle(c_point_a, c_point_b, c_point_c);
  Real fAreaABQ = AreaTriangle(c_point_a, c_point_b, c_point_q);
  Real fAreaBCQ = AreaTriangle(c_point_b, c_point_c, c_point_q);
  Real fAreaACQ = AreaTriangle(c_point_a, c_point_c, c_point_q);

  if (Abs(fAreaTriangle - (fAreaABQ + fAreaACQ + fAreaBCQ)) < 0.0001)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/****************************************/
/****************************************/

void BigForagingTwoSpotsLoopFunction::Reset()
{
  RVRCoreLoopFunctions::Reset();
  std::ios::sync_with_stdio(false);
  m_mapFoodData.clear();
  m_fObjectiveFunction = 0;
}

/****************************************/
/****************************************/

void BigForagingTwoSpotsLoopFunction::PostStep()
{
  UInt32 score_temp = m_fObjectiveFunction;

  CSpace::TMapPerType &tRVRMap = GetSpace().GetEntitiesByType("rvr");
  CVector2 cRVRPosition(0, 0);
  for (CSpace::TMapPerType::iterator it = tRVRMap.begin(); it != tRVRMap.end(); ++it)
  {
    CRVREntity *pcRVR = any_cast<CRVREntity *>(it->second);

    std::string strRobotId = pcRVR->GetId();
    if(m_bRealRobot)
    {
      cRVRPosition = GetRealPosition(*pcRVR);
    }
    else
    {
      cRVRPosition.Set(pcRVR->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                       pcRVR->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());
    }

    Real fDistanceSpot1 = (m_cCoordSpot1 - cRVRPosition).Length();
    Real fDistanceSpot2 = (m_cCoordSpot2 - cRVRPosition).Length();
    if (fDistanceSpot1 <= m_fRadius)
    {
      m_mapFoodData[strRobotId] = 1;
    }
    else if (fDistanceSpot2 <= m_fRadius)
    {
      m_mapFoodData[strRobotId] = 1;
    }
    else if (cRVRPosition.GetY() <= m_fNestLimit)
    {
      std::map<std::string, UInt32>::iterator itFood = m_mapFoodData.find(strRobotId);
      if (itFood != m_mapFoodData.end())
      {
        m_fObjectiveFunction += itFood->second;
      }
      m_mapFoodData[strRobotId] = 0;
      // LOG << "Obj " << m_fObjectiveFunction << std::endl;
    }
  }
  if (score_temp != m_fObjectiveFunction)
  {
    // LOGERR << "Obj " << m_fObjectiveFunction << std::endl;
  }
}

/****************************************/
/****************************************/

Real BigForagingTwoSpotsLoopFunction::GetObjectiveFunction()
{
  if (m_bMinimizeScore) {
      return -m_fObjectiveFunction;
  }
  else {
      return m_fObjectiveFunction;
  }
}

/****************************************/
/****************************************/

CVector3 BigForagingTwoSpotsLoopFunction::GetRandomPosition()
{
  Real temp;
  Real a = m_pcRng->Uniform(CRange<Real>(0.0f, 1.0f));
  Real b = m_pcRng->Uniform(CRange<Real>(0.0f, 1.0f));
  // If b < a, swap them
  if (b < a)
  {
    temp = a;
    a = b;
    b = temp;
  }
  Real fPosX = b * m_fDistributionRadius * cos(2 * CRadians::PI.GetValue() * (a / b));
  Real fPosY = b * m_fDistributionRadius * sin(2 * CRadians::PI.GetValue() * (a / b));

  return CVector3(fPosX, fPosY, 0);
}

/****************************************/
/****************************************/

void BigForagingTwoSpotsLoopFunction::PostExperiment()
{
  if (m_bOutputInFile)
  {
    m_cOutFile << m_fObjectiveFunction << std::endl;
  }
  else
  {
    LOG << m_fObjectiveFunction << std::endl;
  }
}

REGISTER_LOOP_FUNCTIONS(BigForagingTwoSpotsLoopFunction, "big_foraging_loop_functions");
