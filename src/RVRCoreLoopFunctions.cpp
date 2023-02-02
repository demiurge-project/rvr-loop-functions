/*
 * @file <src/RVRCoreLoopFunctions.cpp>
 *
 * @author Miquel Kegeleirs - <Miquel.kegeleirs@ulb.be>
 *
 * @package experiments-loop-functions
 *
 * @license MIT License
 */

#include "RVRCoreLoopFunctions.h"

/****************************************/
/****************************************/

void RVRCoreLoopFunctions::Init(argos::TConfigurationNode &t_tree)
{
  m_pcRng = CRandom::CreateRNG("argos");
  TConfigurationNode cParametersNode;
  try
  {
    cParametersNode = GetNode(t_tree, "params");
    GetNodeAttributeOrDefault(cParametersNode, "number_robots", m_unNumberRobots, (UInt32)1);
    GetNodeAttributeOrDefault(cParametersNode, "dist_radius", m_fDistributionRadius, (Real)0);
    GetNodeAttributeOrDefault(cParametersNode, "real_robot", m_bRealRobot, (bool) false);
    GetNodeAttributeOrDefault(cParametersNode, "random_positions", m_bRandomPositions, (bool) true);
    GetNodeAttributeOrDefault(cParametersNode, "minimize_score", m_bMimimizeScore, (bool) true);
    m_fTagOffset = 0.09;
  }
  catch (std::exception e)
  {
    LOGERR << "Problem with Attributes in node params" << std::endl;
  }

  if (m_bRandomPositions) {
    MoveRobots();
  }
}

/****************************************/
/****************************************/

void RVRCoreLoopFunctions::Reset()
{
  MoveRobots();
}

/****************************************/
/****************************************/

RVRCoreLoopFunctions::~RVRCoreLoopFunctions() {}

/****************************************/
/****************************************/

void RVRCoreLoopFunctions::MoveRobots()
{
  CRVREntity *pcRVR;
  bool bPlaced = false;
  UInt32 unTrials;
  CSpace::TMapPerType &tRVRMap = GetSpace().GetEntitiesByType("rvr");
  for (CSpace::TMapPerType::iterator it = tRVRMap.begin(); it != tRVRMap.end(); ++it)
  {
    pcRVR = any_cast<CRVREntity *>(it->second);
    // Choose position at random
    unTrials = 0;
    do
    {
      ++unTrials;
      CVector3 cRVRPosition = GetRandomPosition();
      bPlaced = MoveEntity(pcRVR->GetEmbodiedEntity(),
                           cRVRPosition,
                           CQuaternion().FromEulerAngles(m_pcRng->Uniform(CRange<CRadians>(CRadians::ZERO, CRadians::TWO_PI)),
                                                         CRadians::ZERO, CRadians::ZERO),
                           false);
    } while (!bPlaced && unTrials < 1000);
    if (!bPlaced)
    {
      THROW_ARGOSEXCEPTION("Can't place robot");
    }
  }
}

/****************************************/
/****************************************/

void RVRCoreLoopFunctions::RemoveRobots()
{
  for (UInt32 i = 1; i < m_unNumberRobots + 1; ++i)
  {
    std::ostringstream id;
    id << "rvr" << i;
    RemoveEntity(id.str().c_str());
  }
}

/****************************************/
/****************************************/

CVector2 RVRCoreLoopFunctions::GetRealPosition(CRVREntity &pcRVR)
{
    CVector2 cRVRPosition(0, 0);
    CRadians cZAngle, cYAngle, cXAngle;
    pcRVR.GetEmbodiedEntity().GetOriginAnchor().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle); 

    cRVRPosition.Set(pcRVR.GetEmbodiedEntity().GetOriginAnchor().Position.GetX()-m_fTagOffset*Cos(cZAngle),
                       pcRVR.GetEmbodiedEntity().GetOriginAnchor().Position.GetY()-m_fTagOffset*Sin(cZAngle));
    return cRVRPosition;
}
