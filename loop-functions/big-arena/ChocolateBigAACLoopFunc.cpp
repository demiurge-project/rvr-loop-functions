/**
 * @file <ChocolateBigAACLoopFunc.cpp>
 *
 * @author Miquel Kegeleirs - <Miquel.Kegeleirs@ulb.be>
 *
 * @license MIT License
 */

#include "ChocolateBigAACLoopFunc.h"

/****************************************/
/****************************************/

ChocolateBigAACLoopFunction::ChocolateBigAACLoopFunction()
{
  m_fRadius = 0.32;
  m_cCoordBlackSpot = CVector2(0, 0.63);
  m_cCoordWhiteSpot = CVector2(0, -0.63);
  m_fObjectiveFunction = 0;
}

/****************************************/
/****************************************/

ChocolateBigAACLoopFunction::ChocolateBigAACLoopFunction(const ChocolateBigAACLoopFunction &orig) {}

/****************************************/
/****************************************/

ChocolateBigAACLoopFunction::~ChocolateBigAACLoopFunction() {}

/****************************************/
/****************************************/

void ChocolateBigAACLoopFunction::Destroy() {}

/****************************************/
/****************************************/

void ChocolateBigAACLoopFunction::Reset()
{
  m_fObjectiveFunction = 0;
  RVRCoreLoopFunctions::Reset();
}

/****************************************/
/****************************************/

argos::CColor ChocolateBigAACLoopFunction::GetFloorColor(const argos::CVector2 &c_position_on_plane)
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

void ChocolateBigAACLoopFunction::PostStep()
{
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
      m_fObjectiveFunction += 1;
    }
  }
}


/****************************************/
/****************************************/

Real ChocolateBigAACLoopFunction::GetObjectiveFunction()
{
  return m_fObjectiveFunction;
}

/****************************************/
/****************************************/

CVector3 ChocolateBigAACLoopFunction::GetRandomPosition()
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

void ChocolateBigAACLoopFunction::PostExperiment()
{
    LOG << m_fObjectiveFunction << std::endl;
    if (m_bMinimizeScore) {
        m_fObjectiveFunction = -m_fObjectiveFunction;
    }
}

REGISTER_LOOP_FUNCTIONS(ChocolateBigAACLoopFunction, "chocolate_big_aac_loop_functions");
