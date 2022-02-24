; SAMY minimal use-case domain
; Bernhard Reiterer, JOANNEUM RESEARCH, 2021
; refactor predicates for easier geometric abstraction
(define (domain samy-min-strips2)

(:requirements :strips :typing )

(:types
 pose status robotpose - object
 mobilepose staticpose - pose
 resource - mobilepose
 human robot - resource
 manipulator - robot
 movable - mobilepose
)

(:constants
 ok error - status
)

(:predicates
 (free ?p - pose)
 (is-at ?obj - movable ?p - staticpose)
 (is-in-robotpose ?r - robot ?p - robotpose)
 (is-held-by ?o - movable ?r - resource)
 (current-status ?statusval - status) ; error or ok
 (gripper-open ?r - robot)
 (gripper-closed ?r - robot)
 (can-pick-from ?r - resource ?o - movable ?robotpose - robotpose ?objectpose - pose)
 (can-place-to ?r - resource ?o - movable ?robotpose - robotpose ?objectpose - pose)
 (expecting-gripper-closed ?r - resource)
)

; robot moves to a pose where it can pick up the object from src
(:action move-to-pickup
 :parameters (?res - robot ?obj - movable ?robotpose ?oldrobotpose - robotpose ?src - staticpose)
 :precondition (and
  (current-status ok) ; no error

  (is-in-robotpose ?res ?oldrobotpose) ; the robot starts at its old pose
  (can-pick-from ?res ?obj ?robotpose ?src) ; the robot in robotpose can pick up the object from src pose
  (is-at ?obj ?src) ; the object is at the src pose
  (free ?res) ; the robot is free
  (gripper-open ?res) ; the gripper is open
 )
 :effect (and
  (is-in-robotpose ?res ?robotpose) ; the robot is now in robotpose
  (not (is-in-robotpose ?res ?oldrobotpose)) ; the robot is no longer in the oldrobotpose
  (not (expecting-gripper-closed ?res)) ; avoid moving away between start and finish of gripper closing
 )
)

; robot sends close gripper signal while at pickup pose
(:action gripper-close-to-pickup
 :parameters (?res - robot ?obj - movable ?robotpose - robotpose ?src - staticpose)
 :precondition (and
  (current-status ok) ; no error
  (is-in-robotpose ?res ?robotpose) ; the robot is at robotpose
  (can-pick-from ?res ?obj ?robotpose ?src) ; the robot in robotpose can pick up the object from src pose
  (is-at ?obj ?src) ; the object is at the src pose
  (free ?res) ; the robot is free
  (gripper-open ?res) ; the gripper is open
 )
 :effect (and
  (not (free ?res)) ; the robot is no longer free (but not yet holding the object)
  (not (gripper-open ?res)) ; the gripper is no longer open (but not yet closed)
  (not (is-at ?obj ?src)) ; the object is no longer at the src location (but the location is not yet free)
  (expecting-gripper-closed ?res) ; the robot is now expecting the gripper closing to finish
 )
)

;robot waits for gripper to close
(:action wait-for-gripper-closed-to-pickup
 :parameters (?res - robot ?obj - movable ?robotpose - robotpose ?src - staticpose)
 :precondition(and
  (current-status ok) ; no error
  (expecting-gripper-closed ?res) ; the robot has just triggered the closing of the gripper
 )
 :effect(and
   (not (expecting-gripper-closed ?res)) ; the robot is no longer expecting the gripper closing to finish
   (gripper-closed ?res) ; the gripper is now closed
   (is-held-by ?obj ?res) ; the robot is now holding the object
 )
)

; robot moves from pickup pose to place pose
(:action move-from-pickup-to-place
 :parameters (?res - robot ?obj - movable ?robotpose ?oldrobotpose - robotpose ?dest ?src - staticpose)
 :precondition(and
  (current-status ok) ; no error
  (gripper-closed ?res) ; the gripper is closed
  (is-held-by ?obj ?res) ; the robot is holding the object
  (is-in-robotpose ?res ?oldrobotpose) ; the robot is in the oldrobotpose
  (can-place-to ?res ?obj ?robotpose ?dest) ; the robot in robotpose can place the object to the dest pose
  (free ?dest) ; the destination pose is free
 )
 :effect(and
  (not (is-in-robotpose ?res ?oldrobotpose)) ; the robot is no longer in the oldrobotpose
  (is-in-robotpose ?res ?robotpose) ; the robot is now in robotpose
  (not (expecting-gripper-closed ?res)) ; avoid moving away between start and finish of gripper closing
  (free ?src) ; the source location is free now
  (not (free ?dest)) ; the destination pose is no longer free (but the object is not there yet)
 )

))