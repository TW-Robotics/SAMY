; SAMY minimal use-case domain, temporal
; Bernhard Reiterer, JOANNEUM RESEARCH, 2021
; refactor predicates for easier geometric abstraction
(define (domain samy-min-temporal2)

(:requirements :strips :typing :fluents :durative-actions :equality)

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
 (idle ?res - resource)
)

(:functions
 (move-duration ?r - robot ?startpose ?endpose - robotpose)
)

; robot moves to a pose where it can pick up the object from src
(:durative-action move-to-pickup
 :parameters (?res - robot ?obj - movable ?robotpose ?oldrobotpose - robotpose ?src - staticpose)
 :duration (= ?duration (move-duration ?res ?oldrobotpose ?robotpose))
 :condition (and
  (over all (current-status ok)) ; no error

  (at start (is-in-robotpose ?res ?oldrobotpose)) ; the robot starts at its old pose
  (over all (can-pick-from ?res ?obj ?robotpose ?src)) ; the robot in robotpose can pick up the object from src pose
  (over all (is-at ?obj ?src)) ; the object is at the src pose
  (over all (free ?res)) ; the robot is free
  (over all (gripper-open ?res)) ; the gripper is open
  (at start (idle ?res)) ; the robot is not doing anything else
 )
 :effect (and
  (at end (is-in-robotpose ?res ?robotpose)) ; the robot is now in robotpose
  (at start (not (is-in-robotpose ?res ?oldrobotpose))) ; the robot is no longer in the oldrobotpose
  (at start (not (expecting-gripper-closed ?res))) ; avoid moving away between start and finish of gripper closing
  (at start (not (idle ?res))) ; the robot cannot do other actions in the meantime
  (at end (idle ?res)) ; the robot can do other actions again
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
  (idle ?res) ; the robot is not doing anything else - but this action does not change it, as it terminates immediately
 )
 :effect (and
  (not (free ?res)) ; the robot is no longer free (but not yet holding the object)
  (not (gripper-open ?res)) ; the gripper is no longer open (but not yet closed)
  (not (is-at ?obj ?src)) ; the object is no longer at the src location (but the location is not yet free)
  (expecting-gripper-closed ?res) ; the robot is now expecting the gripper closing to finish
 )
)

; robot sends close gripper signal while at pickup pose
;(:durative-action gripper-close-to-pickup
; :parameters (?res - robot ?obj - movable ?robotpose ?src - staticpose)
; :duration (= ?duration 0.0)
; :condition (and
;  (at start (current-status ok)) ; no error
;  (at start (is-in-robotpose ?res ?robotpose)) ; the robot is at robotpose
;  (at start (can-pick-from ?res ?obj ?robotpose ?src)) ; the robot in robotpose can pick up the object from src pose
;  (at start (is-at ?obj ?src)) ; the object is at the src pose
;  (at start (free ?res)) ; the robot is free
;  (at start (gripper-open ?res)) ; the gripper is open
;  (at start (idle ?res)) ; the robot is not doing anything else - but this action does not change it, as it terminates immediately
; )
; :effect (and
;  (at end (not (free ?res))) ; the robot is no longer free (but not yet holding the object)
;  (at end (not (gripper-open ?res))) ; the gripper is no longer open (but not yet closed)
;  (at end (not (is-at ?obj ?src))) ; the object is no longer at the src location (but the location is not yet free)
;  (at end (expecting-gripper-closed ?res)) ; the robot is now expecting the gripper closing to finish
; )
;)

;robot waits for gripper to close
(:durative-action wait-for-gripper-closed-to-pickup
 :parameters (?res - robot ?obj - movable ?robotpose - robotpose ?src - staticpose)
 :duration (= ?duration 5)
 :condition(and
  (over all (current-status ok)) ; no error
  (at start (expecting-gripper-closed ?res)) ; the robot has just triggered the closing of the gripper
  (at start (idle ?res)) ; the robot is not doing anything else
 )
 :effect(and
  (at end (not (expecting-gripper-closed ?res))) ; the robot is no longer expecting the gripper closing to finish
  (at end (gripper-closed ?res)) ; the gripper is now closed
  (at end (is-held-by ?obj ?res)) ; the robot is now holding the object
  (at start (not (idle ?res))) ; the robot cannot do other actions in the meantime
  (at end (idle ?res)) ; the robot can do other actions again
 )
)

; robot moves from pickup pose to place pose
(:durative-action move-from-pickup-to-place
 :parameters (?res - robot ?obj - movable ?robotpose ?oldrobotpose - robotpose ?dest ?src - staticpose)
 :duration (= ?duration (move-duration ?res ?oldrobotpose ?robotpose))
 :condition(and
  (over all (current-status ok)) ; no error
  (over all (gripper-closed ?res)) ; the gripper is closed
  (over all (is-held-by ?obj ?res)) ; the robot is holding the object
  (at start (is-in-robotpose ?res ?oldrobotpose)) ; the robot is in the oldrobotpose
  (over all (can-place-to ?res ?obj ?robotpose ?dest)) ; the robot in robotpose can place the object to the dest pose
  (at start (free ?dest)) ; the destination pose is free
  (at start (idle ?res)) ; the robot is not doing anything else
 )
 :effect(and
  (at start (not (is-in-robotpose ?res ?oldrobotpose))) ; the robot is no longer in the oldrobotpose
  (at end (is-in-robotpose ?res ?robotpose)) ; the robot is now in robotpose
  (at start (not (expecting-gripper-closed ?res))) ; avoid moving away between start and finish of gripper closing
  (at end (free ?src)) ; the source location is free now
  (at start (not (free ?dest))) ; the destination pose is no longer free (but the object is not there yet)
  (at start (not (idle ?res))) ; the robot cannot do other actions in the meantime
  (at end (idle ?res)) ; the robot can do other actions again
 )

))