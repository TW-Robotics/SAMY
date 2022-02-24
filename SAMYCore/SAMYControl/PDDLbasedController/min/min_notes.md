# SAMY minimal use case notes

## process steps

1. Move To Pickup Position
2. Close Gripper Signal
3. Wait For Gripper Closed
4. Move To Place Position
(5. Error)

## causal links

start -> 1: gripper is open, object is at object pickup position
1 -> 2: robot gripper is in gripping pose
2 -> 3: expecting gripper closed state
3 -> 4: object gripped
(3 -> 5: object not gripped within timeout)
4 -> end: object is gripped and at object place position

## obtaining facts and fluents - geometric abstraction (based on temporal2 domain)

 (free ?p - pose): no "is-at" for p; OR no object within a certain volume above p
 (is-at ?obj - movable ?p - staticpose): pose of obj is within a certain volume above p
 (is-in-robotpose ?r - robot ?p - robotpose): r's TCP pose is equal to OR with a certain distance of a given pose for p; OR joint pose of r is almost equal to a given jointpose for p
 (is-held-by ?o - movable ?r - resource): gripper of r is closed (mind size of o!) and o is at a certain pose relative to r's TCP pose
 (current-status ?statusval - status): (is it running?)
 (gripper-open ?r - robot): gripper of r is not closed (mind size of o!) - distance of gripper fingers > opening radius for o (configured)
 (gripper-closed ?r - robot): gripper of r is closed (mind size of o!) - distance of gripper fingers <= opening radius for o (configured)
 (can-pick-from ?r - resource ?o - movable ?robotpose - robotpose ?objectpose - pose): configured
 (can-place-to ?r - resource ?o - movable ?robotpose - robotpose ?objectpose - pose): configured
 (expecting-gripper-closed ?r - resource): gripper was instructed to close and has not reportedly finished it
 (idle ?res - resource): robot is not moving and is not expecting the gripper to close

 (move-duration ?r - robot ?startpose ?endpose - robotpose): configured

