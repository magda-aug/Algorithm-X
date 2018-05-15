# Algorithm X
Algorithm X solves exact cover problem with trial and error method.\

Program reads sequence of rows F, W_{1},..., W_{n}, where F is filter and W_{1},..., W_{n} is an instance of exact cover problem.\
All rows have the same length d. Row F contains "-" and "+" signs.\
Every row W_{1},..., W_{n} contains at least one row other than "_".\

Program returns sequence of rows representing solutions of instance W_{1},..., W_{n} transformed by filter F by removing positions which have "_" in filter F.

Solution of instance W_{1},..., W_{n} is set Q \subseteq {1,...,n} represented by text R of length d.
This text does not contain "_" sign and satisifies condition

∀ 1 ≤ i ≤ d ∃j \in Q ((W_j)_i = R_i ∧ ∀k∈Q∖{j}(W_k)_i = _)

Solutions are built out of rows W_{1},..., W_{n} according to their ordering. 
Given one solution, by trial and error we choose signs not colliding with previous choices.
