For both parts, the disk is not actually modified — only the checksum is updated.  

### First Part:
- Iterates from both ends of the disk array, simulating the movement of used blocks to the front.  
- The checksum accumulates `freeIdx * blockID` for each used block as if it were relocated.  

### Second Part:
- Also iterates from both ends, pretending to move used blocks forward.  
- Stores disk metadata as `(start, size, index)`, where `index = -1` for free space.  
- Initializes the checksum with contributions from used regions during parsing.  
- "Moves" used blocks by adjusting `start` offsets in metadata.  
- Updates the checksum with `blockID * size * (new_start - original_start)` to account for virtual relocations.  
