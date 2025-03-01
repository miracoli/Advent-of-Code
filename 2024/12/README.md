### First Part:

- **Region Exploration**:  
  Iterates over every cell in the grid. For each unvisited cell, a BFS is launched to explore a connected region defined by contiguous cells of the same plant type.

- **Area Calculation**:  
  The area is incremented for every cell visited during the BFS that belongs to the current region.

- **Perimeter Calculation**:  
  For each cell in the region, the four adjacent neighbors (up, down, left, right) are examined. The perimeter count increases by one if a neighbor is out-of-bounds or if it is of a different plant type.

- **Cost Computation & Output**:  
  After fully exploring a region, the region’s cost is computed as the product of its area and perimeter. The total cost is the sum of these products over all regions, which is then output.

### Second Part:

- **Region Exploration with Bounding Box Tracking**:  
  For every unvisited cell, a BFS explores the entire region of contiguous cells having the same plant type. During exploration, a local visited map is maintained for the region and a bounding box (minimum and maximum row and column indices) is updated based solely on the region’s cells.

- **Area Calculation**:  
  The area is incremented for each cell that is part of the region during the BFS traversal.

- **Contour (Sides) Calculation via 2×2 Windows**:  
  Once the region is completely identified, every 2×2 window within the computed bounding box is examined:
  - **Detection**: Each of the four cells in a window is checked to see if it is part of the region (using the local visited map) and matches the plant type.
  - **Window Sum**: The number of region cells in the window is summed.
  - **Sides Update**:  
    - The sides count is increased by the remainder when the window sum is divided by 2 (i.e. `windowSum % 2`), capturing odd counts.
    - If exactly two cells are present in the window and they form a diagonal pair, two additional sides are added to account for both exposed edges.

- **Cost Computation & Output**:  
  The cost for each region is computed as the product of its area and the computed sides (representing its contour length). The final total cost is the sum of these values for all regions, and this total is then output.
