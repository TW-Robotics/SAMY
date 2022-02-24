(define (problem samy-min-strips-2) (:domain samy-min-strips)
(:objects
 r - manipulator
 o - movable
 src dst - staticpose ; object locations
 rstart rsrc rdst - staticpose ; robot poses
)

(:init
 (free dst) ; the destination location is free
 (current-status ok) ; no error
 (can-pick-from r o rsrc src) ; the robot in the rsrc pose can pickup the object from the src pose
 (can-place-to r o rdst dst) ; the robot in rdst pose can place the object to dst pose

 (is-at o r) ; the robot is holding the object
 (is-at r rsrc) ; the robot is in the pickup robotpose
 (gripper-closed r) ; the gripper is closed
)

; expect just the final action of the use-case plan
(:goal (and
 (is-at o r) ; the robot is holding the object
 (is-at r rdst) ; the robot is at the destination placement position
 (gripper-closed r) ; the gripper is closed

)
))



