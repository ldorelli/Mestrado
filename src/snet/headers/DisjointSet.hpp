#ifndef __DISJOINT_HPP__
#define __DISJOINT_HPP__

#include <vector>

/**
 * Simple disjoint set class.
 */ 
 namespace snet {
 	class DisjointSet {
 	public:

 		DisjointSet();
 		/**
 		 *	Creates a new DisjointSet structure with n nodes.
 		 */
 		DisjointSet(int n);

 		/**
 		 *	Joins the sets of two elements.
 		 *	@param A The first element.
 		 *  @param B The second element.
 		 */ 
 		void join(int A, int B);

 		/**
 		 * Returns the representative index for the set of the element.
 		 * @param A The query element.
 		 * @return The index of the representative element for the set.
 		 */
 		int  find(int A);

 		/**
 		 * Calculates the number of distinct sets.
 		 *	@return Number of disjoint sets among the elements.
 		 */
 		int  count();

 		/**
 		 * Counts the number of elements in the set the element A is present.
 		 * @param The query element A.
 		 * @return The number of elements in the set A is present.
 		 */
 		int countSet(int A);

 	private:
 		std::vector<int> sets;
 		int nSets;
 	
 		/** 
 		 * Tests if the query node is ok. Throws exception case not.
 		 */
 		void validate(int i);

 		// Internal use
 		int internalFind(int A);
 	};
 }

#endif
