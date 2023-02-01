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

void ChocolateBigAACLoopFunction::Init(TConfigurationNode& t_tree) {
    RVRCoreLoopFunctions::Init(t_tree);
    /* Get output file name from XML tree */
    GetNodeAttribute(t_tree, "output", m_strOutFile);
    /* Open the file for text writing */
    m_cOutFile.open(m_strOutFile.c_str(), std::ofstream::out | std::ofstream::app);
    if(m_cOutFile.fail()) {
       THROW_ARGOSEXCEPTION("Error opening file \"" << m_strOutFile << "\": " << ::strerror(errno));
    }
}
/****************************************/
/****************************************/

ChocolateBigAACLoopFunction::~ChocolateBigAACLoopFunction() {}

/****************************************/
/****************************************/

void ChocolateBigAACLoopFunction::Destroy() {
  /* Close the output file */
    m_cOutFile.close();
    if(m_cOutFile.fail()) {
        THROW_ARGOSEXCEPTION("Error closing file \"" << m_strOutFile << "\": " << ::strerror(errno));
    }
}

/****************************************/
/****************************************/

void ChocolateBigAACLoopFunction::Reset()
{
  m_fObjectiveFunction = 0;
  RVRCoreLoopFunctions::Reset();
  /* Close the output file */
    m_cOutFile.close();

    if(m_cOutFile.fail()) {
        THROW_ARGOSEXCEPTION("Error closing file \"" << m_strOutFile << "\": " << ::strerror(errno));
    }
    /* Open the file for text writing */
    m_cOutFile.open(m_strOutFile.c_str(), std::ofstream::out | std::ofstream::app);
    if(m_cOutFile.fail()) {
        THROW_ARGOSEXCEPTION("Error opening file \"" << m_strOutFile << "\": " << ::strerror(errno));
    }
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
  CSpace::TMapPerType &tRVRMap = GetSpace().GetEntitiesByType("rvr");
  CVector2 cRVRPosition(0, 0);
  for (CSpace::TMapPerType::iterator it = tRVRMap.begin(); it != tRVRMap.end(); ++it)
  {
    CRVREntity *pcRVR = any_cast<CRVREntity *>(it->second);
    if(m_bRealRobot)
    {
      cRVRPosition = GetRealPosition(*pcRVR);
    }
    else
    {
      cRVRPosition.Set(pcRVR->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                       pcRVR->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());
    }
    Real fDistanceSpot = (m_cCoordBlackSpot - cRVRPosition).Length();
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
  if (m_bMinimizeScore) {
      return -m_fObjectiveFunction;
  }
  else {
      return m_fObjectiveFunction;
  }
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
    m_cOutFile << m_fObjectiveFunction << std::endl;
}

REGISTER_LOOP_FUNCTIONS(ChocolateBigAACLoopFunction, "chocolate_big_aac_loop_functions");
