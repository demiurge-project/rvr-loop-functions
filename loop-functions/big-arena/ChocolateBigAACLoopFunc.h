/*
 * Aggregation with Ambient Clues for the RVR
 *
 * @author Miquel Kegeleirs - <Miquel.Kegeleirs@ulb.be>
 */

#ifndef CHOCOLATE_BIG_AAC_LOOP_FUNC_H
#define CHOCOLATE_BIG_AAC_LOOP_FUNC_H

#include "../../src/RVRCoreLoopFunctions.h"
#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/robots/rvr/simulator/rvr_entity.h>

using namespace argos;

class ChocolateBigAACLoopFunction : public RVRCoreLoopFunctions {

   public:
      ChocolateBigAACLoopFunction();
      ChocolateBigAACLoopFunction(const ChocolateBigAACLoopFunction& orig);
      virtual ~ChocolateBigAACLoopFunction();

      virtual void Destroy();
      virtual void Reset();
      virtual void PostStep();
      virtual void PostExperiment();

      Real GetObjectiveFunction();

      virtual CColor GetFloorColor(const CVector2& c_position_on_plane);

      virtual CVector3 GetRandomPosition();

    private:
      Real m_fRadius;
      CVector2 m_cCoordBlackSpot;
      CVector2 m_cCoordWhiteSpot;

      Real m_fObjectiveFunction;
};

#endif
