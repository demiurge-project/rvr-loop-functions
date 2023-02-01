#ifndef BIG_GRID_EXPLORATION_LOOP_FUNC
#define BIG_GRID_EXPLORATION_LOOP_FUNC

#include "../../src/RVRCoreLoopFunctions.h"
#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/robots/rvr/simulator/rvr_entity.h>

using namespace argos;

class BigGridExplorationLoopFunction : public RVRCoreLoopFunctions
{
public:
  BigGridExplorationLoopFunction();
  BigGridExplorationLoopFunction(const BigGridExplorationLoopFunction &orig);
  virtual ~BigGridExplorationLoopFunction();

  virtual void Destroy();

  virtual argos::CColor GetFloorColor(const argos::CVector2 &c_position_on_plane);
  virtual void PostExperiment();
  virtual void PostStep();
  virtual void Init(TConfigurationNode &t_tree);
  virtual void Reset();
  virtual CVector3 GetRandomPosition();

  Real GetObjectiveFunction();
  
private:
  std::vector<std::vector<int>> m_grid;

  Real m_arenaSize;
  UInt32 m_gridSize;
  Real m_fObjectiveFunction;
     /**
      * The path of the output file.
      */
      std::string m_strOutFile;

     /**
      * The stream associated to the output file.
      */
      std::ofstream m_cOutFile;
};

#endif
