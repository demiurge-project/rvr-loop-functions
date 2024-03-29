/**
 * @file <loop-functions/example/AggregationWhiteAndBlackLoopFunc.cpp>
 *
 * @author Jonas Kuckling - <jonas.kuckling@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include "AggregationWhiteAndBlackLoopFunc.h"

/****************************************/
/****************************************/

AggregationWhiteAndBlackLoopFunc::AggregationWhiteAndBlackLoopFunc()
{
  m_fRadius = 0.3;
  m_cCoordBlackSpot = CVector2(0.5, 0);
  m_cCoordWhiteSpot = CVector2(-0.5, 0);
  m_unScoreSpot = 0;
  m_fObjectiveFunction = 0;
}

/****************************************/
/****************************************/

AggregationWhiteAndBlackLoopFunc::AggregationWhiteAndBlackLoopFunc(const AggregationWhiteAndBlackLoopFunc &orig) {}

/****************************************/
/****************************************/

AggregationWhiteAndBlackLoopFunc::~AggregationWhiteAndBlackLoopFunc() {}

/****************************************/
/****************************************/

void AggregationWhiteAndBlackLoopFunc::Destroy() {}

/****************************************/
/****************************************/

void AggregationWhiteAndBlackLoopFunc::Reset()
{
  m_fObjectiveFunction = 0;
  m_unScoreSpot = 0;
  CoreLoopFunctions::Reset();
}

/****************************************/
/****************************************/

argos::CColor AggregationWhiteAndBlackLoopFunc::GetFloorColor(const argos::CVector2 &c_position_on_plane)
{
  CVector2 vCurrentPoint(c_position_on_plane.GetX(), c_position_on_plane.GetY());
  Real d = (m_cCoordBlackSpot - vCurrentPoint).Length();
  if (d <= m_fRadius)
  {
    return CColor::BLACK;
  }
  d = (m_cCoordWhiteSpot - vCurrentPoint).Length();
  if (d <= m_fRadius)
  {
    return CColor::WHITE;
  }

  return CColor::GRAY50;
}

/****************************************/
/****************************************/

void AggregationWhiteAndBlackLoopFunc::PostStep()
{
  m_unScoreSpot = 0;
  CSpace::TMapPerType &tEpuckMap = GetSpace().GetEntitiesByType("rvr");
  CVector2 cEpuckPosition(0, 0);
  for (CSpace::TMapPerType::iterator it = tEpuckMap.begin(); it != tEpuckMap.end(); ++it)
  {
    CRVREntity *pcEpuck = any_cast<CRVREntity *>(it->second);
    cEpuckPosition.Set(pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                       pcEpuck->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());

    Real fDistanceSpot = (m_cCoordBlackSpot - cEpuckPosition).Length();
    if (fDistanceSpot <= m_fRadius)
    {
      m_unScoreSpot += 1;
    }
  }
  m_fObjectiveFunction += m_unScoreSpot / (Real)m_unNumberRobots;
}

/****************************************/
/****************************************/

void AggregationWhiteAndBlackLoopFunc::PostExperiment()
{
  // TODO: Maybe normalize by the execution time?
  LOG << m_fObjectiveFunction << std::endl;
}

/****************************************/
/****************************************/

Real AggregationWhiteAndBlackLoopFunc::GetObjectiveFunction()
{
  return m_fObjectiveFunction;
}

/****************************************/
/****************************************/

CVector3 AggregationWhiteAndBlackLoopFunc::GetRandomPosition()
{
  Real a;
  Real b;
  Real temp;

  a = m_pcRng->Uniform(CRange<Real>(0.0f, 1.0f));
  b = m_pcRng->Uniform(CRange<Real>(0.0f, 1.0f));
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

REGISTER_LOOP_FUNCTIONS(AggregationWhiteAndBlackLoopFunc, "aggregation_white_and_black_loopfunc");
