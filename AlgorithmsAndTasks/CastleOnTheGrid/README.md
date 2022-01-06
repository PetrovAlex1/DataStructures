You are given a square grid with some cells open ( **.** ) and some blocked ( **X** ). Your playing piece can move along any row or column until it reaches the edge of the grid or a blocked cell. Given a grid, a start and a goal, determine the minmum number of moves to get to the goal.

**Example**.

The grid is shown below:

grid = [&quot;…&quot;, &quot;.X.&quot;, &quot;…&quot;]

startX = 0

startY = 0

goalX = 1

goalY = 2

...

.X.

...

The starting position (startX, startY) = (0, 0) so start in the top left corner. The goal is (goalX, goalY) = (1, 2) . The path is (0, 0) -\&gt; (0. 2) -\&gt; (1, 2). It takes 2  moves to reach the goal.

**Function Description**
 Complete the _minimumMoves_ function in the editor.

minimumMoves has the following parameter(s):

- _string grid[n]:_ an array of strings that represent the rows of the grid
- _int startX:_ starting X coordinate
- _int startY:_ starting Y coordinate
- _int goalX:_ ending X coordinate
- _int goalY:_ ending Y coordinate

**Returns**

- _int:_ the minimum moves to reach the goal

**Input Forma**** t**

The first line contains an integer , the size of the array _grid_.
 Each of the next  lines contains a string of length .
 The last line contains four space-separated integers,

**Sample Input**

STDIN FUNCTION

3 grid[] size n = 3

.X. grid = [&#39;.X.&#39;,&#39;.X.&#39;, &#39;...&#39;]

.X.

0 0 0 2 startX = 0, startY = 0, goalX = 0, goalY = 2

**Sample Output**

3

**Explanation**

Here is a path that one could follow in order to reach the destination in  steps:

(0, 0) -\&gt; (2, 0) -\&gt; (2, 2) -\&gt; (0, 2)

.