/**
  * @file <loop-functions/example/AggregationLoopFunc.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AGGREGATION_TWO_SPOTS_XOR
#define AGGREGATION_TWO_SPOTS_XOR

#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/robots/rvr/simulator/rvr_entity.h>

#include "../../src/CoreLoopFunctions.h"
#include "/home/aligot/Desktop/Arena/NEAT-private/src/controllers/NeuralNetworkRM1Dot1Binary.h"

using namespace argos;

class AggregationTwoSpotsXOR: public CoreLoopFunctions {
  public:
    AggregationTwoSpotsXOR();
    AggregationTwoSpotsXOR(const AggregationTwoSpotsXOR& orig);
    virtual ~AggregationTwoSpotsXOR();

    virtual void Destroy();
    virtual void Init(TConfigurationNode& t_tree);

    virtual argos::CColor GetFloorColor(const argos::CVector2& c_position_on_plane);
    virtual void PostExperiment();
    //virtual void PostStep();
    virtual void Reset();

    Real GetObjectiveFunction();

    CVector3 GetRandomPosition();

    void OpenFile();

  private:
    Real m_fRadius;
    CVector2 m_cCoordSpot1;
    CVector2 m_cCoordSpot2;

    UInt32 m_unScoreSpot1;
    UInt32 m_unScoreSpot2;
    Real m_fObjectiveFunction;

    std::string m_strOutputFile;
    std::ofstream m_cTrace;
    std::ofstream m_cFitness;
};

#endif
