# Algorithm X
Algorithm X solves exact cover problem with trial and error method.

Program reads sequence of rows F, W<sub>1</sub>,..., W<sub>n</sub>, where F is filter and W<sub>1</sub>,..., W<sub>n</sub> is an instance of exact cover problem.\
All rows have the same length d. Row F contains "-" and "+" signs.\
Every row W<sub>1</sub>,..., W<sub>n</sub> contains at least one row other than "_".

Program returns sequence of rows representing solutions of instance W<sub>1</sub>,..., W<sub>n</sub> transformed by filter F by removing positions which have "_" in filter F.

Solution of instance W<sub>1</sub>,..., W<sub>n</sub> is set Q ⊆ {1,..., n} represented by text R of length d.
This text does not contain "_" sign and satisifies condition

∀ 1 ≤ i ≤ d ∃ j ∈ Q ((W<sub>j</sub>)<sub>i</sub> = R<sub>i</sub> ∧ ∀k ∈ Q∖{j} (W<sub>k</sub>)<sub>i</sub> = _ )

Solutions are built out of rows W<sub>1</sub>,..., W<sub>n</sub> according to their ordering. 
Given one solution, by trial and error we choose signs not colliding with previous choices.
