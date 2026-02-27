Manual Drawing of a Graph
An interactive application designed for manually drawing, visualizing, and manipulating graphs (nodes and edges) through a Graphical User Interface (GUI), heavily utilizing pointers for efficient memory management and data linking.

🚀 Main Features
Interactive Drawing: Add, move, and delete nodes and edges manually using the mouse directly on the canvas.

Pointer-Based Architecture: Uses pointers extensively to link nodes and edges dynamically, ensuring efficient memory management and fast graph traversal.

Visual-to-Logic Mapping: Translates the visual drawings into classic graph theory data structures (e.g., adjacency lists using pointers to Node objects).

Real-Time Manipulation: The internal graph structure updates instantly as the user interacts with the graphical interface.

📁 Project Structure
The application architecture is divided into the following logical modules:

GUI / Canvas: Visual components handling user input, rendering, and window management.

Data Structures (Graph, Node*, Edge*): The core logic where pointers are used to connect Node instances via Edge instances, maintaining the mathematical properties of the created graph.

Event Handlers: Captures mouse events (clicks, drags) to place nodes or draw lines (edges) between them.

🛠️ Required Dependencies
To compile and run this project, you will need:

Compatible IDE (e.g., Visual Studio).

Graphics Framework: The libraries required to run the UI (e.g., Qt, SFML, or another native framework).

C++ Standard Libraries: For data structure and pointer management (using raw pointers or smart pointers like std::shared_ptr).
