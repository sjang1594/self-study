## find Contours.

Hierarchy data : `<Vec4i>`

* `NEXT_SIBLING  = 0`
* `PREV_SIBLING = 1`
* `CHILD_CONTOUR = 2`
* `PARENT_CONTOUR = 3`

This 4 elements represents `the index of the contours` and that `-1` is used when there is no such object.

---

Let `entry` be an `Vec4i` representing a hierarchy entry. 

* `entry[PARENT_CONTOUR] == -1` : This contour has no parent -- (i.e) it's a top-level contour
* `entry[CHILD_CONTOUR] == -1` : This contours has no children
* `entry[NEXT_SIBLING] == -1`: There are no more contours at this level of hierarchy for this particular parent.

