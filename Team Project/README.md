# Algorithm Team project

## < Detailed description of the design and the requirements >

**Minimum requirements** : Tour period, hotel, transportation, sites(cities), price

**Needed information** :
    100 sites (cities) w/ each site’s tour time
    100 hotels per each sites w/ resonable prices,
    300 transportation among sites w/ resonable prices (assume direct transportation)
    * specific names can be replaced by identification numbers
      (e.g.: hotel-12, transport-15, site-99)
      


1) Implement the data structures including the graph, red black BST tree, and others.
    * others: e.g.) structure, ...
2) The RB tree should make use of the following primitive functions.
   insert, delete, search, print etc.
3) There should be separate UI module.
4) The tree balancing should be done each time the insertion or deletion is performed.



▶ **Minimum requirements of an Input and Output**

    Input: id, budget, destination, period, budget, etc.
    Output: id, itinerary (timed information of hotels, transportations, sites, dates, price)
    
▶ **Minimum requirement for the data structures**

    - A graph for sites layout that shows direct access (100 sites w/ 300 direct routes among them, both random generation).
    The graph consists of edges with distances (thus, travel time and cost to travel each edge).
    - A RB tree to store hotel information: each site linked to the root of the hotel tree. (each site w/ 100 hotels).
    - A RB tree to store reservation info (a key is the customer id).
    
   
▶ extra considerations: hotel to site distance, local sites general preferences, transportation levels (prestige class, business class, economy class), time needed to tour each site, anything that is needed in a practical tour reservation system.

▶ Some of the values above shown can be generated randomly.
Ranges of the values below should be reasonable. Avoid the duplicates.

▶ Other restrictions and special functionalities should be described.
