# Paralel machine scheduling problem

*Elías Hernández Abreu =-= alu0101487137@ull.edu.es*

Paralel machine scheduling problem using greedy, grasp, and some other algorithms.

## TODO

- Remove ghost task 0, make it so that when computing tct, task in position
  0 automatically uses 0 as its predecesor for easier understanding and easier computing
- Calculate only addition to TCT instead of whole thing

## NOTES

#### Movement algorithms

- Reinsert a task in a different machine
- Reinsert a taxt in the same machine
- Switch tasks in a same machine
- Switch tasks in different machines

#### Local searches

Have 4 grasps, one for each movement algorithm

### implement vnd

- search best solution saturating with a movement type
- once a local solution is found, for that movement, try with second movement, then with third...
- if a movement finds a better solution, move to it and go back to saturating with first movement
- finish when no movement returns a better solution

### implement rvns

With reinsertion between machines, max length around 8

- search solutions with distance 1
- if one is better than this, move to it, if not, go for next length
- repeat until no better solution is found for the max length.
