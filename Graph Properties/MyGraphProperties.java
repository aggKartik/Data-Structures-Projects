// Exercise 4.1.16
package algs41;

import algs13.Queue;
import stdlib.*;

// @author: Kartik Aggarwal
// @date: 8/6/2018
// This is problem 4.1.16 from the textbook
//
// You need only change the constructor.
// You can also change the main method.
// But you should not change eccentricity(), diameter(), radius(), center() or isCenter()
// You can (and should!) add more private methods (such as bfs or dfs)
//
// TODO: complete the following, using only Graph and GraphGenerator. 
// You may copy code from other classes in algs41, but you should not use the classes themselves.  
// In particular, you may not use BreadthFirstPaths although you may copy code from there.
//
// Definitions:
//   - The "distance" from vertex v to vertex w is the length of the shortest path from v to w.
//   - The "eccentricity" of a vertex v is distance to the farthest vertex from v.
//   - The "diameter" of a graph is the maximum eccentricity of any vertex. 
//   - The "radius" of a graph is the smallest eccentricity of any vertex. 
//   -  A "center" is a vertex whose eccentricity is the radius. The center is not necessarily unique.

public class MyGraphProperties {
	int[] eccentricity;
	int diameter;
	int radius;
	int center;

	// Constructor can be linear in G.V() * G.E()
	public MyGraphProperties(Graph G) {
		
		this.eccentricity = new int[G.V()];
		int diameter = Integer.MIN_VALUE;
		int radius = Integer.MAX_VALUE;
		int center = -1;
		
		// If G.V()==0, then these are the correct values.
		// If G is not connected, you should throw a new IllegalArgumentException()
		// I suggest that you first get it to work for a connected graph
		// This will require that you traverse the graph starting from some node (say 0)
		// You can then adjust your code so that it throws an exception in the case that all nodes are not visited

		// TODO
		// compute the eccentricity, diameter, radius and center
		// The center of the graph is not unique, set center to SOME center --- it does not matter which one
		if(G.V() != 0) {
			
			eccentricity[0] = bfs(G, 0);
			radius = diameter = eccentricity[0];
			center = 0;
		
			for(int i = 1; i < G.V(); i++) {
				eccentricity[i] = bfs(G, i);
				if(eccentricity[i] < radius) {
					radius = eccentricity[i];
					center = i;
					}
				
				if(eccentricity[i] > diameter)
					diameter = eccentricity[i];

				}
		}
		
		this.diameter = diameter;
		this.radius   = radius;
		this.center   = center;
	}
	
	private int bfs(Graph G, int s) { //returns max eccentricity of s
		Queue<Integer> q = new Queue<>();
		
		boolean[] marked = new boolean[G.V()];
		int[] distTo = new int[G.V()];
		
		for (int v = 0; v < G.V(); v++) distTo[v] = Integer.MAX_VALUE;
		
		distTo[s] = 0;
		int max = 0;
		int counter  = 0; //Count how many nodes are visited from source
		marked[s] = true;
		q.enqueue(s);
		
		while (!q.isEmpty()) {
			counter++;
			int v = q.dequeue();
			for (int w : G.adj(v)) {
				
				if (!marked[w]) {
					distTo[w] = distTo[v] + 1;
					if(distTo[w] > max)
						max = distTo[w];
					marked[w] = true;
					q.enqueue(w);
				}
			}
		}
	
		if(counter < G.V()) //If all nodes can't be navigated to from source, throw exception
			throw new IllegalArgumentException("Graph is not connected");
		
		counter = 0;
		
		return max;
	}
	
	// Do not change the following constant time methods
	public int eccentricity(int v) { return eccentricity[v]; }
	public int diameter()          { return diameter; }
	public int radius()            { return radius; }
	public int center()            { return center; }
	public boolean isCenter(int v) { return eccentricity[v] == radius; }

	public static void main(String[] args) {
		//Graph G = GraphGenerator.fromIn (new In("data/tinyG.txt")); // this is non-connected -- should throw an exception
		//Graph G = GraphGenerator.connected (10, 20, 2); // Random non-connected graph -- should throw an exception

		Graph G = GraphGenerator.fromIn (new In("data/tinyCG.txt")); // diameter=2, radius=2, every node is a center
		//Graph G = GraphGenerator.binaryTree (10); // A complete binary tree
		//Graph G = GraphGenerator.path (10); // A path -- diameter=V-1
		//Graph G = GraphGenerator.connected (20, 400); // Random connected graph

		StdOut.println(G);
		G.toGraphviz ("g.png");

		MyGraphProperties gp = new MyGraphProperties(G);
		for (int v = 0; v < G.V(); v++)
			StdOut.format ("eccentricity of %d: %d\n", v, gp.eccentricity (v));
		StdOut.format ("diameter=%d, radius=%d, center=%d\n", gp.diameter(), gp.radius (), gp.center ());
	}
}
