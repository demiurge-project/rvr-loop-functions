/*
 * @file <src/core/CoreLoopFunctions.h>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#ifndef AUTOMODE_RVR_LOOP_FUNCTIONS
#define AUTOMODE_RVR_LOOP_FUNCTIONS

#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/loop_functions.h>
#include <argos3/plugins/robots/rvr/simulator/rvr_entity.h>

using namespace argos;

class RVRCoreLoopFunctions : public CLoopFunctions
{
protected:
  ~RVRCoreLoopFunctions();

  /*
   * Reset function. First remove the robots, then re-position them.
   */
  virtual void Reset();

  /*
   * Method used to remove the robots from the arena.
   */
  void RemoveRobots();

  /*
   * Method used to reallocate the robots.
   * The position is given by the method GetRandomPosition().
   */
  void MoveRobots();
  
  /*
   * Method used to get real position of the robot taking into account the offset of the tag
   */
  CVector2 GetRealPosition(CRVREntity &pcRVR);

  /*
   * The number of robots to be placed for the experiment.
   */
  UInt32 m_unNumberRobots;

  /*
   * The radius of the circle in which the robots will be distributed.
   */
  Real m_fDistributionRadius;

  /*
   * The offset of the tag with respect to the center of the robot
   */
  Real m_fTagOffset;

  /*
   * Flag that tells whether we are using the real robot or not.
   */
  bool m_bRealRobot;
  /*
   * Determines if robots initial positions are random or not.
   */
  bool m_bRandomPositions;
  /*
   * Determines if score needs to be minimized.
   */
  bool m_bMinimizeScore;

  CRandom::CRNG *m_pcRng;

public:
  /*
   * Initialization method where the parameters of the loop function
   * are fetched from the xml declaration.
   */
  virtual void Init(argos::TConfigurationNode &t_tree);

  /*
   * This method should return the fitness of the controller.
   */
  virtual Real GetObjectiveFunction() = 0;

  /*
   * Return a random position.
   */
  virtual CVector3 GetRandomPosition() = 0;
};

#endif
