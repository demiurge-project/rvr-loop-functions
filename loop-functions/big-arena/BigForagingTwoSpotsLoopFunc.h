/**
  * @file <loop-functions/example/ForagingLoopFunc.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef BIG_FORAGING_TWO_SPOTS_LOOP_FUNC
#define BIG_FORAGING_TWO_SPOTS_LOOP_FUNC

#include <map>

#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/robots/rvr/simulator/rvr_entity.h>

#include "../../src/RVRCoreLoopFunctions.h"

using namespace argos;

class BigForagingTwoSpotsLoopFunction: public RVRCoreLoopFunctions {
  public:
    BigForagingTwoSpotsLoopFunction();
    BigForagingTwoSpotsLoopFunction(const BigForagingTwoSpotsLoopFunction& orig);
    virtual ~BigForagingTwoSpotsLoopFunction();
    
    virtual void Destroy();
    virtual void Init(TConfigurationNode& t_tree);

    virtual argos::CColor GetFloorColor(const argos::CVector2& c_position_on_plane);
    virtual void PostStep();
    virtual void Reset();
    virtual void PostExperiment();

    Real GetObjectiveFunction();

    CVector3 GetRandomPosition();

    bool IsWithinTriangle(CVector2& c_point_q, CVector2& c_point_a, CVector2& c_point_b, CVector2& c_point_c);
    Real AreaTriangle(CVector2& c_point_a, CVector2& c_point_b, CVector2& c_point_c);

  private:
    Real m_fRadius;
    Real m_fNestLimit;
    CVector2 m_cCoordSpot1;
    CVector2 m_cCoordSpot2;

    Real m_fObjectiveFunction;

    std::map<std::string, UInt32> m_mapFoodData;
};

#endif
